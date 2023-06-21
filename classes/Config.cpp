#include "Config.h"
#include "file_workers/TextFileReader.h"
#include "file_workers/TextFileWriter.h"

DefaultConfig::DefaultConfig() {
    try {
        fileReader_ = new TextFileReader();
    }
    catch (const std::bad_alloc &) {
        fileReader_ = nullptr;
    }

    try {
        fileWriter_ = new TextFileWriter();
    }
    catch (const std::bad_alloc &) {
        fileWriter_ = nullptr;
    }
}

IFileReader *DefaultConfig::getFileReader() {
    return fileReader_;
}

IFileWriter *DefaultConfig::getFileWriter() {
    return fileWriter_;
}

DefaultConfig::~DefaultConfig() {
    delete fileReader_;
    delete fileWriter_;
}
