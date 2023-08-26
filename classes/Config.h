#ifndef TEXT_PROCESSOR_CONFIG_H
#define TEXT_PROCESSOR_CONFIG_H


#include "file_workers/IFileReader.h"
#include "file_workers/IFileWriter.h"

/**
 * @class IConfig
 * @brief Interface for providing file reader and writer instances.
 *
 * This interface defines the methods for obtaining instances of IFileReader and IFileWriter.
 * It is designed for dependency injection and allows flexibility in providing different implementations
 * of file reading and writing strategies.
 */
class IConfig {
public:
    virtual IFileReader* getFileReader() = 0;

    virtual IFileWriter* getFileWriter() = 0;

    virtual ~IConfig() = default;
};

/**
 * @class DefaultConfig
 * @brief Default implementation of the IConfig interface for text files using concrete reader and writer instances.
 *
 * This class provides a default implementation of the IConfig interface, creating and returning instances
 * of TextFileReader and TextFileWriter for file reading and writing operations.
 */
class DefaultConfig : public IConfig {
private:
    IFileReader *fileReader_;
    IFileWriter *fileWriter_;

public:
    /**
     * @brief Default constructor.
     *
     * Constructs a DefaultConfig object with TextFileReader and TextFileWriter instances.
     */
    DefaultConfig();

    IFileReader *getFileReader() override;

    IFileWriter *getFileWriter() override;

    /**
    * @brief Destructor.
    *
    * Destructor responsible for cleaning up resources allocated by the DefaultConfig object.
    * In this case TextFileReader and TextFileWriter.
    */
    ~DefaultConfig() override;
};


#endif //TEXT_PROCESSOR_CONFIG_H
