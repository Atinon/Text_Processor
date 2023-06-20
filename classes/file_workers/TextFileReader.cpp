#include "TextFileReader.h"

const std::string &TextFileReader::getFileName() {
    return fileName_;
}

void TextFileReader::setFileName(const std::string &fileName) {
    fileName_ = fileName;
}

std::vector<std::string> TextFileReader::readFileContent() {
    std::vector<std::string> result;
    std::string currentLine;
    std::fstream in(fileName_);

    if(!in.is_open()){
        throw std::runtime_error("Failed to open the file: " + fileName_);
    }

    while(getline(in, currentLine, '\n')){
        try{
            result.push_back(currentLine);
        }
        catch(const std::bad_alloc&){
            in.close();
            result.clear();
            throw std::runtime_error("File too big to load. File name: " + fileName_);
        }
    }

    in.close();
    return result;
}

