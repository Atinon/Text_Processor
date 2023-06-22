#include "ConsoleCommandHandler.h"

const char* ConsoleCommandHandler::SPACE_DELIM_ = " ";
const std::string ConsoleCommandHandler::EXIT_COMMAND_ = "exit";

void ConsoleCommandHandler::basicTokenizingFunction_(const std::string &command, std::vector<std::string> &vectorRef) {
    char* dup = strdup(command.c_str());
    char* tokPtr = strtok(dup, SPACE_DELIM_);
    while(tokPtr != nullptr){
        vectorRef.emplace_back(tokPtr);
        tokPtr = strtok(nullptr, SPACE_DELIM_);
    }
    delete[] dup;
}

void ConsoleCommandHandler::startConsoleUi() {
    std::string command;

    std::cout << "Text Processor console UI started..." << std::endl;
    std::cout << "Please enter a command below: " << std::endl;
    do {
        std::cout << ">> ";
        std::getline(std::cin, command);
//        std::cout << std::endl;
        handleCommand(command);
    }
    while(command != EXIT_COMMAND_);
    std::cout << "Exiting..." << std::endl;
}

void ConsoleCommandHandler::handleCommand(const std::string &command) {
    std::vector<std::string> commandTokens;
    basicTokenizingFunction_(command, commandTokens);

    if(commandTokens.empty()){
        std::cout <<"Please provide a command." << std::endl;
        return;
    }

    if(commandTokens.size() == 1){
        if(commandTokens[0] == EXIT_COMMAND_){
            return;
        }

        handleNoArgCommand_(commandTokens);

        return;
    }

    else if(commandTokens.size() == 2){
        handleOneArgCommand_(commandTokens);
        return;
    }

    // to add other commands...


    std::cout << "Invalid command." << std::endl;
}

void ConsoleCommandHandler::handleNoArgCommand_(const std::vector<std::string> &commandTokens) {
    // textProcessorNoArgsCommandsVoid_
    for (const Command<TextProcessor, void> &c: textProcessorNoArgsCommandsVoid_) {
        if(c.stringValue == commandTokens[0]){
            try{
                (textProcessor_->*c.func)();
                std::cout << "Command successful." << std::endl;
                return;
            }
            catch(const std::runtime_error &e){
                std::cout << e.what() << std::endl;
                return;
            }
        }
    }
    std::cout << "Invalid command." << std::endl;
}

void ConsoleCommandHandler::handleOneArgCommand_(const std::vector<std::string> &commandTokens) {
    // textProcessorOneArgCommandsVoid_
    for (const Command<TextProcessor, void, const std::string&> &c: textProcessorOneArgCommandsVoid_) {
        if(c.stringValue == commandTokens[0]){
            try{
                (textProcessor_->*c.func)(commandTokens[1]);
                std::cout << "Command successful." << std::endl;
                return;
            }
            catch(const std::runtime_error &e){
                std::cout << e.what() << std::endl;
                return;
            }
        }
    }
    std::cout << "Invalid command." << std::endl;
}
