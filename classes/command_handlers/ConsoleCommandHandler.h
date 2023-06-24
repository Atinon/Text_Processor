#ifndef TEXT_PROCESSOR_CONSOLECOMMANDHANDLER_H
#define TEXT_PROCESSOR_CONSOLECOMMANDHANDLER_H


#include "ICommandHandler.h"
#include "ConsoleCommandHandlerUtil.h"
#include "../TextProcessor.h"
#include "Macro.h"
#include <string>
#include <vector>
#include <cstring>
#include <stdexcept>
#include <iostream>

/**
 * Class for console commands, implements the ICommandHandler interface.
 */
class ConsoleCommandHandler : public ICommandHandler<std::string> {
private:
    /**
 * Command struct template acting as a map between console commands and actual functions.
 */
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

    const static std::string HELP_COMMAND_;

    const static std::string COMMAND_SUCCESS_MSG_;

    const static std::string INVALID_COMMAND_MSG_;

    TextProcessor *textProcessor_;

    // Macro support was added last moment, so definitely needs improving and code refactoring
    std::vector<Macro> macros_;

    //NoArgsCommands ---------------------------------------------------------------------------------------------------
    const std::vector<Command<TextProcessor, void>> textProcessorNoArgsCommandsVoid_ =
            {
                    {"save",        &TextProcessor::save},
                    {"sort",        &TextProcessor::sort},
                    {"unset_block", &TextProcessor::unsetBlock},
                    {"undo", &TextProcessor::undo},
            };

    const std::vector<Command<TextProcessor, std::vector<std::string>>>
            textProcessorNoArgsCommandsVectorStringPrinting_ =
            {
                    {"print_open_files", &TextProcessor::getOpenedFileNames},
            };

    const std::vector<CommandConstPrinting<
            TextProcessor,
            const std::vector<BaseLine *> &,
            ConsoleCommandHandler,
            void,
            const std::vector<BaseLine *> &>>
            textProcessorNoArgsCommandsVectorLinesPrinting_ =
            {
                    {
                            "print",
                            &TextProcessor::getLines,
                            &ConsoleCommandHandler::printLinesRegular_
                    },
                    {
                            "print_centered",
                            &TextProcessor::getLines,
                            &ConsoleCommandHandler::printLinesCentered_
                    },
                    {
                            "print_block",
                            &TextProcessor::getBlock,
                            &ConsoleCommandHandler::printLinesRegular_
                    },
                    {
                            "print_block_centered",
                            &TextProcessor::getBlock,
                            &ConsoleCommandHandler::printLinesCentered_
                    },

            };

    //OneArgCommands ---------------------------------------------------------------------------------------------------
    const std::vector<Command<TextProcessor, void, const std::string &>> textProcessorOneArgCommandsVoidString_ =
            {
                    {"open", &TextProcessor::open},
                    {"save_as", &TextProcessor::saveAs},
            };

    const std::vector<Command<TextProcessor, void, size_t>> textProcessorOneArgCommandsVoidNum_ =
            {
                    {"remove_line", &TextProcessor::removeSingleLine},
                    {"set_current_file", &TextProcessor::setCurrentFile},
                    {"close", &TextProcessor::closeFile},
                    {"to_upper", &TextProcessor::toUpperSingleLine},
                    {"to_lower", &TextProcessor::toLowerSingleLine},
                    {"trim_left", &TextProcessor::trimLeftSingleLine},
                    {"trim_right", &TextProcessor::trimRightSingleLine},
            };

    const std::vector<Command<TextProcessor, void, size_t, const std::string &>>
            textProcessorOneArgsCommandsVoidNumPromptLine_ =
            {
                    {"add_line", &TextProcessor::addSingleLine},
            };

    const std::vector<Command<TextProcessor, void, size_t, const std::vector<std::string> &>>
            textProcessorOneArgsCommandsVoidNumPromptLineMulti_ =
            {
                    {"add_lines_many", &TextProcessor::addManyLines},
            };

    const std::vector<Command<ConsoleCommandHandler, void, const std::string &>>
            commandHandlerOneArgCommandsVoidString_ =
            {
                    {"do_macro", &ConsoleCommandHandler::executeMacro_},
                    {"add_macro", &ConsoleCommandHandler::addMacroAndFillFromConsole_},
                    {"remove_macro", &ConsoleCommandHandler::removeMacro_},
            };

    //TwoArgCommands ---------------------------------------------------------------------------------------------------
    const std::vector<Command<TextProcessor, void, size_t, size_t>> textProcessorTwoArgCommandsVoidNum_ =
            {
                    {"remove_lines_range", &TextProcessor::removeManyLines},
                    {"set_block",          &TextProcessor::setBlock},
                    {"to_upper_range", &TextProcessor::toUpperManyLines},
                    {"to_lower_range", &TextProcessor::toLowerManyLines},
                    {"trim_left_range", &TextProcessor::trimLeftManyLines},
                    {"trim_right_range", &TextProcessor::trimRightManyLines},
            };

    static void basicTokenizingFunction_(const std::string &command, std::vector<std::string> &vectorRef);

    static size_t getMaxLineWidth_(const std::vector<BaseLine *> &lines);

    static size_t parseStringToUll_(const std::string &stringValue);

    static std::string getSingleLineInput_();

    static std::vector<std::string> getMultiLineInput_();

    void printLinesRegular_(const std::vector<BaseLine *> &lines);

    void printLinesCentered_(const std::vector<BaseLine *> &lines);

    void handleNoArgCommand_(const std::vector<std::string> &commandTokens);

    void handleOneArgCommand_(const std::vector<std::string> &commandTokens);

    void handleTwoArgCommand_(const std::vector<std::string> &commandTokens);

    void executeMacro_(const std::string &macroName);

    void addMacroAndFillFromConsole_(const std::string &macroName);

    void removeMacro_(const std::string &macroName);

    void promptForSaveIfFilesOpened_();

public:
    explicit ConsoleCommandHandler(TextProcessor *textProcessor) : textProcessor_(textProcessor) {};

    void handleCommand(const std::string &command) override;

    void startConsoleUi();

    ~ConsoleCommandHandler() override = default;
};


#endif //TEXT_PROCESSOR_CONSOLECOMMANDHANDLER_H
