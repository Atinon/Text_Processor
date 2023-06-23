#ifndef TEXT_PROCESSOR_CONSOLECOMMANDHANDLER_H
#define TEXT_PROCESSOR_CONSOLECOMMANDHANDLER_H


#include "ICommandHandler.h"
#include "../TextProcessor.h"
#include <string>
#include <vector>
#include <cstring>
#include <stdexcept>
#include <iostream>


class ConsoleCommandHandler : public ICommandHandler<std::string> {
private:
    template<typename ClassName, typename ReturnType, typename ...Args>
    struct Command {
        std::string stringValue;

        ReturnType (ClassName::*func)(Args...);
    };

    template<typename ClassName,
            typename ReturnType,
            typename PrinterClass,
            typename PrinterReturnType,
            typename ...PrinterArgs>
    struct CommandConstPrinting {
        std::string stringValue;

        ReturnType (ClassName::*func)() const;

        PrinterReturnType (PrinterClass::*printFunc)(PrinterArgs...);
    };

    const static char *SPACE_DELIM_;

    const static std::string EXIT_COMMAND_;

    TextProcessor *textProcessor_;

    const std::vector<Command<TextProcessor, void>> textProcessorNoArgsCommandsVoid_ =
            {
                    {"save", &TextProcessor::save},
                    {"sort", &TextProcessor::sort},
            };

    const std::vector<CommandConstPrinting<
            TextProcessor,
            const std::vector<BaseLine *> &,
            ConsoleCommandHandler,
            void,
            const std::vector<BaseLine *> &>>
            textProcessorNoArgsCommandsVectorPrinting_ =
            {
                    {
                            "print",
                            &TextProcessor::getLines,
                            &ConsoleCommandHandler::printRegular_
                    },
                    {
                            "print_centered",
                            &TextProcessor::getLines,
                            &ConsoleCommandHandler::printCentered_
                    },

            };

    const std::vector<Command<TextProcessor, void, const std::string &>> textProcessorOneArgCommandsVoid_ =
            {
                    {"open", &TextProcessor::open},
                    {"save_as", &TextProcessor::saveAs},
            };

    static size_t getMaxLineWidth_(const std::vector<BaseLine *> &lines);

    static void basicTokenizingFunction_(const std::string &command, std::vector<std::string> &vectorRef);

    void printRegular_(const std::vector<BaseLine *> &lines);

    void printCentered_(const std::vector<BaseLine *> &lines);

    void handleNoArgCommand_(const std::vector<std::string> &commandTokens);

    void handleOneArgCommand_(const std::vector<std::string> &commandTokens);

public:
    explicit ConsoleCommandHandler(TextProcessor *textProcessor) : textProcessor_(textProcessor) {};

    void handleCommand(const std::string &command) override;

    void startConsoleUi();

    ~ConsoleCommandHandler() override = default;
};


#endif //TEXT_PROCESSOR_CONSOLECOMMANDHANDLER_H
