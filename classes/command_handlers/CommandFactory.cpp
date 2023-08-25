#include "CommandFactory.h"

Command *CommandFactory::createCommand(const std::vector<std::string> &commandTokens) {
    Command *result = nullptr;

    if(commandTokens.empty()){
        throw std::runtime_error("Please provide a command.");
    }

    if (commandTokens.size() == 1) {
        const std::string &commandToken = commandTokens[0];

        if(commandToken == "save"){
            result = new SaveCommand();
        }
        else if(commandToken == "sort"){
            result = new SortCommand();
        }
        else if(commandToken == "unset_block"){
            result = new UnsetBlockCommand();
        }
        else if(commandToken == "undo"){
            result = new UndoCommand();
        }
        else if(commandToken == "print_open_files"){
            result = new PrintOpenFilesCommand();
        }
        else if(commandToken == "print"){
            result = new PrintCommand();
        }
        else if(commandToken == "print_centered"){
            result = new PrintCenteredCommand();
        }
        else if(commandToken == "print_block"){
            result = new PrintBlockCommand();
        }
        else if(commandToken == "print_block_centered"){
            result = new PrintBlockCenteredCommand();
        }
    }

    else if (commandTokens.size() == 2){
        const std::string &commandToken = commandTokens[0];
        const std::string &argOne = commandTokens[1];

        if (commandToken == "open"){
            result = new OpenCommand(argOne);
        }
        else if (commandToken == "save_as"){
            result = new SaveAsCommand(argOne);
        }
        else if (commandToken == "remove_line"){
            result = new RemoveLineCommand(InputParser::parseStringToUll(argOne));
        }
        else if (commandToken == "set_current_file"){
            result = new SetCurrentFileCommand(InputParser::parseStringToUll(argOne));
        }
        else if (commandToken == "close"){
            result = new CloseCommand(InputParser::parseStringToUll(argOne));
        }
        else if (commandToken == "to_upper"){
            result = new ToUpperCommand(InputParser::parseStringToUll(argOne));
        }
        else if (commandToken == "to_lower"){
            result = new ToLowerCommand(InputParser::parseStringToUll(argOne));
        }
        else if (commandToken == "trim_left"){
            result = new TrimLeftCommand(InputParser::parseStringToUll(argOne));
        }
        else if (commandToken == "trim_right"){
            result = new TrimRightCommand(InputParser::parseStringToUll(argOne));
        }
        else if (commandToken == "add_line"){
            result = new AddLineCommand(InputParser::parseStringToUll(argOne));
        }
        else if (commandToken == "add_lines_many"){
            result = new AddLinesManyCommand(InputParser::parseStringToUll(argOne));
        }
    }

    else if(commandTokens.size() == 3){
        const std::string &commandToken = commandTokens[0];
        const std::string &argOne = commandTokens[1];
        const std::string &argTwo = commandTokens[2];

        if(commandToken == "remove_lines_range"){
            result = new RemoveLinesRangeCommand(InputParser::parseStringToUll(argOne),
                                                 InputParser::parseStringToUll(argTwo));
        }
        else if(commandToken == "set_block"){
            result = new SetBlockCommand(InputParser::parseStringToUll(argOne),
                                         InputParser::parseStringToUll(argTwo));
        }
        else if(commandToken == "to_upper_range"){
            result = new ToUpperRangeCommand(InputParser::parseStringToUll(argOne),
                                             InputParser::parseStringToUll(argTwo));
        }
        else if(commandToken == "to_lower_range"){
            result = new ToLowerRangeCommand(InputParser::parseStringToUll(argOne),
                                             InputParser::parseStringToUll(argTwo));
        }
        else if(commandToken == "trim_left_range"){
            result = new TrimLeftRangeCommand(InputParser::parseStringToUll(argOne),
                                              InputParser::parseStringToUll(argTwo));
        }
        else if(commandToken == "trim_right_range"){
            result = new TrimRightRangeCommand(InputParser::parseStringToUll(argOne),
                                               InputParser::parseStringToUll(argTwo));
        }
    }

    return result;
}
