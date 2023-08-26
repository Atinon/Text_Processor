#ifndef TEXT_PROCESSOR_BASELINEDERIVEDCLASSES_H
#define TEXT_PROCESSOR_BASELINEDERIVEDCLASSES_H

#include "BaseLine.h"

/**
 * @class CaseConverter
 * @brief Base class for line classes that can change the casing of their letters.
 *
 * This class provides an interface for line classes that need to perform letter casing conversions.
 */
class CaseConverter {
protected:
    /**
    * @brief Convert the string to lowercase using the default implementation.
    * @param stringRef Reference to the string to be converted.
    */
    static void toLowerDefault(std::string &stringRef);

    /**
     * @brief Convert the string to uppercase using the default implementation.
    * @param stringRef Reference to the string to be converted.
     */
    static void toUpperDefault(std::string &stringRef);

public:
    virtual void toLower() = 0;

    virtual void toUpper() = 0;

    virtual ~CaseConverter() = default;
};

// ---------------------------------------------------------------------------------------------------------------------

/**
 * @class WhitespaceTrimmer
 * @brief Base class for line classes that can trim excess whitespace characters.
 *
 * This class provides an interface for line classes that need to perform whitespace trimming operations.
 */
class WhitespaceTrimmer {
protected:
    /**
    * @brief Trim whitespace characters from the left of the string using the default implementation.
    * @param stringRef Reference to the string to be trimmed.
    */
    static void trimLeftDefault(std::string &stringRef);

    /**
     * @brief Trim whitespace characters from the right of the string using the default implementation.
    * @param stringRef Reference to the string to be trimmed.
    */
    static void trimRightDefault(std::string &stringRef);

public:
    virtual void trimLeft() = 0;

    virtual void trimRight() = 0;

    virtual ~WhitespaceTrimmer() = default;
};

// ---------------------------------------------------------------------------------------------------------------------

/*
 * All the BaseLine derived classes are tightly coupled with the LineParser class.
 * It is responsible for creating the correct classes for each line(or block) of raw text.
 * The setter methods for each line type use the LineParser functionality.
 * LineParser is declared a friend class to all derived classes to indicate this.
 * LineParser can use the protected constructor with string value to construct line objects.
 */

// ---------------------------------------------------------------------------------------------------------------------

/**
 * @class RegularLine
 * @brief Represents all Lines that don't fit in the other categories. Just plain text.
 *
 * This class inherits from BaseLine and provides functionality for changing casing and trimming whitespace.
 */
class RegularLine : public BaseLine, public CaseConverter, public WhitespaceTrimmer {
protected:
    friend class LineParser;

    explicit RegularLine(const std::string &stringValue);
public:
    RegularLine() = default;

    LineTypes getType() const override;

    void setStringValue(const std::string &stringValue) override;

    void toLower() override;

    void toUpper() override;

    void trimLeft() override;

    void trimRight() override;

    BaseLine *clone() override;

    ~RegularLine() override = default;
};

// ---------------------------------------------------------------------------------------------------------------------

/**
 * @class QuotedLine
 * @brief Represents single and multi-line text that starts and ends with quotes.
 *
 * This class inherits from BaseLine and provides basic quote-specific functionality.
 */
class QuotedLine : public BaseLine {
protected:
    friend class LineParser;

    explicit QuotedLine(const std::string &stringValue);
public:
    QuotedLine() = default;

    LineTypes getType() const override;

    void setStringValue(const std::string &stringValue) override;

    BaseLine *clone() override;

    ~QuotedLine() override = default;
};

// ---------------------------------------------------------------------------------------------------------------------

/**
 * @class BulletPointLine
 * @brief Represents text that starts with a number followed by a dot.
 *
 * This class inherits from BaseLine and provides casing and trimming functionality.
 */
class BulletPointLine : public BaseLine, public CaseConverter, public WhitespaceTrimmer {
protected:
    friend class LineParser;

    explicit BulletPointLine(const std::string &stringValue);
public:
    BulletPointLine() = default;

    LineTypes getType() const override;

    void setStringValue(const std::string &stringValue) override;

    void toLower() override;

    void toUpper() override;

    void trimLeft() override;

    void trimRight() override;

    BaseLine *clone() override;

    ~BulletPointLine() override = default;
};

// ---------------------------------------------------------------------------------------------------------------------

/**
 * @class NumberLine
 * @brief Represents text with a numeric value.
 *
 * This class inherits from BaseLine and provides whitespace trimming functionality.
 */
class NumberLine : public BaseLine, public WhitespaceTrimmer {
protected:
    friend class LineParser;

    explicit NumberLine(const std::string &stringValue);
public:
    NumberLine() = default;

    LineTypes getType() const override;

    void setStringValue(const std::string &stringValue) override;

    void trimLeft() override;

    void trimRight() override;

    BaseLine *clone() override;

    /**
    * @brief Get the numeric value of the number.
    * @return The numeric value of the number.
    */
    long long getNumericValue() const;

    ~NumberLine() override = default;
};


#endif //TEXT_PROCESSOR_BASELINEDERIVEDCLASSES_H
