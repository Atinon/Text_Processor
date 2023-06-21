#ifndef TEXT_PROCESSOR_IFILEWRITER_H
#define TEXT_PROCESSOR_IFILEWRITER_H

#include <string>
#include <vector>

class BaseLine;

class IFileWriter {
public:
    virtual void writeFileContent(const std::vector<BaseLine*> &vec) = 0;

    virtual const std::string &getFileName() const = 0;

    virtual void setFileName(const std::string &fileName) = 0;

    virtual ~IFileWriter() = default;
};


#endif //TEXT_PROCESSOR_IFILEWRITER_H
