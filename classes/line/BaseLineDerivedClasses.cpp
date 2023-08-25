#include "BaseLineDerivedClasses.h"
#include "LineParser.h"


void CaseConverter::toLowerDefault(std::string &stringRef) {
    for (char &c: stringRef){
        c = tolower(c);
    }
}

void CaseConverter::toUpperDefault(std::string &stringRef) {
    for (char &c: stringRef){
        c = toupper(c);
    }
}

// ---------------------------------------------------------------------------------------------------------------------

void WhitespaceTrimmer::trimLeftDefault(std::string &stringRef) {
    size_t firstNotWhiteSpace = 0;

    while (firstNotWhiteSpace < stringRef.length() && isspace(stringRef[firstNotWhiteSpace])){
        firstNotWhiteSpace++;
    }

    stringRef = stringRef.substr(firstNotWhiteSpace);
}

void WhitespaceTrimmer::trimRightDefault(std::string &stringRef) {
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
    CaseConverter::toLowerDefault(stringValue_);
}

void RegularLine::toUpper() {
    CaseConverter::toUpperDefault(stringValue_);
}

void RegularLine::trimLeft() {
    WhitespaceTrimmer::trimLeftDefault(stringValue_);
}

void RegularLine::trimRight() {
    WhitespaceTrimmer::trimRightDefault(stringValue_);
}

BaseLine *RegularLine::clone() {
    return new RegularLine(*this);
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

BaseLine *QuotedLine::clone() {
    return new QuotedLine(*this);
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
    CaseConverter::toLowerDefault(stringValue_);
}

void NumberAndDotLine::toUpper() {
    CaseConverter::toUpperDefault(stringValue_);
}

void NumberAndDotLine::trimLeft() {
    WhitespaceTrimmer::trimLeftDefault(stringValue_);
}

void NumberAndDotLine::trimRight() {
    WhitespaceTrimmer::trimRightDefault(stringValue_);
}

BaseLine *NumberAndDotLine::clone() {
    return new NumberAndDotLine(*this);
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
    WhitespaceTrimmer::trimLeftDefault(stringValue_);
}

void NumberLine::trimRight() {
    WhitespaceTrimmer::trimRightDefault(stringValue_);
}

long long NumberLine::getNumericValue() const {
//    std::string temp = stringValue_;
//    WhitespaceTrimmer::trimLeftDefault(temp);
//    WhitespaceTrimmer::trimRightDefault(temp);

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

BaseLine *NumberLine::clone() {
    return new NumberLine(*this);
}
