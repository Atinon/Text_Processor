#ifndef TEXT_PROCESSOR_TEXTPROCESSOR_H
#define TEXT_PROCESSOR_TEXTPROCESSOR_H


#include "file_workers/IFileReader.h"
#include "file_workers/IFileWriter.h"
#include "line/LineParser.h"
#include "Config.h"
#include "line/LineComparator.h"


/**
 * This is the main class that fits all of the components together and provides complete methods.
 */
class TextProcessor final {
private:
    const static size_t NPOS_;
    const static short UNDO_STACK_LIMIT_;

    /**
 * This struct represents opened files.
 */
    struct FileData {
        std::string fileName;
        std::vector<BaseLine*> lines_;
    };

    struct Block {
        const static size_t NPOS_ = -1; // remove later and use TextProcessor::NPOS_ instead
        size_t fileId;
        size_t indexStart;
        size_t indexEnd;
        std::vector<BaseLine*> vectorLinePtr;
        Block() : fileId(NPOS_), indexStart(NPOS_), indexEnd(NPOS_){};
    };

    struct UndoHistory {
        size_t fileId;
        std::vector<BaseLine*> previousState;
        UndoHistory() : fileId(NPOS_){};
    };

    IFileReader *fileReader_;
    IFileWriter *fileWriter_;

    std::vector<FileData> files_;
    size_t currentFileIndex_;

    Block block_;

    std::vector<UndoHistory> undoStack_; // will be used as a stack

    static void deAllocSingleLine(BaseLine *&line);

    static void deAllocAllLines(std::vector<BaseLine *> &vectorRef);

    static std::vector<BaseLine *> getDeepCopyLinesVector(const std::vector<BaseLine *> &lines);

    void checkIfAnyOpenFilesOrThrow() const;

    std::vector<BaseLine *> &getCurrentLinesRefOrThrow();

    const std::vector<BaseLine *> &getCurrentLinesConstRefOrThrow() const;

    std::string &getCurrentFileNameRefOrThrow();

    bool blockExists() const;

    bool blockForCurrentFile() const;

    template<typename T>
    void parseIndexOrSetToLast(size_t &indexRef, const std::vector<T> &vec);

    template<typename T>
    void parseIndexOrThrow(size_t index, const std::vector<T> &vec);

    template<typename T>
    void parseIndexRangeOrThrow(size_t indexStart, size_t indexEnd, const std::vector<T> &vec);

    void pushCurrentStateToStack();

    void clearUndoStack();

    void pushCurrentStateToStackOrClearOnFailure();

    void removeOldestFromUndoStackIfLimitReached();

    void changeCasingSingle(size_t index, bool toUpper);
    size_t changeCasingMulti(size_t indexStart, size_t indexEnd , bool toUpper);

    void trimLineSingle(size_t index, bool trimLeft);
    size_t trimLineMulti(size_t indexStart, size_t indexEnd , bool trimLeft);

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

    void toUpperSingleLine(size_t index);
    void toLowerSingleLine(size_t index);
    void trimLeftSingleLine(size_t index);
    void trimRightSingleLine(size_t index);

    void toUpperManyLines(size_t indexStart, size_t indexEnd);
    void toLowerManyLines(size_t indexStart, size_t indexEnd);
    void trimLeftManyLines(size_t indexStart, size_t indexEnd);
    void trimRightManyLines(size_t indexStart, size_t indexEnd);

    // TODO: add the methods for block too

    std::vector<std::string> getOpenedFileNames();

    void setCurrentFile(size_t index);

    void closeFile(size_t index);

    void undo();

    ~TextProcessor();
};


#endif //TEXT_PROCESSOR_TEXTPROCESSOR_H
