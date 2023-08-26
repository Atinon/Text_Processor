#ifndef TEXT_PROCESSOR_CONSOLECOMMANDHANDLER_H
#define TEXT_PROCESSOR_CONSOLECOMMANDHANDLER_H

#include "Command.h"
#include "CommandFactory.h"
#include "ICommandHandler.h"
#include "../TextProcessor.h"
#include "Macro.h"
#include <string>
#include <vector>
#include <cstring>
#include <stdexcept>
#include <iostream>

/**
 * @class ConsoleCommandHandler
 * @brief Class for handling console commands, implements the ICommandHandler interface.
 *
 * This class is responsible for handling console commands. It implements the ICommandHandler interface, allowing it
 * to handle commands of type std::string. The class is designed to interact with a TextProcessor instance to execute
 * various commands on text files.
 */
class ConsoleCommandHandler : public ICommandHandler<std::string> {
private:
    const static std::string EXIT_COMMAND_; ///< The command to exit the console UI.

    const static std::string HELP_COMMAND_; ///< The command to display help information.

    const static std::string COMMAND_SUCCESS_MSG_; ///< Success message for command execution.

    const static std::string INVALID_COMMAND_MSG_; ///< Message for invalid command input.

    TextProcessor *textProcessor_; /// Pointer to the TextProcessor instance.

    // Macro support was added last moment, so needs improving/refactoring
    std::vector<Macro> macros_; /// Collection of macros for command shortcuts.

    /**
    * @brief Execute a macro by its name.
    *
    * This private method executes a stored macro by its name, if it exists.
    *
    * @param macroName The name of the macro to execute.
    * @throw std::runtime_error if no such macro
    */
    void executeMacro(const std::string &macroName);

    /**
    * @brief Add a macro and populate its commands from console input.
    *
    * This private method allows adding a new macro by providing its name and then filling its commands using
    * console input.
    *
    * @param macroName The name of the new macro.
    * @throw std::runtime_error If macro with same name exists.
    */
    void addMacroAndFillFromConsole(const std::string &macroName);

    /**
     * @brief Remove a macro by its name.
    *
    * This private method removes a macro by its name.
     *
     * @param macroName The name of the macro to remove.
     * @throw std::runtime_error If no macro with this name exists.
     */
    void removeMacro(const std::string &macroName);

    /**
    * @brief Prompt for saving if files are opened.
    *
    * This private method prompts the user for saving any modified files if there are opened files.
     */
    void promptForSaveIfFilesOpened();

    /**
    * @brief Execute a command based on the command tokens.
    *
    * This private method executes a command based on the parsed command tokens.
    *
    * @param commandTokens The parsed command tokens.
    */
    void executeCommand(const std::vector<std::string> &commandTokens);

public:
    /**
    * @brief Constructor taking a TextProcessor instance.
    *
    * This constructor initializes the ConsoleCommandHandler with a TextProcessor instance, allowing it to interact
    * with text files.
    *
    * @param textProcessor Pointer to a TextProcessor instance.
    */
    explicit ConsoleCommandHandler(TextProcessor *textProcessor);

    /**
    * @brief Handle a console command.
    *
    * This method is called to handle a console command passed as a string. It delegates the command to the
    * appropriate execution method.
    *
    * @param command The console command to handle.
    */
    void handleCommand(const std::string &command) override;

    /**
    * @brief Start the console user interface.
    *
    * This method initiates the console user interface, allowing users to input commands and interact with the
    * TextProcessor instance.
    */
    void startConsoleUi();

    ~ConsoleCommandHandler() override = default;
};


#endif //TEXT_PROCESSOR_CONSOLECOMMANDHANDLER_H
