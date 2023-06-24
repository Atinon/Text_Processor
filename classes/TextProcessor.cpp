#include <algorithm>
#include "TextProcessor.h"
#include "line/BaseLineDerivedClasses.h"


const size_t TextProcessor::NPOS_ = -1;

TextProcessor::TextProcessor(IConfig *config) : fileReader_(config->getFileReader()),
                                                fileWriter_(config->getFileWriter()),
                                                currentFileIndex_(NPOS_) {}

TextProcessor::~TextProcessor() {
    for(FileData &fdRef : files_){
        deAllocAllLines_(fdRef.lines_);
    }
}

void TextProcessor::deAllocSingleLine_(BaseLine *&line) {
    delete line;
    line = nullptr;
}

void TextProcessor::deAllocAllLines_(std::vector<BaseLine *> &vectorRef) {
    if (!vectorRef.empty()) {
        for (BaseLine *&line: vectorRef) {
            deAllocSingleLine_(line);
        }
    }
}

template<typename T>
void TextProcessor::parseIndexOrSetToLast_(size_t &indexRef, const std::vector<T> &vec) {
    indexRef = indexRef > vec.size() ? vec.size() : indexRef;
}

template<typename T>
void TextProcessor::parseIndexOrThrow_(size_t index, const std::vector<T> &vec) {
    if (index >= vec.size()) {
        throw std::runtime_error("Invalid index.");
    }
}

template<typename T>
void TextProcessor::parseIndexRangeOrThrow_(size_t indexStart, size_t indexEnd, const std::vector<T> &vec) {
    if (indexStart >= indexEnd) {
        throw std::runtime_error("Inversed index range.");
    }
    parseIndexOrThrow_(indexEnd, vec);
    // If indexStart < indexEnd && indexEnd in range, assumes correct boundaries
}

void TextProcessor::checkIfAnyOpenFilesOrThrow_() const {
    if(currentFileIndex_ == NPOS_){
        throw std::runtime_error("No file open.");
    }
}

std::vector<BaseLine *> &TextProcessor::getCurrentLinesRefOrThrow_() {
    checkIfAnyOpenFilesOrThrow_();

    return files_[currentFileIndex_].lines_;
}

const std::vector<BaseLine *> &TextProcessor::getCurrentLinesConstRefOrThrow_() const {
    checkIfAnyOpenFilesOrThrow_();

    return files_[currentFileIndex_].lines_;
}

std::string &TextProcessor::getCurrentFileNameRefOrThrow_() {
    checkIfAnyOpenFilesOrThrow_();

    return files_[currentFileIndex_].fileName;
}



void TextProcessor::open(const std::string &fileName) {
    std::vector<std::string> rawData;

    fileReader_->setFileName(fileName);

    try {
        rawData = fileReader_->readFileContent();
    }
    catch (...) {
        throw;
    }

    FileData fd;
    fd.fileName = fileName;
    try {
        fd.lines_ = LineParser::createFromStringVector(rawData);
    }
    catch (const std::invalid_argument &e) {
        throw std::runtime_error(e.what());
    }
    catch(const std::bad_alloc &){
        throw std::runtime_error("Not enough memory to open a new file.");
    }
    catch (...) {
        throw;
    }

    try{
        files_.push_back(fd);
    }
    catch(const std::bad_alloc &){
        deAllocAllLines_(fd.lines_);
        throw std::runtime_error("Not enough memory to add file to current files.");
    }

    currentFileIndex_ = files_.size() - 1;
}

void TextProcessor::save() {
    saveAs(getCurrentFileNameRefOrThrow_());
}

void TextProcessor::saveAs(const std::string &fileName) {
    const std::vector<BaseLine *> &currentLines = getCurrentLinesConstRefOrThrow_();

    fileWriter_->setFileName(fileName);

    try {
        fileWriter_->writeFileContent(currentLines);
    }
    catch (...) {
        throw;
    }
}

const std::vector<BaseLine *> &TextProcessor::getLines() const {
    return getCurrentLinesConstRefOrThrow_();
}

void TextProcessor::sort() {
    struct NumberDotLinePositions {
        size_t idx;
        BaseLine *line;
    };

    // Separate NumberAndDotLine objects from the rest
    std::vector<NumberDotLinePositions> numberAndDotLines;
    std::vector<BaseLine *> otherLines;

    std::vector<BaseLine *> &currentLinesRef = getCurrentLinesRefOrThrow_();
    try {
        for (size_t i = 0; i < currentLinesRef.size(); ++i) {
            BaseLine *currentLine = currentLinesRef[i];
            if (currentLine->getType() == BaseLine::NUMBER_AND_DOT) {
                numberAndDotLines.push_back(NumberDotLinePositions{i, currentLine});
                continue;
            }
            otherLines.push_back(currentLine);
        }
    }
    catch (...) {
        throw std::runtime_error("Internal sorting function error. Stage: 1");
    }

    std::vector<BaseLine *> backup;
    try {
        backup = currentLinesRef;
    }
    catch (...) {
        throw std::runtime_error("Internal sorting function error. Stage: 2");
    }

    try {
        // Sort the other lines using LineComparator
        std::sort(otherLines.begin(), otherLines.end(), LineComparator());

        // Combine the sorted lines and insert NumberAndDot lines at their previous indexes
        currentLinesRef.clear();
        currentLinesRef.reserve(otherLines.size() + numberAndDotLines.size());
        currentLinesRef.insert(currentLinesRef.begin(), otherLines.begin(), otherLines.end());
        for (const NumberDotLinePositions &line: numberAndDotLines) {
            currentLinesRef.insert(currentLinesRef.begin() + line.idx, line.line);
        }
    } catch (...) {
        currentLinesRef.clear();
        currentLinesRef = backup;
        throw std::runtime_error("Internal sorting function error. Stage: 3");
    }
}

