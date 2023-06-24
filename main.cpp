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
	 * add_lines_many idxToAddAt
	 * sort
	 * save_as fileName
	 * add_macro macroName
	 * do_macro macroName
	 * open newFileName
	 * print_open_files
	 * set_current_file fileIdx
	 * ... and more
	 * All commands for ConsoleCommandHandler can be seen in the respective header file
	 * There are some methods which are not implemented as console commands yet,
	 * but are existent as methods for the respective classes and should be functioning properly.
	 * */

    /* P.S. : If there is an issue with CMake versions, open the CMakeLists.txt file and edit the line :
    *         cmake_minimum_required(VERSION 3.25)
    *         to fit your current version.
    */
}
