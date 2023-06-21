#ifndef TEXT_PROCESSOR_TEXTFILEWRITER_H
#define TEXT_PROCESSOR_TEXTFILEWRITER_H


#include "IFileWriter.h"
#include <fstream>

class TextFileWriter: public IFileWriter {
private:
    std::string fileName_;

public:
    TextFileWriter() = default;

    explicit TextFileWriter(const std::string &fileName) : fileName_(fileName) {};

    const std::string &getFileName() const override;

    void setFileName(const std::string &fileName) override;

    void writeFileContent(const std::vector<BaseLine*> &vec) override;

    ~TextFileWriter() override = default;
};


#endif //TEXT_PROCESSOR_TEXTFILEWRITER_H
