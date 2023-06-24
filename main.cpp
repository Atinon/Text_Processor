#include <iostream>
#include <cstring>

#include "classes/Config.h"
#include "classes/TextProcessor.h"
#include "classes/line/BaseLine.h"
#include "classes/line/BaseLineDerivedClasses.h"
#include "classes/line/LineParser.h"
#include "classes/command_handlers/ConsoleCommandHandler.h"

using namespace std;


int main(){
    DefaultConfig defaultConfig;
    TextProcessor textProcessor(&defaultConfig);

    // ---------- command handler
    ConsoleCommandHandler commandHandler(&textProcessor);


    const std::string fileNameOne = "sample_files/sample_text.txt";
    const std::string fileNameTwo = "sample_files/sample_text_better.txt";

//    textProcessor.open(fileNameTwo);
//
//    for(const auto &e : textProcessor.getLines())
//    {
//        cout << e->getStringValue() << endl;
//    }

//    commandHandler.handleCommand("print");

//    std::vector<FileData> data;
//
//
//    test(data);
//
//    for(const auto &el : data){
//        for (const auto &line: el.lines) {
//            cout << line->getStringValue() << endl;
//        }
//    }

    commandHandler.startConsoleUi();
}
