#include <algorithm>
#include "TextProcessor.h"

TextProcessor::~TextProcessor() {
    deAllocAllLines_();
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
        lines_ = LineParser::createFromString(rawData);
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
        throw std::runtime_error("Internal sorting function error.");
    }

    std::vector<BaseLine *> backup;
    try{
        backup = lines_;
    }
    catch(...){
        throw std::runtime_error("Internal sorting function error.");
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
        throw std::runtime_error("Internal sorting function error.");
    }
}


