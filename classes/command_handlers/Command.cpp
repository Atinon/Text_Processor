#include "Command.h"


// No argument commands

void SaveCommand::execute(TextProcessor &tp) {
    tp.save();
}

void SortCommand::execute(TextProcessor &tp) {
    tp.sort();
}

void UnsetBlockCommand::execute(TextProcessor &tp) {
    tp.unsetBlock();
}

void UndoCommand::execute(TextProcessor &tp) {
    tp.undo();
}

void PrintCommand::execute(TextProcessor &tp) {
    const std::vector<BaseLine *> &lines = tp.getLines();
    Printer::printLinesRegular(lines);
}

void PrintCenteredCommand::execute(TextProcessor &tp) {
    const std::vector<BaseLine *> &lines = tp.getLines();
    Printer::printLinesCentered(lines);
}

void PrintBlockCommand::execute(TextProcessor &tp) {
    const std::vector<BaseLine *> &lines = tp.getBlock();
    Printer::printLinesRegular(lines);
}

void PrintBlockCenteredCommand::execute(TextProcessor &tp) {
    const std::vector<BaseLine *> &lines = tp.getBlock();
    Printer::printLinesCentered(lines);
}

void PrintOpenFilesCommand::execute(TextProcessor &tp) {
    const std::vector<std::string> &fileNames = tp.getOpenedFileNames();
    Printer::printFileNames(fileNames);
}

// One argument commands

OpenCommand::OpenCommand(const std::string &fileName) : fileName_(fileName) {}

void OpenCommand::execute(TextProcessor &tp) {
    tp.open(fileName_);
}

SaveAsCommand::SaveAsCommand(const std::string &fileName) : fileName_(fileName) {}

void SaveAsCommand::execute(TextProcessor &tp) {
    tp.saveAs(fileName_);
}

RemoveLineCommand::RemoveLineCommand(size_t index) : index_(index) {}

void RemoveLineCommand::execute(TextProcessor &tp) {
    tp.removeSingleLine(index_);
}

SetCurrentFileCommand::SetCurrentFileCommand(size_t index) : index_(index) {}

void SetCurrentFileCommand::execute(TextProcessor &tp) {
    tp.setCurrentFile(index_);
}

CloseCommand::CloseCommand(size_t index) : index_(index) {}

void CloseCommand::execute(TextProcessor &tp) {
    tp.closeFile(index_);
}

ToUpperCommand::ToUpperCommand(size_t index) : index_(index) {}

void ToUpperCommand::execute(TextProcessor &tp) {
    tp.toUpperSingleLine(index_);
}

ToLowerCommand::ToLowerCommand(size_t index) : index_(index) {}

void ToLowerCommand::execute(TextProcessor &tp) {
    tp.toLowerSingleLine(index_);
}

TrimLeftCommand::TrimLeftCommand(size_t index) : index_(index) {}

void TrimLeftCommand::execute(TextProcessor &tp) {
    tp.trimLeftSingleLine(index_);
}

TrimRightCommand::TrimRightCommand(size_t index) : index_(index) {}

void TrimRightCommand::execute(TextProcessor &tp) {
    tp.trimRightSingleLine(index_);
}

AddLineCommand::AddLineCommand(size_t index) : index_(index) {}

void AddLineCommand::execute(TextProcessor &tp) {
    std::cout << "Enter the line you want to enter: " << std::endl;
    const std::string &input = InputReceiver::getSingleLineInput();
    tp.addSingleLine(index_, input);
}

AddLinesManyCommand::AddLinesManyCommand(size_t index) : index_(index) {}

void AddLinesManyCommand::execute(TextProcessor &tp) {
    std::cout << "Enter the lines you want to enter (blank line to stop): " << std::endl;
    const std::vector<std::string> &input = InputReceiver::getMultiLineInput();
    tp.addManyLines(index_, input);
}

// TODO
//AddMacro::AddMacro(const std::string &name) : name_(name) {}
//
//void AddMacro::execute(TextProcessor &tp) {
//
//}
//
//DoMacro::DoMacro(const std::string &name) : name_(name) {}
//
//RemoveMacro::RemoveMacro(const std::string &name) : name_(name) {}
// TODO

// Two argument commands

RemoveLinesRangeCommand::RemoveLinesRangeCommand(size_t firstIndex, size_t secondIndex) : firstIndex_(firstIndex),
                                                                                          secondIndex_(secondIndex) {}

void RemoveLinesRangeCommand::execute(TextProcessor &tp) {
    tp.removeManyLines(firstIndex_, secondIndex_);
}

SetBlockCommand::SetBlockCommand(size_t firstIndex, size_t secondIndex) : firstIndex_(firstIndex),
                                                                          secondIndex_(secondIndex) {}

void SetBlockCommand::execute(TextProcessor &tp) {
    tp.setBlock(firstIndex_, secondIndex_);
}

ToUpperRangeCommand::ToUpperRangeCommand(size_t firstIndex, size_t secondIndex) : firstIndex_(firstIndex),
                                                                                  secondIndex_(secondIndex) {}

void ToUpperRangeCommand::execute(TextProcessor &tp) {
    tp.toUpperManyLines(firstIndex_, secondIndex_);
}

ToLowerRangeCommand::ToLowerRangeCommand(size_t firstIndex, size_t secondIndex) : firstIndex_(firstIndex),
                                                                                  secondIndex_(secondIndex) {}

void ToLowerRangeCommand::execute(TextProcessor &tp) {
    tp.toLowerManyLines(firstIndex_, secondIndex_);
}

TrimLeftRangeCommand::TrimLeftRangeCommand(size_t firstIndex, size_t secondIndex) : firstIndex_(firstIndex),
                                                                                    secondIndex_(secondIndex) {}

void TrimLeftRangeCommand::execute(TextProcessor &tp) {
    tp.trimLeftManyLines(firstIndex_, secondIndex_);
}

TrimRightRangeCommand::TrimRightRangeCommand(size_t firstIndex, size_t secondIndex) : firstIndex_(firstIndex),
                                                                                      secondIndex_(secondIndex) {}

void TrimRightRangeCommand::execute(TextProcessor &tp) {
    tp.trimRightManyLines(firstIndex_, secondIndex_);
}
