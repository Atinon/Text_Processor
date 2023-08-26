#ifndef TEXT_PROCESSOR_TEXTPROCESSOR_H
#define TEXT_PROCESSOR_TEXTPROCESSOR_H


#include "file_workers/IFileReader.h"
#include "file_workers/IFileWriter.h"
#include "line/LineParser.h"
#include "Config.h"
#include "line/LineComparator.h"


/**
 * @class TextProcessor
 * @brief The main class that orchestrates and manages the processing of text files.
 *
 * This class acts as the core component that ties together various functionalities for processing and managing
 * text files. It maintains information about opened files, blocks of lines, undo history, and provides methods for
 * manipulating and interacting with these components.
 */
class TextProcessor final {
private:
    const static size_t NPOS_;
    const static short UNDO_STACK_LIMIT_;

    /**
     * @struct FileData
     * @brief Represents information about opened files.
     *
     * This structure holds details about an opened file, including its file name and a vector of BaseLine pointers
     * representing the lines in the file.
     */
    struct FileData {
        std::string fileName;
        std::vector<BaseLine*> lines_;
    };

    /**
    * @struct Block
    * @brief Represents a block of lines within a file.
    *
    * This structure represents a block of lines within a file, identified by its starting and ending indices. It
    * also holds a vector of BaseLine pointers for the lines within the block.
    */
    struct Block {
        const static size_t NPOS_ = -1; // can use TextProcessor::NPOS_
        size_t fileId;
        size_t indexStart;
        size_t indexEnd;
        std::vector<BaseLine*> vectorLinePtr;
        Block() : fileId(NPOS_), indexStart(NPOS_), indexEnd(NPOS_){};
    };

    /**
    * @struct UndoHistory
    * @brief Represents a snapshot of a file's previous state for undo functionality.
    *
    * This structure stores information about a file's previous state, including its file ID and a vector of
    * BaseLine pointers(clones) representing the lines in the previous state. It is used for undo operations.
    */
    struct UndoHistory {
        size_t fileId;
        std::vector<BaseLine*> previousState;
        UndoHistory() : fileId(NPOS_){};
    };

    IFileReader *fileReader_; ///< Pointer to the file reader implementation for reading file contents.
    IFileWriter *fileWriter_; ///< Pointer to the file writer implementation for writing file contents.

    std::vector<FileData> files_; ///< Collection of opened files and their associated lines.
    size_t currentFileIndex_; ///< Index indicating the currently active file in the 'files_' collection.

    Block block_; ///< A data structure representing a block of lines within a file

    std::vector<UndoHistory> undoStack_; ///< Stack used to keep track of undo history for line modifications.

    static void deAllocSingleLine(BaseLine *&line);

    static void deAllocAllLines(std::vector<BaseLine *> &vectorRef);

    static std::vector<BaseLine *> getDeepCopyLinesVector(const std::vector<BaseLine *> &lines);

    void checkIfAnyOpenFilesOrThrow() const;

    /**
    * @brief Returns a reference to the vector with lines of the current open file.
    * @throw std::runtime_error If not file is open
    */
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

    const std::vector<BaseLine*> &getBlock() const;

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
