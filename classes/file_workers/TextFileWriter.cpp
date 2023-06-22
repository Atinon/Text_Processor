#include "TextFileWriter.h"
#include "../line/BaseLine.h"

const std::string &TextFileWriter::getFileName() const {
    return fileName_;
}

void TextFileWriter::setFileName(const std::string &fileName) {
    fileName_ = fileName;
}

void TextFileWriter::writeFileContent(const std::vector<BaseLine*> &vec) {
    if(fileName_.empty()){
        throw std::runtime_error("Please provide a file name to save to.");
    }

    if(fileName_.substr(fileName_.find_last_of('.') + 1) != "txt"){
        throw std::runtime_error("Please provide a file of .txt format.");
    }

    if(vec.empty()){
        throw std::runtime_error("Nothing to write to file.");
    }

    std::ofstream out(fileName_);

    if(!out.is_open()){
        throw std::runtime_error("Failed to open the file: " + fileName_);
    }

    try{
        for (BaseLine* currentLine : vec) {
            out << currentLine->getStringValue() << '\n';
        }
    }
    catch(const std::ofstream::failure&){
        out.close();
        throw std::runtime_error("File writing error. File could be corrupt.");
    }
    catch(const std::bad_alloc&){
        out.close();
        throw std::runtime_error("Memory allocation error.");
    }
    catch(...){
        out.close();
        throw std::runtime_error("Internal error when writing. Not yet accounted for.");
    }

    out.close();
}

