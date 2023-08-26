#ifndef TEXT_PROCESSOR_ICOMMANDHANDLER_H
#define TEXT_PROCESSOR_ICOMMANDHANDLER_H

/**
 * @class ICommandHandler
 * @brief Interface template class to handle commands of a specified type.
 *
 * @tparam T The type of command to be handled.
 */
template <typename T>
class ICommandHandler {
public:
    virtual void handleCommand(const T &command) = 0;

    virtual ~ICommandHandler() = default;
};


#endif //TEXT_PROCESSOR_ICOMMANDHANDLER_H
