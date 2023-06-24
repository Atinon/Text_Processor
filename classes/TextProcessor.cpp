#include <algorithm>
#include "TextProcessor.h"
#include "line/BaseLineDerivedClasses.h"


TextProcessor::TextProcessor(IConfig *config) : fileReader_(config->getFileReader()),
                                                fileWriter_(config->getFileWriter()) {}

TextProcessor::~TextProcessor() {
    deAllocAllLines_();
}

bool TextProcessor::blockExists_() const {
    return block_.indexStart != Block::NPOS_ && block_.indexEnd != Block::NPOS_;
}

void TextProcessor::parseIndexOrSetToLast_(size_t &indexRef) {
    indexRef = indexRef > lines_.size() ? lines_.size() : indexRef;
}

void TextProcessor::parseIndexOrThrow_(size_t index) {
    if (index >= lines_.size()) {
        throw std::runtime_error("Invalid index.");
    }
}


void TextProcessor::parseIndexRangeOrThrow_(size_t indexStart, size_t indexEnd) {
    if (indexStart >= indexEnd) {
        throw std::runtime_error("Inversed index range.");
    }
    parseIndexOrThrow_(indexEnd);
    // If indexStart < indexEnd && indexEnd in range, assumes correct boundaries
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

    try {
        // Can add a separate vector to store backup data in case creating fails
        deAllocAllLines_();
        lines_ = LineParser::createFromStringVector(rawData);
    }
    catch (const std::invalid_argument &e) {
        throw std::runtime_error(e.what());
    }
    catch (...) {
        throw;
    }
}

void TextProcessor::save() {
    saveAs(fileReader_->getFileName());
}

void TextProcessor::saveAs(const std::string &fileName) {
    fileWriter_->setFileName(fileName);

    try {
        fileWriter_->writeFileContent(lines_);
    }
    catch (...) {
        throw;
    }
}

const std::vector<BaseLine *> &TextProcessor::getLines() const {
    return lines_;
}

void TextProcessor::deAllocSingleLine_(BaseLine *&line) {
    delete line;
    line = nullptr;
}

void TextProcessor::deAllocAllLines_() {
    if (!lines_.empty()) {
        for (BaseLine *&line: lines_) {
            deAllocSingleLine_(line);
        }
    }
}

void TextProcessor::sort() {
    struct NumberDotLinePositions {
        size_t idx;
        BaseLine *line;
    };

    // Separate NumberAndDotLine objects from the rest
    std::vector<NumberDotLinePositions> numberAndDotLines;
    std::vector<BaseLine *> otherLines;
    try {
        for (size_t i = 0; i < lines_.size(); ++i) {
            BaseLine *currentLine = lines_[i];
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
        backup = lines_;
    }
    catch (...) {
        throw std::runtime_error("Internal sorting function error. Stage: 2");
    }

    try {
        // Sort the other lines using LineComparator
        std::sort(otherLines.begin(), otherLines.end(), LineComparator());

        // Combine the sorted lines and insert NumberAndDot lines at their previous indexes
        lines_.clear();
        lines_.reserve(otherLines.size() + numberAndDotLines.size());
        lines_.insert(lines_.begin(), otherLines.begin(), otherLines.end());
        for (const NumberDotLinePositions &line: numberAndDotLines) {
            lines_.insert(lines_.begin() + line.idx, line.line);
        }
    } catch (...) {
        lines_.clear();
        lines_ = backup;
        throw std::runtime_error("Internal sorting function error. Stage: 3");
    }
}

void TextProcessor::addSingleLine(size_t index, const std::string &rawData) {
    parseIndexOrSetToLast_(index);

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
        lines_.insert(lines_.begin() + index, newLine);
    }
    catch (...) {
        deAllocSingleLine_(newLine);
        throw std::runtime_error("Internal error. Unable to add line to existing lines.");
    }
}

void TextProcessor::addManyLines(size_t index, const std::vector<std::string> &rawData) {
    parseIndexOrSetToLast_(index);
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
        lines_.reserve(linesToAdd.size());
        lines_.insert(lines_.begin() + index, linesToAdd.begin(), linesToAdd.end());
    }
    catch (...) {
        throw std::runtime_error("Unable to allocate space for new lines.");
    }
}

void TextProcessor::removeSingleLine(size_t index) {
    parseIndexOrThrow_(index);

    try {
        BaseLine *currentLine = lines_[index];
        lines_.erase(lines_.begin() + index);
        deAllocSingleLine_(currentLine);
    }
    catch (...) {
        throw std::runtime_error("Error removing line at index: " + std::to_string(index));
    }
}

void TextProcessor::removeManyLines(size_t indexStart, size_t indexEnd) {
    parseIndexRangeOrThrow_(indexStart, indexEnd);

    std::vector<BaseLine *> pointersToFree;

    try {
        // inclusive
        for (size_t i = indexStart; i <= indexEnd; ++i) {
            pointersToFree.push_back(lines_[i]);
        }
    }
    catch (const std::bad_alloc &) {
        throw std::runtime_error("Internal memory allocation error.");
    }

    try {
        lines_.erase(lines_.begin() + indexStart, lines_.begin() + indexEnd + 1);
    }
    catch (...) {
        throw std::runtime_error("Failed to remove lines. State should not have been changed.");
    }

    for (BaseLine *&line: pointersToFree) {
        deAllocSingleLine_(line);
    }
}

void TextProcessor::setBlock(size_t indexStart, size_t indexEnd) {
    parseIndexRangeOrThrow_(indexStart, indexEnd);

    block_.indexStart = indexStart;
    block_.indexEnd = indexEnd;

    try{
        // inclusive
        block_.vectorLinePtr.assign
                (lines_.begin() + block_.indexStart, lines_.begin() + block_.indexEnd + 1);
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
    block_.indexStart = Block::NPOS_;
    block_.indexEnd = Block::NPOS_;
}

const std::vector<BaseLine *> &TextProcessor::getBlock() const {
    if (!blockExists_()) {
        throw std::runtime_error("No block set.");
    }
    return block_.vectorLinePtr;
}


