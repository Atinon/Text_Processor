#ifndef TEXT_PROCESSOR_CONFIG_H
#define TEXT_PROCESSOR_CONFIG_H


#include "file_workers/IFileReader.h"

class IConfig {
public:
    virtual IFileReader* getFileReader() = 0;

    virtual ~IConfig() = default;
};


class DefaultConfig : public IConfig {
private:
    IFileReader *fileReader_;

public:
    DefaultConfig();

    IFileReader *getFileReader() override;

    ~DefaultConfig() override;
};


#endif //TEXT_PROCESSOR_CONFIG_H
