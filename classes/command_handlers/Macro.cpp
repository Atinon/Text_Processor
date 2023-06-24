#include "Macro.h"

Macro::Macro(const std::string &name): name(name) {}

Macro::Macro(const std::string &name, const std::vector<std::string> &commands):name(name), commands(commands) {}
