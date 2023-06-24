#include "ConsoleCommandHandler.h"

const char *ConsoleCommandHandler::SPACE_DELIM_ = " ";

const std::string ConsoleCommandHandler::EXIT_COMMAND_ = "exit";

const std::string ConsoleCommandHandler::COMMAND_SUCCESS_MSG_ = "Command successful.";

const std::string ConsoleCommandHandler::INVALID_COMMAND_MSG_ = "Invalid Command.";

void ConsoleCommandHandler::basicTokenizingFunction_(const std::string &command, std::vector<std::string> &vectorRef) {
    char *dup = strdup(command.c_str());
    char *tokPtr = strtok(dup, SPACE_DELIM_);
    while (tokPtr != nullptr) {
        vectorRef.emplace_back(tokPtr);
        tokPtr = strtok(nullptr, SPACE_DELIM_);
    }
    delete[] dup;
}

size_t ConsoleCommandHandler::getMaxLineWidth_(const std::vector<BaseLine *> &lines) {
    size_t maxWidth = 0;
    for (const BaseLine *line: lines) {
        size_t lineWidth = line->getStringValue().length();
        if (lineWidth > maxWidth) {
            maxWidth = lineWidth;
        }
    }
    return maxWidth;
}

size_t ConsoleCommandHandler::parseStringToUll_(const std::string &stringValue) {
    try {
        return std::stoull(stringValue);
    }
    catch (...) {
        throw std::runtime_error("Please enter a valid number.");
    }
}

std::string ConsoleCommandHandler::getSingleLineInput_() {
    std::string result;

    if(!std::getline(std::cin, result)){
        throw std::runtime_error("Error reading from input stream.");
    }

    return result;
}

