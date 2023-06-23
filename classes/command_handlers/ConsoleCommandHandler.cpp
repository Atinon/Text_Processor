#include "ConsoleCommandHandler.h"

const char *ConsoleCommandHandler::SPACE_DELIM_ = " ";
const std::string ConsoleCommandHandler::EXIT_COMMAND_ = "exit";

size_t ConsoleCommandHandler::getMaxLineWidth_(const std::vector<BaseLine *> &lines) {
    size_t maxWidth = 0;
    for (const BaseLine* line : lines) {
        size_t lineWidth = line->getStringValue().length();
        if (lineWidth > maxWidth) {
            maxWidth = lineWidth;
        }
    }
    return maxWidth;
}

void ConsoleCommandHandler::basicTokenizingFunction_(const std::string &command, std::vector<std::string> &vectorRef) {
    char *dup = strdup(command.c_str());
    char *tokPtr = strtok(dup, SPACE_DELIM_);
    while (tokPtr != nullptr) {
        vectorRef.emplace_back(tokPtr);
        tokPtr = strtok(nullptr, SPACE_DELIM_);
    }
    delete[] dup;
}

void ConsoleCommandHandler::startConsoleUi() {
    std::string command;

    std::cout << "Text Processor console UI started..." << std::endl;
    std::cout << "Please enter a command below: " << std::endl;
    do {
        std::cout << ">> ";
        std::getline(std::cin, command);
//        std::cout << std::endl;
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
    } else if (commandTokens.size() == 2) {
        handleOneArgCommand_(commandTokens);
        return;
    }

    // to add other commands...


    std::cout << "Invalid command." << std::endl;
}

void ConsoleCommandHandler::handleNoArgCommand_(const std::vector<std::string> &commandTokens) {
    // textProcessorNoArgsCommandsVoid_
    for (const Command<TextProcessor, void> &c: textProcessorNoArgsCommandsVoid_) {
        if (c.stringValue == commandTokens[0]) {
            try {
                (textProcessor_->*c.func)();
                std::cout << "Command successful." << std::endl;
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
        if (c.stringValue == commandTokens[0]) {
            const std::vector<BaseLine *> &lines = (textProcessor_->*c.func)();
            (this->*c.printFunc)(lines);
            return;
        }
    }

    std::cout << "Invalid command." << std::endl;
}

void ConsoleCommandHandler::handleOneArgCommand_(const std::vector<std::string> &commandTokens) {
    // textProcessorOneArgCommandsVoid_
    for (const Command<TextProcessor, void, const std::string &> &c: textProcessorOneArgCommandsVoid_) {
        if (c.stringValue == commandTokens[0]) {
            try {
                (textProcessor_->*c.func)(commandTokens[1]);
                std::cout << "Command successful." << std::endl;
                return;
            }
            catch (const std::runtime_error &e) {
                std::cout << e.what() << std::endl;
                return;
            }
        }
    }
    std::cout << "Invalid command." << std::endl;
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
