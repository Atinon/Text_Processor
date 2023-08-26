#ifndef TEXT_PROCESSOR_COMMANDUTIL_H
#define TEXT_PROCESSOR_COMMANDUTIL_H

#include <iostream>
#include <vector>
#include <cstring>
#include "../line/BaseLine.h"

/**
 * @class Printer
 * @brief Utility class for printing and formatting tasks.
 *
 * This class provides static methods for printing different types of information, including lines, file names,
 * and command information. It also includes utility methods for determining the maximum line width and
 * obtaining a string representation of a line's type.
 */
class Printer {
public:
    static size_t getMaxLineWidth(const std::vector<BaseLine *> &lines);

    static std::string getLineTypeString(const BaseLine &line);

    static void printLinesRegular(const std::vector<BaseLine *> &lines);

    static void printLinesCentered(const std::vector<BaseLine *> &lines);

    static void printFileNames(const std::vector<std::string> &names);

    static void printCommandInfo();
};

/**
 * @class InputReceiver
 * @brief Utility class for receiving user input.
 *
 * This class provides static methods for receiving user input, both single-line and multi-line.
 */
class InputReceiver {
public:
    static std::string getSingleLineInput();

    static std::vector<std::string> getMultiLineInput();
};

/**
 * @class InputParser
 * @brief Utility class for parsing and tokenizing user input.
 *
 * This class provides static methods for parsing strings and tokenizing commands.
 */
class InputParser {
public:
    static size_t parseStringToUll(const std::string &stringValue);

    static void basicTokenizingFunction(const std::string &command, std::vector<std::string> &vectorRef);
};

/**
 * @struct CommandInfo
 * @brief Utility struct containing the name of a command and a brief explanation.
 *
 * This class provides information about commands and is used in a vector, after which
 * appropriate information if printed to the user.
 */
struct CommandInfo {
    std::string name;
    std::string explanation;
};

static const std::vector<CommandInfo> ONE_ARG_COMMAND_INFO = {
        {"open *filename*", "open a file at work directory or full path"},
        {"save_as *filename*", "open a file at work directory or full path"},
        {"remove_line *lineIndex*", "remove a line at index"},
        {"set_current_file *fileIndex*", "set current working file to one with index"},
        {"close *fileIndex*", "close opened file with index"},
        {"to_upper *lineIndex*", "make line text upper-case at index"},
        {"to_lower *lineIndex*", "make line text lower-case at index"},
        {"trim_left *lineIndex*", "trim line empty symbols from left at index"},
        {"trim_right *lineIndex*", "trim line empty symbols from right at index"},
        {"add_line *indexToInsertAt*", "add line at index. Prompt will appear to enter text"},
        {"add_lines_many *indexToInsertAt*", "add many lines at index. Prompt will appear to enter text"},
        {"add_macro *macroName*", "create a series of commands under a name. Prompt will appear"},
        {"do_macro *macroName*", "execute series of commands stored under a name"},
        {"remove_macro *macroName*", "remove macro from saved macros"},
};

static const std::vector<CommandInfo> TWO_ARG_COMMAND_INFO = {
        {"remove_lines_range *indexStart* *indexEnd*", "removes lines within range"},
        {"set_block *indexStart* *indexEnd*","defines a special block within range"},
        {"to_upper_range *indexStart* *indexEnd*", "make text upper-case within range"},
        {"to_lower_range *indexStart* *indexEnd*", "make text lower-case within range"},
        {"trim_left_range *indexStart* *indexEnd*", "trim empty symbols from left within range"},
        {"trim_right_range *indexStart* *indexEnd*", "trim empty symbols from right within range"},
};


static const std::vector<CommandInfo> NO_ARG_COMMAND_INFO = {
        {"print_open_files", "prints all open files and their indexes"},
        {"print", "prints current opened file content"},
        {"print_centered", "prints current opened file content, but centered"},
        {"print_block", "prints current defined block"},
        {"print_block_centered", "prints current defined block, but centered"},
        {"sort", "sorts currently opened file based on predefined criteria"},
        {"save", "saves changes to currently opened file"},
        {"undo", "un-does the last file editing operation. keeps up to 3 operations"},
        {"unset_block", "un-sets the currently defined block"},
};

#endif //TEXT_PROCESSOR_COMMANDUTIL_H
