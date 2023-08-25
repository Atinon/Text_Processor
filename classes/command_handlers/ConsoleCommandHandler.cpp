#include "ConsoleCommandHandler.h"

const char *ConsoleCommandHandler::SPACE_DELIM_ = " ";

const std::string ConsoleCommandHandler::EXIT_COMMAND_ = "exit";

const std::string ConsoleCommandHandler::HELP_COMMAND_ = "help";

const std::string ConsoleCommandHandler::COMMAND_SUCCESS_MSG_ = "Command successful.";

const std::string ConsoleCommandHandler::INVALID_COMMAND_MSG_ = "Invalid Command.";

void ConsoleCommandHandler::basicTokenizingFunction(const std::string &command, std::vector<std::string> &vectorRef) {
    char *dup = strdup(command.c_str());
    char *tokPtr = strtok(dup, SPACE_DELIM_);
    while (tokPtr != nullptr) {
        vectorRef.emplace_back(tokPtr);
        tokPtr = strtok(nullptr, SPACE_DELIM_);
    }
    delete[] dup;
}

size_t ConsoleCommandHandler::getMaxLineWidth(const std::vector<BaseLine *> &lines) {
    size_t maxWidth = 0;
    for (const BaseLine *line: lines) {
        size_t lineWidth = line->getStringValue().length();
        if (lineWidth > maxWidth) {
            maxWidth = lineWidth;
        }
    }
    return maxWidth;
}

size_t ConsoleCommandHandler::parseStringToUll(const std::string &stringValue) {
    try {
        return std::stoull(stringValue);
    }
    catch (...) {
        throw std::runtime_error("Please enter a valid number.");
    }
}

std::string ConsoleCommandHandler::getSingleLineInput() {
    std::string result;

    if(!std::getline(std::cin, result)){
        throw std::runtime_error("Error reading from input stream.");
    }

    return result;
}

std::vector<std::string> ConsoleCommandHandler::getMultiLineInput() {
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
    promptForSaveIfFilesOpened();
    std::cout << "Exiting..." << std::endl;
}

void ConsoleCommandHandler::handleCommand(const std::string &command) {
    std::vector<std::string> commandTokens;
    basicTokenizingFunction(command, commandTokens);

    if (commandTokens.empty()) {
        std::cout << "Please provide a command." << std::endl;
        return;
    }

    if (commandTokens.size() == 1) {
        if (commandTokens[0] == EXIT_COMMAND_) {
            return;
        }

        if(commandTokens[0] == HELP_COMMAND_){
            printCommandInfo();
            return;
        }

        handleNoArgCommand(commandTokens);
        return;
    }

    else if (commandTokens.size() == 2) {
        handleOneArgCommand(commandTokens);
        return;
    }

    else if (commandTokens.size() == 3) {
        handleTwoArgCommand(commandTokens);
        return;
    }

    // to add other commands...

    std::cout << INVALID_COMMAND_MSG_ << std::endl;
}

