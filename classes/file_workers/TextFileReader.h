#ifndef TEXT_PROCESSOR_TEXTFILEREADER_H
#define TEXT_PROCESSOR_TEXTFILEREADER_H


#include "IFileReader.h"
#include <fstream>

class TextFileReader : public IFileReader {
private:
    std::string fileName_;

public:
    TextFileReader() = default;

    explicit TextFileReader(const std::string &fileName) : fileName_(fileName) {};

    const std::string &getFileName() const override;

    void setFileName(const std::string &fileName) override;

    std::vector<std::string> readFileContent() override;

    ~TextFileReader() override = default;
};


#endif //TEXT_PROCESSOR_TEXTFILEREADER_H
