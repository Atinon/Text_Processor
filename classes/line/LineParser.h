#ifndef TEXT_PROCESSOR_LINEPARSER_H
#define TEXT_PROCESSOR_LINEPARSER_H


#include "BaseLine.h"

#include <vector>
#include <string>
#include <stdexcept>

class CaseConverter;
class WhitespaceTrimmer;

/**
 * @class LineParser
 * @brief This class is used for parsing raw strings or vectors of strings and producing Line objects.
 *
 * LineParser provides methods for parsing various line types and creating Line objects from raw data.
 * It also includes utilities for casting to specific Line interfaces.
 */
class LineParser {
private:
    static const size_t NPOS_; ///< Represents an invalid size_t value.

    static const char SPACE_CHAR_; ///< Represents the space character.

    static const char NEWLINE_CHAR_; ///< Represents the newline character.

    /**
    * @brief Creates a new Line object and pushes it to the result vector or throws an exception.
    * @param resultRef Reference to the result vector.
    * @param type The Line type.
    * @param stringValue The string value of the Line.
    * @throw std::runtime_error If there's an issue pushing the Line to the result vector.
    */
    static void pushNewLineToVectorOrThrow
            (std::vector<BaseLine *> &resultRef, BaseLine::LineTypes type, const std::string &stringValue);

    /**
    * @brief Returns the index of the quote if the text starts with one or returns NPOS_.
    * @param s Raw string.
    * @return size_t type value of index or NPOS_ if not found.
    */
    static size_t getStringIndexIfStartsWithQuote(const std::string &s);

    /**
    * @brief Returns the index of the quote if the text ends with one or returns NPOS_.
    * @param s Raw string.
    * @return size_t type value of index or NPOS_ if not found.
    */
    static size_t getStringIndexIfEndsWithQuote(const std::string &s);

    /**
    * @brief From a vector of strings(lines of text), returns the index in the vector where end quote is found or NPOS_;
    * @param rawData Vector containing the lines of text.
    * @param vectorStartIndex Index in the vector from which after to start looking for end quote.
    * @param stringStartIndex Index in the actual line of text from which to start looking for end quote.
    * @return size_t type value of index or NPOS_ if not found.
    */
    static size_t getVectorIndexIfEndQuoteFound
            (const std::vector<std::string> &rawData, size_t vectorStartIndex, size_t stringStartIndex);

    /**
    * @brief Given a vector of strings try to match a quoted line type and push it to result vector.
    * @param rawDataIndexRef Reference to index from which to start looking.
    * @param rawData Vector with the lines of raw text.
    * @param resultRef Reference to the resulting vector which contains the Line objects.
    * @return Boolean showing whether or not it was created.
    */
    static bool createQuotedLineIfQualify
    (size_t &rawDataIndexRef, const std::vector<std::string> &rawData, std::vector<BaseLine*> &resultRef);

public:
    LineParser() = default;

    /**
    * @brief Creates a vector of Line objects from a vector of raw strings.
    * @param rawData The vector of raw strings(block of text).
    * @return A vector of pointers to dynamic created Line objects.
    */
    static std::vector<BaseLine *> createFromStringVector(const std::vector<std::string> &rawData);

    /**
    * @brief Creates a Line object from a raw string.
    * @param rawData The raw string.
    * @return A pointer to the created Line object.
    */
    static BaseLine* createFromString(const std::string &rawData);

    static bool isNumberLine(const std::string &s);

    static bool isBulletPointLine(const std::string &s);

    static bool isQuotedLine(const std::string &s);

    static bool isRegularLine(const std::string &s);

    /**
    * @brief Casts a Line object to the CaseConverter interface if applicable.
    * @param line The Line object.
    * @return A pointer to the CaseConverter interface of the Line if applicable, otherwise nullptr.
    */
    static CaseConverter* castToCaseConverter(BaseLine *line);

    /**
    * @brief Casts a Line object to the WhitespaceTrimmer interface if applicable.
    * @param line The Line object.
    * @return A pointer to the WhitespaceTrimmer interface of the Line if applicable, otherwise nullptr.
    */
    static WhitespaceTrimmer* castToWhitespaceTrimmer(BaseLine *line);
};


#endif //TEXT_PROCESSOR_LINEPARSER_H
