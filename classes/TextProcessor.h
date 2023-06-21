#ifndef TEXT_PROCESSOR_TEXTPROCESSOR_H
#define TEXT_PROCESSOR_TEXTPROCESSOR_H


#include "file_workers/IFileReader.h"
#include "Config.h"

class TextProcessor final {
public: // TODO: MAKE PRIVATE
    IFileReader *fileReader_;

public:
    explicit TextProcessor(IConfig *config) : fileReader_(config->getFileReader()) {};
};


#endif //TEXT_PROCESSOR_TEXTPROCESSOR_H