void ConsoleCommandHandler::handleNoArgCommand(const std::vector<std::string> &commandTokens) {
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

    // textProcessorNoArgsCommandsVectorStringPrinting_
    for(const Command<TextProcessor, std::vector<std::string>> &c : textProcessorNoArgsCommandsVectorStringPrinting_){
        if(c.stringValue == currentCommand){
            try{
                const std::vector<std::string> &valuesRef = (textProcessor_->*c.func)();
                for(size_t i = 0; i < valuesRef.size(); ++i){
                    std::cout
                            << "idx: " << i
                            << "|  " << valuesRef[i]
                            << std::endl;
                }
                return;
            }
            catch(...){
                std::cout << "Internal error when printing file names!" << std::endl;
                return;
            }
        }
    }

    // textProcessorNoArgsCommandsVectorLinesPrinting_
    for (const CommandConstPrinting<
                TextProcessor,
                const std::vector<BaseLine *> &,
                ConsoleCommandHandler,
                void,
                const std::vector<BaseLine *> &> &c: textProcessorNoArgsCommandsVectorLinesPrinting_) {
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

void ConsoleCommandHandler::handleOneArgCommand(const std::vector<std::string> &commandTokens) {
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
                indexVal = parseStringToUll(argOne);
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
                indexVal = parseStringToUll(argOne);
            }
            catch (const std::runtime_error &e) {
                std::cout << e.what() << std::endl;
                return;
            }

            std::string input;
            std::cout << "Enter the line you want to enter: " << std::endl;
            try{
                input = getSingleLineInput();
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
                indexVal = parseStringToUll(argOne);
            }
            catch (const std::runtime_error &e) {
                std::cout << e.what() << std::endl;
                return;
            }

            std::vector<std::string> input;
            std::cout << "Enter the lines you want to enter (blank line to stop): " << std::endl;
            try {
                input = getMultiLineInput();
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

    //commandHandlerOneArgCommandsVoidString_
    for(const Command<ConsoleCommandHandler, void, const std::string &> &c : commandHandlerOneArgCommandsVoidString_){
        if(c.stringValue == currentCommand){
            try{
                (this->*c.func)(argOne);
                std::cout << "Macro operation finished successfully." << std::endl;
                return;
            }
            catch(const std::bad_alloc &){
                std::cout << "Too many lines entered. Insufficient memory." << std::endl;
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

void ConsoleCommandHandler::handleTwoArgCommand(const std::vector<std::string> &commandTokens) {
    const std::string &currentCommand = commandTokens[0];
    const std::string &argOne = commandTokens[1];
    const std::string &argTwo = commandTokens[2];

    // textProcessorTwoArgCommandsVoidNum_
    for (const Command<TextProcessor, void, size_t, size_t> &c: textProcessorTwoArgCommandsVoidNum_) {
        if (c.stringValue == currentCommand) {
            size_t firstIndexVal, secondIndexVal;
            try {
                firstIndexVal = parseStringToUll(argOne);
                secondIndexVal = parseStringToUll(argTwo);
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

void ConsoleCommandHandler::printLinesRegular(const std::vector<BaseLine *> &lines) {
    for (int i = 0; i < lines.size(); ++i) {
        std::cout
                << "idx: " << i
                << "|  " << lines[i]->getStringValue()
                << "  |Type: " << lines[i]->getType()
                << std::endl;
    }
}

void ConsoleCommandHandler::printLinesCentered(const std::vector<BaseLine *> &lines) {
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

void ConsoleCommandHandler::executeMacro(const std::string &macroName) {
    for (const Macro &m : macros_) {
        if(m.name == macroName){
            for(const std::string &commandName : m.commands){
                std::cout << "-- Executing Command: [" << commandName << ']' << std::endl;
                handleCommand(commandName);
            }
            return;
        }
    }
    throw std::runtime_error("No such macro found.");
}

void ConsoleCommandHandler::addMacroAndFillFromConsole(const std::string &macroName) {
    for (const Macro &m : macros_) {
        if(m.name == macroName){
            throw std::runtime_error("Macro with this name already exists.");
        }
    }
    std::cout << "Enter commands line by line (blank line to stop): " << std::endl;
    std::vector<std::string> userCommands = getMultiLineInput();

    macros_.emplace_back(macroName, userCommands);
}

void ConsoleCommandHandler::removeMacro(const std::string &macroName) {
    for (int i = 0; i < macros_.size(); ++i) {
        if(macros_[i].name == macroName){
            macros_.erase(macros_.begin() + i);
            return;
        }
    }
    throw std::runtime_error("No macro exists with this name.");
}

void ConsoleCommandHandler::promptForSaveIfFilesOpened() {
    std::vector<std::string> openedFileNames = textProcessor_->getOpenedFileNames();
    for (size_t i = 0; i < openedFileNames.size(); ++i) {
        std::string input;
        std::cout
        << "File: " << openedFileNames[i] << " is open, would you like to save changes to it? (y/n)" << std::endl;
        do{
            input = getSingleLineInput();
            if(input == "y"){
                std::cout << "Attempting to execute saving commands..." << std::endl;
                handleCommand("set_current_file " + std::to_string(i));
                handleCommand("save");
            }
        }
        while(input != "y" && input != "n");
    }
}
