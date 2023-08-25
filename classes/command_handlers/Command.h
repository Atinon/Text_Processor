#ifndef TEXT_PROCESSOR_COMMAND_H
#define TEXT_PROCESSOR_COMMAND_H

#include "../TextProcessor.h"
#include "CommandUtil.h"

class Command {
public:
    virtual void execute(TextProcessor &tp) = 0;

    virtual ~Command() = default;
};

// No argument commands

class SaveCommand : public Command {
public:
    void execute(TextProcessor &tp) override;
};

class SortCommand : public Command {
public:
    void execute(TextProcessor &tp) override;
};

class UnsetBlockCommand : public Command {
public:
    void execute(TextProcessor &tp) override;
};

class UndoCommand : public Command {
public:
    void execute(TextProcessor &tp) override;
};

class PrintCommand : public Command {
public:
    void execute(TextProcessor &tp) override;
};

class PrintCenteredCommand : public Command {
public:
    void execute(TextProcessor &tp) override;
};

class PrintBlockCommand : public Command {
public:
    void execute(TextProcessor &tp) override;
};

class PrintBlockCenteredCommand : public Command {
public:
    void execute(TextProcessor &tp) override;
};

class PrintOpenFilesCommand : public Command {
public:
    void execute(TextProcessor &tp) override;
};

// One argument commands

class OpenCommand : public Command {
    std::string fileName_;

public:
    explicit OpenCommand(const std::string &fileName);

    void execute(TextProcessor &tp) override;
};

class SaveAsCommand : public Command {
    std::string fileName_;

public:
    explicit SaveAsCommand(const std::string &fileName);

    void execute(TextProcessor &tp) override;
};

class RemoveLineCommand : public Command {
    size_t index_;

public:
    explicit RemoveLineCommand(size_t index);

    void execute(TextProcessor &tp) override;
};

class SetCurrentFileCommand : public Command {
    size_t index_;

public:
    explicit SetCurrentFileCommand(size_t index);

    void execute(TextProcessor &tp) override;
};

class CloseCommand : public Command {
    size_t index_;

public:
    explicit CloseCommand(size_t index);

    void execute(TextProcessor &tp) override;
};

class ToUpperCommand : public Command {
    size_t index_;

public:
    explicit ToUpperCommand(size_t index);

    void execute(TextProcessor &tp) override;
};

class ToLowerCommand : public Command {
    size_t index_;

public:
    explicit ToLowerCommand(size_t index);

    void execute(TextProcessor &tp) override;
};

class TrimLeftCommand : public Command {
    size_t index_;

public:
    explicit TrimLeftCommand(size_t index);

    void execute(TextProcessor &tp) override;
};

class TrimRightCommand : public Command {
    size_t index_;

public:
    explicit TrimRightCommand(size_t index);

    void execute(TextProcessor &tp) override;
};

class AddLineCommand : public Command {
    size_t index_;

public:
    explicit AddLineCommand(size_t index);

    void execute(TextProcessor &tp) override;
};

class AddLinesManyCommand : public Command {
    size_t index_;

public:
    explicit AddLinesManyCommand(size_t index);

    void execute(TextProcessor &tp) override;
};

// TODO
//class AddMacro : public CommandOld {
//    std::string name_;
//
//public:
//    explicit AddMacro(const std::string &name);
//
//    void execute(TextProcessor &tp) override;
//};
//
//class DoMacro : public CommandOld {
//    std::string name_;
//
//public:
//    explicit DoMacro(const std::string &name);
//};
//
//class RemoveMacro : public CommandOld {
//    std::string name_;
//
//public:
//    explicit RemoveMacro(const std::string &name);
//};
// TODO

// Two argument commands

class RemoveLinesRangeCommand : public Command {
    size_t firstIndex_;
    size_t secondIndex_;

public:
    RemoveLinesRangeCommand(size_t firstIndex, size_t secondIndex);

    void execute(TextProcessor &tp) override;
};

class SetBlockCommand : public Command {
    size_t firstIndex_;
    size_t secondIndex_;

public:
    SetBlockCommand(size_t firstIndex, size_t secondIndex);

    void execute(TextProcessor &tp) override;
};

class ToUpperRangeCommand : public Command {
    size_t firstIndex_;
    size_t secondIndex_;

public:
    ToUpperRangeCommand(size_t firstIndex, size_t secondIndex);

    void execute(TextProcessor &tp) override;
};

class ToLowerRangeCommand : public Command {
    size_t firstIndex_;
    size_t secondIndex_;

public:
    ToLowerRangeCommand(size_t firstIndex, size_t secondIndex);

    void execute(TextProcessor &tp) override;
};

class TrimLeftRangeCommand : public Command {
    size_t firstIndex_;
    size_t secondIndex_;

public:
    TrimLeftRangeCommand(size_t firstIndex, size_t secondIndex);

    void execute(TextProcessor &tp) override;
};

class TrimRightRangeCommand : public Command {
    size_t firstIndex_;
    size_t secondIndex_;

public:
    TrimRightRangeCommand(size_t firstIndex, size_t secondIndex);

    void execute(TextProcessor &tp) override;
};

#endif //TEXT_PROCESSOR_COMMAND_H
