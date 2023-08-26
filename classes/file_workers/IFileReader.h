#ifndef TEXT_PROCESSOR_IFILEREADER_H
#define TEXT_PROCESSOR_IFILEREADER_H

#include <vector>
#include <string>

/**
 * @class IFileReader
 * @brief Interface for file reading operations.
 *
 * This interface defines the basic contract for classes that perform file reading operations.
 * It includes methods for reading file content and producing a vector of strings, and managing the file name.
 */
class IFileReader {
public:
    /**
    * @brief Read the content of the file and return it as a vector of strings representing each line from the file.
    * @return A vector containing the lines of the file content.
    */
    virtual std::vector<std::string> readFileContent() = 0;

    virtual const std::string &getFileName() const = 0;

    virtual void setFileName(const std::string &fileName) = 0;

    virtual ~IFileReader() = default;
};


#endif //TEXT_PROCESSOR_IFILEREADER_H
