#ifndef TEXT_PROCESSOR_COMMANDFACTORY_H
#define TEXT_PROCESSOR_COMMANDFACTORY_H

#include "Command.h"

class CommandFactory {
public:
    static Command *createCommand(const std::vector<std::string> &commandTokens);
};


#endif //TEXT_PROCESSOR_COMMANDFACTORY_H
