#include "BaseLineDerivedClasses.h"
#include "LineParser.h"


RegularLine::RegularLine(const std::string &stringValue) : BaseLine(stringValue) {}

BaseLine::LineTypes RegularLine::getType() const {
    return BaseLine::REGULAR;
}

void RegularLine::setStringValue(const std::string &stringValue) {
    stringValue_ = stringValue;
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

