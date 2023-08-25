#include "CommandUtil.h"

size_t Printer::getMaxLineWidth(const std::vector<BaseLine *> &lines) {
    size_t maxWidth = 0;
    for (const BaseLine *line: lines) {
        size_t lineWidth = line->getStringValue().length();
        if (lineWidth > maxWidth) {
            maxWidth = lineWidth;
        }
    }
    return maxWidth;
}

void Printer::printLinesRegular(const std::vector<BaseLine *> &lines) {
    for (int i = 0; i < lines.size(); ++i) {
        std::cout
                << "idx: " << i
                << "|  " << lines[i]->getStringValue()
                << "  |Type: " << lines[i]->getType()
                << std::endl;
    }
}

void Printer::printLinesCentered(const std::vector<BaseLine *> &lines) {
    size_t maxWidth = getMaxLineWidth(lines);

    for (int i = 0; i < lines.size(); ++i) {
        std::cout << "idx: " << i << "|  ";

        const std::string &lineValue = lines[i]->getStringValue();
        size_t padding = (maxWidth - lineValue.length()) / 2;

        // Print leading spaces for centering
        for (int j = 0; j < padding; ++j) {
            std::cout << " ";
        }

        std::cout << lineValue;

        for (int j = 1; j < padding; ++j) {
            std::cout << " ";
        }

        // Print trailing space for centering (if needed)
        if (padding > 0 && (maxWidth - lineValue.length()) % 2 != 0) {
            std::cout << " ";
        }

        std::cout << "  |Type: " << lines[i]->getType() << std::endl;
    }
}

void Printer::printFileNames(const std::vector<std::string> &names) {
    for(size_t i = 0; i < names.size(); ++i){
        std::cout
                << "idx: " << i
                << "|  " << names[i]
                << std::endl;
    }
}

void Printer::printCommandInfo() {
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

std::string InputReceiver::getSingleLineInput() {
    std::string result;

    if(!std::getline(std::cin, result)){
        throw std::runtime_error("Error reading from input stream.");
    }

    return result;
}

std::vector<std::string> InputReceiver::getMultiLineInput() {
    std::vector<std::string> result;
    std::string currentString;

    try {
        do {
            if(!std::getline(std::cin, currentString)){
                throw std::runtime_error("Error reading from input stream.");
            };
            result.push_back(currentString);
        } while (!currentString.empty());
    }
    catch (const std::bad_alloc &) {
        result.clear();
        throw;
    }
    return result;
}

size_t InputParser::parseStringToUll(const std::string &stringValue) {
    try {
        return std::stoull(stringValue);
    }
    catch (...) {
        throw std::runtime_error("Please enter a valid number.");
    }
}

void InputParser::basicTokenizingFunction(const std::string &command, std::vector<std::string> &vectorRef) {
    static const char* SPACE_DELIM = " ";

    char *dup = strdup(command.c_str());
    char *tokPtr = strtok(dup, SPACE_DELIM);
    while (tokPtr != nullptr) {
        vectorRef.emplace_back(tokPtr);
        tokPtr = strtok(nullptr, SPACE_DELIM);
    }
    delete[] dup;
}
