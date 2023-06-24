#ifndef TEXT_PROCESSOR_TEXTPROCESSOR_H
#define TEXT_PROCESSOR_TEXTPROCESSOR_H


#include "file_workers/IFileReader.h"
#include "file_workers/IFileWriter.h"
#include "line/LineParser.h"
#include "Config.h"
#include "line/LineComparator.h"



class TextProcessor final {
private:
    struct Block{
        const static size_t NPOS_ = -1;
        size_t indexStart;
        size_t indexEnd;
        std::vector<BaseLine*> vectorLinePtr;
        Block() : indexStart(NPOS_), indexEnd(NPOS_){};
    };

    IFileReader *fileReader_;
    IFileWriter *fileWriter_;

    std::vector<BaseLine*> lines_;

    Block block_;

    static void deAllocSingleLine_(BaseLine *&line);

    void deAllocAllLines_();

    bool blockExists_() const;

    void parseIndexOrSetToLast_(size_t &indexRef);

    void parseIndexOrThrow_(size_t index);

    void parseIndexRangeOrThrow_(size_t indexStart, size_t indexEnd);

public:
    explicit TextProcessor(IConfig *config);

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

    void setBlock(size_t indexStart, size_t indexEnd);

    void unsetBlock();

    const std::vector<BaseLine*> &getBlock() const; // TODO: added print and print_centered so far

    // TODO: ADD toUpper, toLower, trimLeft, trimRight to methods!! Also for block

    ~TextProcessor();
};


#endif //TEXT_PROCESSOR_TEXTPROCESSOR_H
