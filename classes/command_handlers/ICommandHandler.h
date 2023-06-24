#ifndef TEXT_PROCESSOR_ICOMMANDHANDLER_H
#define TEXT_PROCESSOR_ICOMMANDHANDLER_H

/**
 * Interface template class providing a handle command with a template parameter.
 *
 * Can be implemented with different types of commands. Current implementation used is with string commands.
 */
template <typename T>
class ICommandHandler {
public:
    virtual void handleCommand(const T &command) = 0;

    virtual ~ICommandHandler() = default;
};


#endif //TEXT_PROCESSOR_ICOMMANDHANDLER_H
