#ifndef TEXT_PROCESSOR_TEXTPROCESSOR_H
#define TEXT_PROCESSOR_TEXTPROCESSOR_H


#include "file_workers/IFileReader.h"
#include "file_workers/IFileWriter.h"
#include "line/LineParser.h"
#include "Config.h"
#include "line/LineComparator.h"



class TextProcessor final {
private: // TODO: MAKE PRIVATE
    IFileReader *fileReader_;
    IFileWriter *fileWriter_;

    std::vector<BaseLine*> lines_;

    static void deAllocSingleLine_(BaseLine *&line);
    void deAllocAllLines_();

    void parseIndexOrSetToLast_(size_t &indexRef);

    void parseIndexOrThrow_(size_t index);

    void parseIndexRangeOrThrow_(size_t indexStart, size_t indexEnd);

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

    const std::vector<BaseLine*> &getLines() const;

    void sort();

    void addSingleLine(size_t index, const std::string &rawData);

    void addManyLines(size_t index, const std::vector<std::string> &rawData);

    void removeSingleLine(size_t index);

    void removeManyLines(size_t indexStart, size_t indexEnd);

    ~TextProcessor();
};


#endif //TEXT_PROCESSOR_TEXTPROCESSOR_H
