#include "ConsoleCommandHandler.h"


const std::string ConsoleCommandHandler::EXIT_COMMAND_ = "exit";

const std::string ConsoleCommandHandler::HELP_COMMAND_ = "help";

const std::string ConsoleCommandHandler::COMMAND_SUCCESS_MSG_ = "Command successful.";

const std::string ConsoleCommandHandler::INVALID_COMMAND_MSG_ = "Invalid Command.";

void ConsoleCommandHandler::startConsoleUi() {
    std::string command;

    std::cout << "Text Processor console UI started..." << std::endl;
    std::cout << "Please enter a command below: " << std::endl;
    do {
        std::cout << ">> ";
        std::getline(std::cin, command);
        handleCommand(command);
    } while (command != EXIT_COMMAND_);
    promptForSaveIfFilesOpened();
    std::cout << "Exiting..." << std::endl;
}

void ConsoleCommandHandler::handleCommand(const std::string &command) {
    std::vector<std::string> commandTokens;
    InputParser::basicTokenizingFunction(command, commandTokens);

    if (commandTokens.empty()) {
        std::cout << "Please provide a command." << std::endl;
        return;
    }

    if (commandTokens.size() == 1) {
        if (commandTokens[0] == EXIT_COMMAND_) {
            return;
        }

        if(commandTokens[0] == HELP_COMMAND_){
            printCommandInfo();
            return;
        }
    }

    else if(commandTokens.size() == 2){
        const std::string &commandToken = commandTokens[0];
        const std::string &argOne = commandTokens[1];
        try{
            if(commandToken == "add_macro"){
                addMacroAndFillFromConsole(argOne);
                std::cout << "Macro created successfully." << std::endl;
                return;
            }
            else if (commandToken == "do_macro"){
                executeMacro(argOne);
                std::cout << "Macro executed successfully." << std::endl;
                return;
            }
            else if(commandToken == "remove_macro"){
                removeMacro(argOne);
                std::cout << "Macro removed successfully." << std::endl;
                return;
            }
        }
        catch(const std::exception &e){
            std::cout << e.what() << std::endl;
            return;
        }
    }

    executeCommand(commandTokens);
}

void ConsoleCommandHandler::executeMacro(const std::string &macroName) {
    for (const Macro &m : macros_) {
        if(m.name == macroName){
            for(const std::string &commandName : m.commands){
                std::cout << "-- Executing Command: [" << commandName << ']' << std::endl;
                handleCommand(commandName);
            }
            return;
        }
    }
    throw std::runtime_error("No such macro found.");
}

void ConsoleCommandHandler::addMacroAndFillFromConsole(const std::string &macroName) {
    for (const Macro &m : macros_) {
        if(m.name == macroName){
            throw std::runtime_error("Macro with this name already exists.");
        }
    }
    std::cout << "Enter commands line by line (blank line to stop): " << std::endl;
    std::vector<std::string> userCommands = InputReceiver::getMultiLineInput();

    macros_.emplace_back(macroName, userCommands);
}

void ConsoleCommandHandler::removeMacro(const std::string &macroName) {
    for (int i = 0; i < macros_.size(); ++i) {
        if(macros_[i].name == macroName){
            macros_.erase(macros_.begin() + i);
            return;
        }
    }
    throw std::runtime_error("No macro exists with this name.");
}

void ConsoleCommandHandler::promptForSaveIfFilesOpened() {
    std::vector<std::string> openedFileNames = textProcessor_->getOpenedFileNames();
    for (size_t i = 0; i < openedFileNames.size(); ++i) {
        std::string input;
        std::cout
        << "File: " << openedFileNames[i] << " is open, would you like to save changes to it? (y/n)" << std::endl;
        do{
            input = InputReceiver::getSingleLineInput();
            if(input == "y"){
                std::cout << "Attempting to execute saving commands..." << std::endl;
                handleCommand("set_current_file " + std::to_string(i));
                handleCommand("save");
            }
        }
        while(input != "y" && input != "n");
    }
}

void ConsoleCommandHandler::executeCommand(const std::vector<std::string> &commandTokens) {
    if(!textProcessor_){
        std::cout << "Internal Error. TextProcessor is a nullptr." << std::endl;
        return;
    }
    Command *command = nullptr;
    try{
        command = CommandFactory::createCommand(commandTokens);
        if(!command){
            std::cout << INVALID_COMMAND_MSG_ << std::endl;
            return;
        }
        command->execute(*textProcessor_);
//        std::cout << COMMAND_SUCCESS_MSG_ << std::endl;
        delete command;
    }
    catch(const std::exception &e){
        std::cout << e.what() << std::endl;
        delete command;
    }
}
