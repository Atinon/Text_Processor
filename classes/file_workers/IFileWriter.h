#ifndef TEXT_PROCESSOR_IFILEWRITER_H
#define TEXT_PROCESSOR_IFILEWRITER_H

#include <string>
#include <vector>

class BaseLine;

/**
 * @class IFileWriter
 * @brief Interface for file writing operations.
 *
 * This interface defines the basic contract for classes that perform file writing operations.
 * It includes methods for writing a given vector of BaseLine pointers to a file using polymorphism
 * and managing the file name.
 */
class IFileWriter {
public:
    virtual void writeFileContent(const std::vector<BaseLine*> &vec) = 0;

    virtual const std::string &getFileName() const = 0;

    virtual void setFileName(const std::string &fileName) = 0;

    virtual ~IFileWriter() = default;
};


#endif //TEXT_PROCESSOR_IFILEWRITER_H
