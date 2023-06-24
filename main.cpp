#include <iostream>
#include "classes/Config.h"
#include "classes/TextProcessor.h"
#include "classes/command_handlers/ConsoleCommandHandler.h"

using namespace std;


int main(){
    DefaultConfig defaultConfig;
    TextProcessor textProcessor(&defaultConfig);

    ConsoleCommandHandler commandHandler(&textProcessor);

    commandHandler.startConsoleUi();

    /* example work-flow:
     * open filename
     * print
     * remove_lines_range idxStart idxEnd
     * undo
     * set_block idxStart idxEnd
     * print_block_centered
     * add_lines_many
     * add_macro
     * do_macro
     * open newFileName
     * print_open_files
     * set_current_file fileIdx
     * ... and more
     * All commands for ConsoleCommandHandler can be seen in the respective header file
     * There are some methods which are not implemented as console commands yet,
     * but are existent as methods for the respective classes and should be functioning properly.
     * */
}
