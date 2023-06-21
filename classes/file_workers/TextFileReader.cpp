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

    if(fileName_.empty()){
        throw std::runtime_error("Please provide a file name to open.");
    }

    // if '.' is not found, find_last_of returns string::npos which is max value for size_t type
    // adding +1 to it reverts it back to 0, so theoretically, there shouldn't be out of bound operations
    if(fileName_.substr(fileName_.find_last_of('.') + 1) != "txt"){
        throw std::runtime_error("Please provide a file of .txt format.");
    }

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

