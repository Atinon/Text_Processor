#ifndef TEXT_PROCESSOR_MACRO_H
#define TEXT_PROCESSOR_MACRO_H

#include <string>
#include <vector>

/**
 * @class Macro
 * @brief A class to define a macro containing a name and a series of commands.
 *
 * This class is used within the ConsoleCommandHandler to manage macros. A macro consists of a user-defined name and
 * a collection of commands that can be executed as a sequence.
 */
class Macro {
public:
    std::string name;
    std::vector<std::string> commands;

    Macro() = default;

    Macro(const std::string &name);

    Macro(const std::string &name, const std::vector<std::string> &commands);
};


#endif //TEXT_PROCESSOR_MACRO_H
