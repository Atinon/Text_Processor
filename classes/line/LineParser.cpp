#include "LineParser.h"
#include "BaseLineDerivedClasses.h"

const size_t LineParser::NPOS_ = -1;

const char LineParser::SPACE_CHAR_ = ' ';

std::vector<BaseLine *> LineParser::createFromString(const std::vector<std::string> &rawData) {
    std::vector<BaseLine *> result;

    for (size_t i = 0; i < rawData.size(); ++i) {
        if (isNumberLine(rawData[i])) {
            pushNewLineToVectorOrThrow_(result, BaseLine::NUMBER, rawData[i]);
            continue;
        }

        if (isNumberAndDotLine(rawData[i])) {
            pushNewLineToVectorOrThrow_(result, BaseLine::NUMBER_AND_DOT, rawData[i]);
            continue;
        }

        if(createQuotedLineIfQualify_(i, rawData, result)){
            continue;
        }

        //Default case
        pushNewLineToVectorOrThrow_(result, BaseLine::REGULAR, rawData[i]);
    }

    return result;
}

// Currently only allowed empty symbols on the left side
bool LineParser::isNumberLine(const std::string &s) {
    bool charAlreadyFound = false;
    bool atLeastOneDigitFound = false;
    for (char c: s) {
        if(!charAlreadyFound && (!iswspace(c) || c != SPACE_CHAR_)){
            charAlreadyFound = true;
            if(isdigit(c)) {
                atLeastOneDigitFound = true;
            }
        }

        if(charAlreadyFound){
            if (!isdigit(c)) {
                return false;
            }
        }
    }
    return atLeastOneDigitFound;
}

bool LineParser::isNumberAndDotLine(const std::string &s) {
    size_t offset = 0, firstIndex = 0, secondIndex = 1;

    for (int i = 0; i < s.length(); ++i) {
        if(iswspace(s[i]) || s[i] == SPACE_CHAR_){
            offset++;
            firstIndex++;
            secondIndex++;
            continue;
        }
        if (s.length() >= 2 + offset && isdigit(s[firstIndex]) && s[secondIndex] == '.') {
            return true;
        }
    }

    return false;
}

bool LineParser::isQuotedLine(const std::string &s) {
    int quoteCount = 0;
    for(char c : s){
        if(c == '"') quoteCount++;
    }
    if(quoteCount != 2) {
        return false;
    }

    if(getStringIndexIfStartsWithQuote_(s) != NPOS_){
        if(getStringIndexIfEndsWithQuote_(s) != NPOS_){
            return true;
        }
    }
    return false;
}

size_t LineParser::getStringIndexIfStartsWithQuote_(const std::string &s) {
    for (size_t i = 0; i < s.length(); ++i) {
        if (iswspace(s[i]) || s[i] == SPACE_CHAR_) {
            continue;
        }
        if (s[i] == '"') {
            return i;
        }
        return NPOS_;
    }
    return NPOS_;
}

size_t LineParser::getStringIndexIfEndsWithQuote_(const std::string &s) {
    for (size_t i = s.length(); i > 0; --i) {
        // First char should not be inspected, as it is presumed to be the opening quote
        if(i == 1){
            return NPOS_;
        }

        if (iswspace(s[i - 1]) || s[i - 1] == SPACE_CHAR_) {
            continue;
        }
        if (s[i - 1] == '"') {
            return i;
        }
        return NPOS_;
    }
    return NPOS_;
}

size_t LineParser::getVectorIndexIfEndQuoteFound_
        (const std::vector<std::string> &rawData, size_t vectorStartIndex, size_t stringStartIndex) {
    for (size_t lineIndex = vectorStartIndex; lineIndex < rawData.size(); ++lineIndex) {
        for (size_t charIndex = stringStartIndex; charIndex < rawData[lineIndex].length(); ++charIndex) {
            if(rawData[lineIndex][charIndex] == '"'){
                return lineIndex;
            }
        }
    }
    return NPOS_;
}

bool LineParser::createQuotedLineIfQualify_
        (size_t &rawDataIndexRef, const std::vector<std::string> &rawData, std::vector<BaseLine*> &resultRef) {
    size_t openQuoteIndex = getStringIndexIfStartsWithQuote_(rawData[rawDataIndexRef]);
    if (openQuoteIndex != NPOS_) {
        size_t stringStartingIndex = openQuoteIndex + 1;
        size_t vectorLineIndexWithClosingQuote =
                getVectorIndexIfEndQuoteFound_(rawData, rawDataIndexRef, stringStartingIndex);
        if(vectorLineIndexWithClosingQuote != NPOS_){
            std::string resultingString;
            for (size_t j = rawDataIndexRef; j < vectorLineIndexWithClosingQuote + 1; ++j) {
                resultingString += rawData[j];
                if(j < vectorLineIndexWithClosingQuote) resultingString += '\n';
            }
            pushNewLineToVectorOrThrow_(resultRef, BaseLine::QUOTED, resultingString);
            rawDataIndexRef = vectorLineIndexWithClosingQuote;
            return true;
        }
    }
    return false;
}

void LineParser::pushNewLineToVectorOrThrow_(std::vector<BaseLine *> &resultRef, BaseLine::LineTypes type,
                                             const std::string &stringValue) {
    try{
        switch(type){
            case BaseLine::REGULAR:
                resultRef.push_back(new RegularLine(stringValue));
                return;
            case BaseLine::NUMBER:
                resultRef.push_back(new NumberLine(stringValue));
                return;
            case BaseLine::NUMBER_AND_DOT:
                resultRef.push_back(new NumberAndDotLine(stringValue));
                return;
            case BaseLine::QUOTED:
                resultRef.push_back(new QuotedLine(stringValue));
                return;
            default:
                throw std::invalid_argument("Invalid Line Type!");
        }
    }
    catch(const std::bad_alloc &){
        for (BaseLine* &i : resultRef) {
            delete i;
        }
        resultRef.clear();
        throw std::runtime_error("Failed to allocate enough memory.");
    }
}
