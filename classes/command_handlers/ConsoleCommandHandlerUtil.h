#ifndef TEXT_PROCESSOR_CONSOLECOMMANDHANDLERUTIL_H
#define TEXT_PROCESSOR_CONSOLECOMMANDHANDLERUTIL_H

#include <string>
#include <vector>
#include <iostream>

struct CommandInfo {
    std::string name;
    std::string explanation;
};

static const std::vector<CommandInfo> ONE_ARG_COMMAND_INFO = {
        // OneArgCommands
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
        // TwoArgCommands
        {"remove_lines_range *indexStart* *indexEnd*", "removes lines within range"},
        {"set_block *indexStart* *indexEnd*","defines a special block within range"},
        {"to_upper_range *indexStart* *indexEnd*", "make text upper-case within range"},
        {"to_lower_range *indexStart* *indexEnd*", "make text lower-case within range"},
        {"trim_left_range *indexStart* *indexEnd*", "trim empty symbols from left within range"},
        {"trim_right_range *indexStart* *indexEnd*", "trim empty symbols from right within range"},
};


static const std::vector<CommandInfo> NO_ARG_COMMAND_INFO = {
        // NoArgCommands
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


void printCommandInfo();






#endif //TEXT_PROCESSOR_CONSOLECOMMANDHANDLERUTIL_H
