#ifndef TEXT_PROCESSOR_MACRO_H
#define TEXT_PROCESSOR_MACRO_H

#include <string>
#include <vector>

/**
 * Basic class defined to hold a macro name and a series of commands for it.
 *
 * Used in ConsoleCommandHandler.
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
