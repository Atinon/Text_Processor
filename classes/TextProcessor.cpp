#include "TextProcessor.h"

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
        lines = LineParser::createFromString(rawData);
    }
    catch (const std::invalid_argument &e) {
        throw std::runtime_error(e.what());
    }
    catch (...) {
        throw;
    }
}

void TextProcessor::save() {
    try{
        fileWriter_->writeFileContent(lines);
    }
    catch(...){
        throw;
    }
}

void TextProcessor::saveAs(const std::string &fileName) {
    fileWriter_->setFileName(fileName);
    save();
}

TextProcessor::~TextProcessor() {
    for (BaseLine* line : lines) {
        delete line;
    }
}
