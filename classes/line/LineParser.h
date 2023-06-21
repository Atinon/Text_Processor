#ifndef TEXT_PROCESSOR_LINEPARSER_H
#define TEXT_PROCESSOR_LINEPARSER_H


#include "BaseLine.h"

#include <vector>
#include <string>
#include <stdexcept>

class LineParser {
private:
    static const size_t NPOS_;

    static const char SPACE_CHAR_;

    static void pushNewLineToVectorOrThrow_
            (std::vector<BaseLine *> &resultRef, BaseLine::LineTypes type, const std::string &stringValue);

    static size_t getStringIndexIfStartsWithQuote_(const std::string &s);

    static size_t getStringIndexIfEndsWithQuote_(const std::string &s);

    static size_t getVectorIndexIfEndQuoteFound_
            (const std::vector<std::string> &rawData, size_t vectorStartIndex, size_t stringStartIndex);

    static bool createQuotedLineIfQualify_
    (size_t &rawDataIndexRef, const std::vector<std::string> &rawData, std::vector<BaseLine*> &resultRef);

public:
    LineParser() = default;

    static std::vector<BaseLine *> createFromString(const std::vector<std::string> &rawData);

    static bool isNumberLine(const std::string &s);

    static bool isNumberAndDotLine(const std::string &s);

    static bool isQuotedLine(const std::string &s);
};


#endif //TEXT_PROCESSOR_LINEPARSER_H
