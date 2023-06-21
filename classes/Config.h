#ifndef TEXT_PROCESSOR_CONFIG_H
#define TEXT_PROCESSOR_CONFIG_H


#include "file_workers/IFileReader.h"
#include "file_workers/IFileWriter.h"

class IConfig {
public:
    virtual IFileReader* getFileReader() = 0;

    virtual IFileWriter* getFileWriter() = 0;

    virtual ~IConfig() = default;
};


class DefaultConfig : public IConfig {
private:
    IFileReader *fileReader_;
    IFileWriter *fileWriter_;

public:
    DefaultConfig();

    IFileReader *getFileReader() override;

    IFileWriter *getFileWriter() override;

    ~DefaultConfig() override;
};


#endif //TEXT_PROCESSOR_CONFIG_H
