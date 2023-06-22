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

    try{
        fileWriter_->writeFileContent(lines_);
    }
    catch(...){
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
    if(!lines_.empty()){
        for (BaseLine *& line : lines_) {
            deAllocSingleLine_(line);
        }
    }
}


