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


//    // ---------- reading
//    textProcessor.fileReader_->setFileName("sample_files/sample_text.txt");
//    vector<string> rawData;
//    try{
//        rawData = textProcessor.fileReader_->readFileContent();
//    }
//    catch(const runtime_error &e){
//        cout << e.what() << endl;
//        return -1;
//    }
//
//    // ---------- creating
//    vector<BaseLine*> result;
//    try{
//        result = LineParser::createFromStringVector(rawData);
//    }
//    catch(const std::runtime_error &re){
//        cout << re.what() << endl;
//    }
//    catch(const std::invalid_argument &ie){
//        cout << ie.what() << endl;
//    }
//
//    for (BaseLine *line : result) {
//        cout << line->getStringValue() << " ||| Type: " << line->getType() << endl;
//    }
//
//
//    // ---------- writing
//    textProcessor.fileWriter_->setFileName("sample_files/first_write_sample.txt");
//    try{
//        textProcessor.fileWriter_->writeFileContent(result);
//    }
//    catch(const std::runtime_error &e){
//        cout << e.what() << endl;
//        return -1;
//    }


    // ---------- command handler
    ConsoleCommandHandler commandHandler(&textProcessor);
    commandHandler.startConsoleUi();

}
