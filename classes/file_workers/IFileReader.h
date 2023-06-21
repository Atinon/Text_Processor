#ifndef TEXT_PROCESSOR_IFILEREADER_H
#define TEXT_PROCESSOR_IFILEREADER_H

#include <vector>
#include <string>

class IFileReader {
public:
    virtual std::vector<std::string> readFileContent() = 0;

    virtual const std::string &getFileName() const = 0;

    virtual void setFileName(const std::string &fileName) = 0;

    virtual ~IFileReader() = default;
};


#endif //TEXT_PROCESSOR_IFILEREADER_H
