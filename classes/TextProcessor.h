#ifndef TEXT_PROCESSOR_TEXTPROCESSOR_H
#define TEXT_PROCESSOR_TEXTPROCESSOR_H


#include "file_workers/IFileReader.h"
#include "file_workers/IFileWriter.h"
#include "line/LineParser.h"
#include "Config.h"


class TextProcessor final {
public: // TODO: MAKE PRIVATE
    IFileReader *fileReader_;
    IFileWriter *fileWriter_;

    std::vector<BaseLine*> lines;

public:
    explicit TextProcessor(IConfig *config) : fileReader_(config->getFileReader()),
                                              fileWriter_(config->getFileWriter()) {};

    TextProcessor(const TextProcessor&) = delete;
    TextProcessor(TextProcessor&&) = delete;
    TextProcessor& operator=(const TextProcessor&) = delete;
    TextProcessor& operator=(TextProcessor&&) = delete;

    void open(const std::string &fileName);

    void save();

    void saveAs(const std::string &fileName);

    ~TextProcessor();
};


#endif //TEXT_PROCESSOR_TEXTPROCESSOR_H
