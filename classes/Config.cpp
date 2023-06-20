#include "Config.h"
#include "file_workers/TextFileReader.h"

DefaultConfig::DefaultConfig() {
    try {
        fileReader_ = new TextFileReader();
    }
    catch (const std::bad_alloc &) {
        fileReader_ = nullptr;
    }
}

IFileReader *DefaultConfig::getFileReader() {
    return fileReader_;
}

DefaultConfig::~DefaultConfig() {
    delete fileReader_;
}
