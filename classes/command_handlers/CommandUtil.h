#ifndef TEXT_PROCESSOR_COMMANDUTIL_H
#define TEXT_PROCESSOR_COMMANDUTIL_H

#include <iostream>
#include <vector>
#include "../line/BaseLine.h"

class Printer {
public:
    static size_t getMaxLineWidth(const std::vector<BaseLine *> &lines);

    static void printLinesRegular(const std::vector<BaseLine *> &lines);

    static void printLinesCentered(const std::vector<BaseLine *> &lines);

    static void printFileNames(const std::vector<std::string> &names);
};

class InputReceiver {
public:
    static std::string getSingleLineInput();

    static std::vector<std::string> getMultiLineInput();
};

class InputParser {
public:
    static size_t parseStringToUll(const std::string &stringValue);
};
#endif //TEXT_PROCESSOR_COMMANDUTIL_H
