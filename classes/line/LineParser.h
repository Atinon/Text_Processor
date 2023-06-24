#ifndef TEXT_PROCESSOR_LINEPARSER_H
#define TEXT_PROCESSOR_LINEPARSER_H


#include "BaseLine.h"

#include <vector>
#include <string>
#include <stdexcept>

class CaseConverter;
class WhitespaceTrimmer;

/**
 * This class is used for parsing raw strings, or vectors of such, and producing Line objects.
 *
 * Also provides methods for copying lines. Includes a dynamic_cast wrapper as well.
 */
class LineParser {
private:
    static const size_t NPOS_;

    static const char SPACE_CHAR_;

    static const char NEWLINE_CHAR_;

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

    static std::vector<BaseLine *> createFromStringVector(const std::vector<std::string> &rawData);

    static BaseLine* createFromString(const std::string &rawData);

    static BaseLine* parseTypeAndCreateCopy(BaseLine* line);

    static bool isNumberLine(const std::string &s);

    static bool isNumberAndDotLine(const std::string &s);

    static bool isQuotedLine(const std::string &s);

    static bool isRegularLine(const std::string &s);

    static CaseConverter* castToCaseConverter(BaseLine *line);
    static WhitespaceTrimmer* castToWhitespaceTrimmer(BaseLine *line);
};


#endif //TEXT_PROCESSOR_LINEPARSER_H
