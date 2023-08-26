#ifndef TEXT_PROCESSOR_COMMANDFACTORY_H
#define TEXT_PROCESSOR_COMMANDFACTORY_H

#include "Command.h"

/**
  * @class CommandFactory
  * @brief Factory class for creating Command objects.
  *
  * This class provides a static method for creating Command objects based on the provided command tokens.
  * It is responsible for parsing the command tokens and returning an appropriate Command object.
  */
class CommandFactory {
public:
    /**
     * @brief Create a Command object based on the provided command tokens.
    * @param commandTokens A vector of strings containing the command tokens.
    * @return A dynamically allocated Command object.
    *
    * This function analyzes the provided command tokens and creates an appropriate Command object.
    * The specific Command subclass created depends on the content of the command tokens.
    * The caller is responsible for managing the memory of the returned Command object.
    */
    static Command *createCommand(const std::vector<std::string> &commandTokens);
};


#endif //TEXT_PROCESSOR_COMMANDFACTORY_H
