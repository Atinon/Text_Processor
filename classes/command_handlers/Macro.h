#ifndef TEXT_PROCESSOR_MACRO_H
#define TEXT_PROCESSOR_MACRO_H

#include <string>
#include <vector>

class Macro {
public:
    std::string name;
    std::vector<std::string> commands;

    Macro() = default;

    Macro(const std::string &name);

    Macro(const std::string &name, const std::vector<std::string> &commands);
};


#endif //TEXT_PROCESSOR_MACRO_H
