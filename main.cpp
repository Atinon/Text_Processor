#include <iostream>

#include "classes/Config.h"
#include "classes/TextProcessor.h"
#include "classes/line/BaseLine.h"
#include "classes/line/LineParser.h"

using namespace std;


int main(){
    DefaultConfig defaultConfig;
    TextProcessor textProcessor(&defaultConfig);
    textProcessor.fileReader_->setFileName("sample_files/single_line_sample.txt");
    vector<string> rawData;
    try{
        rawData = textProcessor.fileReader_->readFileContent();
    }
    catch(const runtime_error &e){
        cout << e.what() << endl;
        return -1;
    }

    vector<BaseLine*> result;
    try{
        result = LineParser::createFromString(rawData);
    }
    catch(const std::runtime_error &re){
        cout << re.what() << endl;
    }
    catch(const std::invalid_argument &ie){
        cout << ie.what() << endl;
    }

    for (BaseLine *line : result) {
        cout << line->getStringValue() << " ||| Type: " << line->getType() << endl;
    }

    try{
        string hey = " \" \"";
        cout << hey << endl;
        result[0]->setStringValue(hey);
    }
    catch(const std::invalid_argument &e){
        cout << e.what();
        return -1;
    }
    cout << result[0]->getStringValue() << endl;
}