std::vector<std::string> ConsoleCommandHandler::getMultiLineInput_() {
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

void ConsoleCommandHandler::startConsoleUi() {
    std::string command;

    std::cout << "Text Processor console UI started..." << std::endl;
    std::cout << "Please enter a command below: " << std::endl;
    do {
        std::cout << ">> ";
        std::getline(std::cin, command);
        handleCommand(command);
    } while (command != EXIT_COMMAND_);
    std::cout << "Exiting..." << std::endl;
}

void ConsoleCommandHandler::handleCommand(const std::string &command) {
    std::vector<std::string> commandTokens;
    basicTokenizingFunction_(command, commandTokens);

    if (commandTokens.empty()) {
        std::cout << "Please provide a command." << std::endl;
        return;
    }

    if (commandTokens.size() == 1) {
        if (commandTokens[0] == EXIT_COMMAND_) {
            return;
        }

        handleNoArgCommand_(commandTokens);
        return;
    }

    else if (commandTokens.size() == 2) {
        handleOneArgCommand_(commandTokens);
        return;
    }

    else if (commandTokens.size() == 3) {
        handleTwoArgCommand_(commandTokens);
        return;
    }

    // to add other commands...

    std::cout << INVALID_COMMAND_MSG_ << std::endl;
}

void ConsoleCommandHandler::handleNoArgCommand_(const std::vector<std::string> &commandTokens) {
    const std::string &currentCommand = commandTokens[0];

    // textProcessorNoArgsCommandsVoid_
    for (const Command<TextProcessor, void> &c: textProcessorNoArgsCommandsVoid_) {
        if (c.stringValue == currentCommand) {
            try {
                (textProcessor_->*c.func)();
                std::cout << COMMAND_SUCCESS_MSG_ << std::endl;
                return;
            }
            catch (const std::runtime_error &e) {
                std::cout << e.what() << std::endl;
                return;
            }
        }
    }

    // textProcessorNoArgsCommandsVectorPrinting_
    for (const CommandConstPrinting<
                TextProcessor,
                const std::vector<BaseLine *> &,
                ConsoleCommandHandler,
                void,
                const std::vector<BaseLine *> &> &c: textProcessorNoArgsCommandsVectorPrinting_) {
        if (c.stringValue == currentCommand) {
            try{
                const std::vector<BaseLine *> &lines = (textProcessor_->*c.func)();
                (this->*c.printFunc)(lines);
                return;
            }
            catch(const std::runtime_error &e){
                std::cout << e.what() << std::endl;
                return;
            }

        }
    }

    std::cout << INVALID_COMMAND_MSG_ << std::endl;
}

void ConsoleCommandHandler::handleOneArgCommand_(const std::vector<std::string> &commandTokens) {
    const std::string &currentCommand = commandTokens[0];
    const std::string &argOne = commandTokens[1];

    // textProcessorOneArgCommandsVoidString_
    for (const Command<TextProcessor, void, const std::string &> &c: textProcessorOneArgCommandsVoidString_) {
        if (c.stringValue == currentCommand) {
            try {
                (textProcessor_->*c.func)(argOne);
                std::cout << COMMAND_SUCCESS_MSG_ << std::endl;
                return;
            }
            catch (const std::runtime_error &e) {
                std::cout << e.what() << std::endl;
                return;
            }
        }
    }

    // textProcessorOneArgCommandsVoidNum_
    for (const Command<TextProcessor, void, size_t> &c: textProcessorOneArgCommandsVoidNum_) {
        if (c.stringValue == currentCommand) {
            size_t indexVal;
            try {
                indexVal = parseStringToUll_(argOne);
            }
            catch (const std::runtime_error &e) {
                std::cout << e.what() << std::endl;
                return;
            }
            try {
                (textProcessor_->*c.func)(indexVal);
                std::cout << COMMAND_SUCCESS_MSG_ << std::endl;
                return;
            }
            catch (const std::runtime_error &e) {
                std::cout << e.what() << std::endl;
                return;
            }
        }
    }

    // textProcessorOneArgsCommandsVoidNumPromptLine_
    for (const Command<
                TextProcessor,
                void,
                size_t,
                const std::string &> &c: textProcessorOneArgsCommandsVoidNumPromptLine_) {
        if (c.stringValue == currentCommand) {
            size_t indexVal;
            try {
                indexVal = parseStringToUll_(argOne);
            }
            catch (const std::runtime_error &e) {
                std::cout << e.what() << std::endl;
                return;
            }

            std::string input;
            std::cout << "Enter the line you want to enter: " << std::endl;
            try{
                input = getSingleLineInput_();
            }
            catch(const std::runtime_error &e){
                std::cout << e.what() << std::endl;
                return;
            }

            try {
                (textProcessor_->*c.func)(indexVal, input);
                std::cout << COMMAND_SUCCESS_MSG_ << std::endl;
                return;
            }
            catch (const std::runtime_error &e) {
                std::cout << e.what() << std::endl;
                return;
            }
        }
    }

    //textProcessorOneArgsCommandsVoidNumPromptLineMulti_
    for (const Command<
                TextProcessor,
                void,
                size_t,
                const std::vector<std::string> &> &c: textProcessorOneArgsCommandsVoidNumPromptLineMulti_) {
        if (c.stringValue == currentCommand) {
            size_t indexVal;
            try {
                indexVal = parseStringToUll_(argOne);
            }
            catch (const std::runtime_error &e) {
                std::cout << e.what() << std::endl;
                return;
            }

            std::vector<std::string> input;
            std::cout << "Enter the lines you want to enter (blank line to stop): " << std::endl;
            try {
                input = getMultiLineInput_();
            }
            catch (const std::bad_alloc &) {
                std::cout << "Too many lines entered. Insufficient memory." << std::endl;
                return;
            }
            catch(const std::runtime_error &e){
                std::cout << e.what() << std::endl;
                return;
            }

            try {
                (textProcessor_->*c.func)(indexVal, input);
                std::cout << COMMAND_SUCCESS_MSG_ << std::endl;
                return;
            }
            catch (const std::runtime_error &e) {
                std::cout << e.what() << std::endl;
                return;
            }
        }
    }

    std::cout << INVALID_COMMAND_MSG_ << std::endl;
}

void ConsoleCommandHandler::handleTwoArgCommand_(const std::vector<std::string> &commandTokens) {
    const std::string &currentCommand = commandTokens[0];
    const std::string &argOne = commandTokens[1];
    const std::string &argTwo = commandTokens[2];

    // textProcessorTwoArgCommandsVoidNum_
    for (const Command<TextProcessor, void, size_t, size_t> &c: textProcessorTwoArgCommandsVoidNum_) {
        if (c.stringValue == currentCommand) {
            size_t firstIndexVal, secondIndexVal;
            try {
                firstIndexVal = parseStringToUll_(argOne);
                secondIndexVal = parseStringToUll_(argTwo);
            }
            catch (const std::runtime_error &e) {
                std::cout << e.what() << std::endl;
                return;
            }
            try {
                (textProcessor_->*c.func)(firstIndexVal, secondIndexVal);
                std::cout << COMMAND_SUCCESS_MSG_ << std::endl;
                return;
            }
            catch (const std::runtime_error &e) {
                std::cout << e.what() << std::endl;
                return;
            }
        }
    }

    std::cout << INVALID_COMMAND_MSG_ << std::endl;
}

void ConsoleCommandHandler::printRegular_(const std::vector<BaseLine *> &lines) {
    for (int i = 0; i < lines.size(); ++i) {
        std::cout
                << "idx: " << i
                << "|  " << lines[i]->getStringValue()
                << "  |Type: " << lines[i]->getType()
                << std::endl;
    }
}

void ConsoleCommandHandler::printCentered_(const std::vector<BaseLine *> &lines) {
    size_t maxWidth = getMaxLineWidth_(lines);

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
