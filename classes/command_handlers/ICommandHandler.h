#ifndef TEXT_PROCESSOR_ICOMMANDHANDLER_H
#define TEXT_PROCESSOR_ICOMMANDHANDLER_H

template <typename T>
class ICommandHandler {
public:
    virtual void handleCommand(const T &command) = 0;

    virtual ~ICommandHandler() = default;
};


#endif //TEXT_PROCESSOR_ICOMMANDHANDLER_H
