#ifndef TEXT_PROCESSOR_TEXTPROCESSOR_H
#define TEXT_PROCESSOR_TEXTPROCESSOR_H


#include "file_workers/IFileReader.h"
#include "file_workers/IFileWriter.h"
#include "Config.h"

class TextProcessor final {
public: // TODO: MAKE PRIVATE
    IFileReader *fileReader_;
    IFileWriter *fileWriter_;

public:
    explicit TextProcessor(IConfig *config) : fileReader_(config->getFileReader()),
                                              fileWriter_(config->getFileWriter()) {};
};


#endif //TEXT_PROCESSOR_TEXTPROCESSOR_H
