#ifndef TEXT_PROCESSOR_CONSOLECOMMANDHANDLER_H
#define TEXT_PROCESSOR_CONSOLECOMMANDHANDLER_H

#include "Command.h"
#include "CommandFactory.h"
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
    const static std::string EXIT_COMMAND_;

    const static std::string HELP_COMMAND_;

    const static std::string COMMAND_SUCCESS_MSG_;

    const static std::string INVALID_COMMAND_MSG_;

    TextProcessor *textProcessor_;

    // Macro support was added last moment, so needs improving/refactoring
    std::vector<Macro> macros_;

    void executeMacro(const std::string &macroName);

    void addMacroAndFillFromConsole(const std::string &macroName);

    void removeMacro(const std::string &macroName);

    void promptForSaveIfFilesOpened();

    void executeCommand(const std::vector<std::string> &commandTokens);

public:
    explicit ConsoleCommandHandler(TextProcessor *textProcessor) : textProcessor_(textProcessor) {};

    void handleCommand(const std::string &command) override;

    void startConsoleUi();

    ~ConsoleCommandHandler() override = default;
};


#endif //TEXT_PROCESSOR_CONSOLECOMMANDHANDLER_H
