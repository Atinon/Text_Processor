#include "LineParser.h"
#include "BaseLineDerivedClasses.h"

const size_t LineParser::NPOS_ = -1;

const char LineParser::SPACE_CHAR_ = ' ';

const char LineParser::NEWLINE_CHAR_ = '\n';

// might need to refactor later
std::vector<BaseLine *> LineParser::createFromStringVector(const std::vector<std::string> &rawData) {
    std::vector<BaseLine *> result;

    for (size_t i = 0; i < rawData.size(); ++i) {
        if (isNumberLine(rawData[i])) {
            pushNewLineToVectorOrThrow(result, BaseLine::NUMBER, rawData[i]);
            continue;
        }

        if (isNumberAndDotLine(rawData[i])) {
            pushNewLineToVectorOrThrow(result, BaseLine::BULLET_POINT, rawData[i]);
            continue;
        }

        if(createQuotedLineIfQualify(i, rawData, result)){
            continue;
        }

        //Default case
        //Might need to parsing for /n symbol later if vector is not previously curated
        pushNewLineToVectorOrThrow(result, BaseLine::REGULAR, rawData[i]);
    }

    return result;
}

BaseLine *LineParser::createFromString(const std::string &rawData) {
    try{
        BaseLine *newLine;

        if(isNumberLine(rawData)){
            newLine = new NumberLine(rawData);
        }
        else if (isNumberAndDotLine(rawData)){
            newLine = new BulletPointLine(rawData);
        }
        else if (isQuotedLine(rawData)){
            newLine = new QuotedLine(rawData);
        }
        else if (isRegularLine(rawData)){
            newLine = new RegularLine(rawData);
        }
        else{
            throw std::invalid_argument("Invalid line format.");
        }

        return newLine;
    }
    catch(const std::bad_alloc &){
        throw;
    }
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

    if(getStringIndexIfStartsWithQuote(s) != NPOS_){
        if(getStringIndexIfEndsWithQuote(s) != NPOS_){
            return true;
        }
    }
    return false;
}

bool LineParser::isRegularLine(const std::string &s) {
    for (char c : s) {
        if(c == NEWLINE_CHAR_){
            return false;
        }
    }
    return true;
}

size_t LineParser::getStringIndexIfStartsWithQuote(const std::string &s) {
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

size_t LineParser::getStringIndexIfEndsWithQuote(const std::string &s) {
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

size_t LineParser::getVectorIndexIfEndQuoteFound
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

bool LineParser::createQuotedLineIfQualify
        (size_t &rawDataIndexRef, const std::vector<std::string> &rawData, std::vector<BaseLine*> &resultRef) {
    size_t openQuoteIndex = getStringIndexIfStartsWithQuote(rawData[rawDataIndexRef]);
    if (openQuoteIndex != NPOS_) {
        size_t stringStartingIndex = openQuoteIndex + 1;
        size_t vectorLineIndexWithClosingQuote =
                getVectorIndexIfEndQuoteFound(rawData, rawDataIndexRef, stringStartingIndex);
        if(vectorLineIndexWithClosingQuote != NPOS_){
            std::string resultingString;
            for (size_t j = rawDataIndexRef; j < vectorLineIndexWithClosingQuote + 1; ++j) {
                resultingString += rawData[j];
                if(j < vectorLineIndexWithClosingQuote) resultingString += '\n';
            }
            pushNewLineToVectorOrThrow(resultRef, BaseLine::QUOTED, resultingString);
            rawDataIndexRef = vectorLineIndexWithClosingQuote;
            return true;
        }
    }
    return false;
}

void LineParser::pushNewLineToVectorOrThrow(std::vector<BaseLine *> &resultRef, BaseLine::LineTypes type,
                                            const std::string &stringValue) {
    try{
        switch(type){
            case BaseLine::REGULAR:
                resultRef.push_back(new RegularLine(stringValue));
                return;
            case BaseLine::NUMBER:
                resultRef.push_back(new NumberLine(stringValue));
                return;
            case BaseLine::BULLET_POINT:
                resultRef.push_back(new BulletPointLine(stringValue));
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

BaseLine *LineParser::parseTypeAndCreateCopy(BaseLine *line) {
    BaseLine *copiedLine = nullptr;

    if (NumberLine *numberLine = dynamic_cast<NumberLine *>(line)) {
        copiedLine = new (std::nothrow) NumberLine(*numberLine);
    }
    else if (BulletPointLine *numberAndDotLine = dynamic_cast<BulletPointLine *>(line)) {
        copiedLine = new (std::nothrow) BulletPointLine(*numberAndDotLine);
    }
    else if (QuotedLine *quotedLine = dynamic_cast<QuotedLine *>(line)) {
        copiedLine = new (std::nothrow) QuotedLine(*quotedLine);
    }
    else if (RegularLine *regularLine = dynamic_cast<RegularLine *>(line)) {
        copiedLine = new (std::nothrow) RegularLine(*regularLine);
    }

    return copiedLine;
}

CaseConverter *LineParser::castToCaseConverter(BaseLine *line) {
    return dynamic_cast<CaseConverter *>(line);
}

WhitespaceTrimmer *LineParser::castToWhitespaceTrimmer(BaseLine *line) {
    return dynamic_cast<WhitespaceTrimmer *>(line);
}
