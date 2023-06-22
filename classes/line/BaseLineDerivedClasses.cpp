#include "BaseLineDerivedClasses.h"
#include "LineParser.h"


void CaseConverter::toLower_(std::string &stringRef) {
    for (char &c: stringRef){
        c = tolower(c);
    }
}

void CaseConverter::toUpper_(std::string &stringRef) {
    for (char &c: stringRef){
        c = toupper(c);
    }
}

// ---------------------------------------------------------------------------------------------------------------------

void WhitespaceTrimmer::trimLeft_(std::string &stringRef) {
    size_t firstNotWhiteSpace = 0;

    while (firstNotWhiteSpace < stringRef.length() && isspace(stringRef[firstNotWhiteSpace])){
        firstNotWhiteSpace++;
    }

    stringRef = stringRef.substr(firstNotWhiteSpace);
}

void WhitespaceTrimmer::trimRight_(std::string &stringRef) {
    size_t lastNotWhiteSpace = stringRef.length();

    while (lastNotWhiteSpace > 0 && isspace(stringRef[lastNotWhiteSpace - 1])){
        lastNotWhiteSpace--;
    }

    stringRef = stringRef.substr(0, lastNotWhiteSpace);
}

// ---------------------------------------------------------------------------------------------------------------------

RegularLine::RegularLine(const std::string &stringValue) : BaseLine(stringValue) {}

BaseLine::LineTypes RegularLine::getType() const {
    return BaseLine::REGULAR;
}

void RegularLine::setStringValue(const std::string &stringValue) {
    stringValue_ = stringValue;
}

void RegularLine::toLower() {
    CaseConverter::toLower_(stringValue_);
}

void RegularLine::toUpper() {
    CaseConverter::toUpper_(stringValue_);
}

void RegularLine::trimLeft() {
    WhitespaceTrimmer::trimLeft_(stringValue_);
}

void RegularLine::trimRight() {
    WhitespaceTrimmer::trimRight_(stringValue_);
}

// ---------------------------------------------------------------------------------------------------------------------

QuotedLine::QuotedLine(const std::string &stringValue) : BaseLine(stringValue) {}

BaseLine::LineTypes QuotedLine::getType() const {
    return BaseLine::QUOTED;
}

void QuotedLine::setStringValue(const std::string &stringValue) {
    if (LineParser::isQuotedLine(stringValue)) {
        stringValue_ = stringValue;
        return;
    }
    throw std::invalid_argument("Provided value is not fit for QuotedLine.");
}

// ---------------------------------------------------------------------------------------------------------------------

NumberAndDotLine::NumberAndDotLine(const std::string &stringValue) : BaseLine(stringValue) {}

BaseLine::LineTypes NumberAndDotLine::getType() const {
    return BaseLine::NUMBER_AND_DOT;
}

void NumberAndDotLine::setStringValue(const std::string &stringValue) {
    if (LineParser::isNumberAndDotLine(stringValue)) {
        stringValue_ = stringValue;
        return;
    }
    throw std::invalid_argument("Provided value is not fit for NumberAndDotLine.");
}

void NumberAndDotLine::toLower() {
    CaseConverter::toLower_(stringValue_);
}

void NumberAndDotLine::toUpper() {
    CaseConverter::toUpper_(stringValue_);
}

void NumberAndDotLine::trimLeft() {
    WhitespaceTrimmer::trimLeft_(stringValue_);
}

void NumberAndDotLine::trimRight() {
    WhitespaceTrimmer::trimRight_(stringValue_);
}

// ---------------------------------------------------------------------------------------------------------------------

NumberLine::NumberLine(const std::string &stringValue) : BaseLine(stringValue) {}

BaseLine::LineTypes NumberLine::getType() const {
    return BaseLine::NUMBER;
}

void NumberLine::setStringValue(const std::string &stringValue) {
    if (LineParser::isNumberLine(stringValue)) {
        stringValue_ = stringValue;
        return;
    }
    throw std::invalid_argument("Provided value is not fit for NumberLine.");
}

void NumberLine::trimLeft() {
    WhitespaceTrimmer::trimLeft_(stringValue_);
}

void NumberLine::trimRight() {
    WhitespaceTrimmer::trimRight_(stringValue_);
}

long long NumberLine::getNumericValue() const {
//    std::string temp = stringValue_;
//    WhitespaceTrimmer::trimLeft_(temp);
//    WhitespaceTrimmer::trimRight_(temp);

    long long result;

    try{
        result = std::stoll(stringValue_);
    }
    catch(const std::out_of_range&){
        result = -1;
    }
    catch(const std::invalid_argument&){
        result = -1;
    }

    return result;
}