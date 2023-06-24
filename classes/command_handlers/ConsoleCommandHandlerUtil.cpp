#include "ConsoleCommandHandlerUtil.h"

void printCommandInfo(){
    std::cout << "One argument commands: " << std::endl;
    for(const CommandInfo &c : ONE_ARG_COMMAND_INFO){
        std::cout << c.name << " - " << c.explanation << std::endl;
    }
    std::cout << std::endl;

    std::cout << "Two argument commands: " << std::endl;
    for(const CommandInfo &c : TWO_ARG_COMMAND_INFO){
        std::cout << c.name << " - " << c.explanation << std::endl;
    }
    std::cout << std::endl;


    std::cout << "No argument commands: " << std::endl;
    for(const CommandInfo &c : NO_ARG_COMMAND_INFO){
        std::cout << c.name << " - " << c.explanation << std::endl;
    }
}