void TextProcessor::addSingleLine(size_t index, const std::string &rawData) {
    std::vector<BaseLine *> &currentLinesRef = getCurrentLinesRefOrThrow_();

    parseIndexOrSetToLast_(index, currentLinesRef);

    BaseLine *newLine;
    try {
        newLine = LineParser::createFromString(rawData);
    }
    catch (const std::invalid_argument &e) {
        throw std::runtime_error(e.what());
    }
    catch (const std::bad_alloc &) {
        throw std::runtime_error("Unable to allocate space for new line.");
    }

    try {
        currentLinesRef.insert(currentLinesRef.begin() + index, newLine);
    }
    catch (...) {
        deAllocSingleLine_(newLine);
        throw std::runtime_error("Internal error. Unable to add line to existing lines.");
    }
}

void TextProcessor::addManyLines(size_t index, const std::vector<std::string> &rawData) {
    std::vector<BaseLine *> &currentLinesRef = getCurrentLinesRefOrThrow_();

    parseIndexOrSetToLast_(index, currentLinesRef);
    std::vector<BaseLine *> linesToAdd;
    try {
        linesToAdd = LineParser::createFromStringVector(rawData);
    }
    catch (const std::invalid_argument &e) {
        throw std::runtime_error(e.what());
    }
    catch (...) {
        throw;
    }

    try {
        currentLinesRef.reserve(linesToAdd.size());
        currentLinesRef.insert(currentLinesRef.begin() + index, linesToAdd.begin(), linesToAdd.end());
    }
    catch (...) {
        throw std::runtime_error("Unable to allocate space for new lines.");
    }
}

void TextProcessor::removeSingleLine(size_t index) {
    std::vector<BaseLine *> &currentLinesRef = getCurrentLinesRefOrThrow_();

    parseIndexOrThrow_(index, currentLinesRef);

    try {
        BaseLine *currentLine = currentLinesRef[index];
        currentLinesRef.erase(currentLinesRef.begin() + index);
        deAllocSingleLine_(currentLine);
    }
    catch (...) {
        throw std::runtime_error("Error removing line at index: " + std::to_string(index));
    }
}

void TextProcessor::removeManyLines(size_t indexStart, size_t indexEnd) {
    std::vector<BaseLine *> &currentLinesRef = getCurrentLinesRefOrThrow_();

    parseIndexRangeOrThrow_(indexStart, indexEnd, currentLinesRef);

    std::vector<BaseLine *> pointersToFree;

    try {
        // inclusive
        for (size_t i = indexStart; i <= indexEnd; ++i) {
            pointersToFree.push_back(currentLinesRef[i]);
        }
    }
    catch (const std::bad_alloc &) {
        throw std::runtime_error("Internal memory allocation error.");
    }

    try {
        currentLinesRef.erase(currentLinesRef.begin() + indexStart, currentLinesRef.begin() + indexEnd + 1);
    }
    catch (...) {
        throw std::runtime_error("Failed to remove lines. State should not have been changed.");
    }

    for (BaseLine *&line: pointersToFree) {
        deAllocSingleLine_(line);
    }
}

bool TextProcessor::blockExists_() const {
    return block_.indexStart != Block::NPOS_ && block_.indexEnd != Block::NPOS_;
}

bool TextProcessor::blockForCurrentFile_() const {
    return block_.fileId == currentFileIndex_;
}

void TextProcessor::setBlock(size_t indexStart, size_t indexEnd) {
    std::vector<BaseLine *> &currentLinesRef = getCurrentLinesRefOrThrow_();

    parseIndexRangeOrThrow_(indexStart, indexEnd, currentLinesRef);

    block_.fileId = currentFileIndex_;
    block_.indexStart = indexStart;
    block_.indexEnd = indexEnd;

    try{
        // inclusive
        block_.vectorLinePtr.assign
                (currentLinesRef.begin() + block_.indexStart, currentLinesRef.begin() + block_.indexEnd + 1);
    }
    catch(const std::bad_alloc &){
        unsetBlock();
        throw std::runtime_error("Error setting block. Memory allocation failure.");
    }
}

void TextProcessor::unsetBlock() {
    if (!blockExists_()) {
        throw std::runtime_error("No block set.");
    }
    block_.vectorLinePtr.clear();
    block_.fileId = Block::NPOS_;
    block_.indexStart = Block::NPOS_;
    block_.indexEnd = Block::NPOS_;
}

const std::vector<BaseLine *> &TextProcessor::getBlock() const {
    if (!blockExists_()) {
        throw std::runtime_error("No block set.");
    }

    if(!blockForCurrentFile_()){
        throw std::runtime_error("Block not set for current file. Please update block.");
    }

    return block_.vectorLinePtr;
}

std::vector<std::string> TextProcessor::getOpenedFileNames() {
    std::vector<std::string> result;

    result.reserve(files_.size());
    for (const FileData &fd : files_) {
        result.push_back(fd.fileName);
    }

    return result;
}

void TextProcessor::setCurrentFile(size_t index) {
    parseIndexOrThrow_(index, files_);

    if(index == currentFileIndex_){
        throw std::runtime_error("This file is the current file set.");
    }

    currentFileIndex_ = index;
}

