#ifndef TEXT_PROCESSOR_BASELINEDERIVEDCLASSES_H
#define TEXT_PROCESSOR_BASELINEDERIVEDCLASSES_H

#include "BaseLine.h"

/**
 * This class is inherited by Line classes that have the ability to change the casing of their letters.
 */
class CaseConverter {
protected:
    static void toLowerDefault(std::string &stringRef);

    static void toUpperDefault(std::string &stringRef);

public:
    virtual void toLower() = 0;

    virtual void toUpper() = 0;

    virtual ~CaseConverter() = default;
};

// ---------------------------------------------------------------------------------------------------------------------

/**
 * This class is inherited by Line classes that have the ability trim excess whitespace characters.
 */
class WhitespaceTrimmer {
protected:
    static void trimLeftDefault(std::string &stringRef);

    static void trimRightDefault(std::string &stringRef);

public:
    virtual void trimLeft() = 0;

    virtual void trimRight() = 0;

    virtual ~WhitespaceTrimmer() = default;
};

// ---------------------------------------------------------------------------------------------------------------------

/**
 * This class represents all Lines that don't fit in the other categories. Just plain text.
 */
class RegularLine : public BaseLine, public CaseConverter, public WhitespaceTrimmer {

public:
    explicit RegularLine(const std::string &stringValue);

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
 * This class represents single and multi-line text that starts and ends with quotes.
 */
class QuotedLine : public BaseLine {

public:
    explicit QuotedLine(const std::string &stringValue);

    LineTypes getType() const override;

    void setStringValue(const std::string &stringValue) override;

    BaseLine *clone() override;

    ~QuotedLine() override = default;
};

// ---------------------------------------------------------------------------------------------------------------------

/**
 * This class represents text that starts with a number followed by a dot. For example: 1. Lorem Ipsum...
 */
class BulletPointLine : public BaseLine, public CaseConverter, public WhitespaceTrimmer {

public:
    explicit BulletPointLine(const std::string &stringValue);

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
 * This class represents numbers. It's value can be interpreted as a numeric one.
 */
class NumberLine : public BaseLine, public WhitespaceTrimmer {

public:
    explicit NumberLine(const std::string &stringValue);

    LineTypes getType() const override;

    void setStringValue(const std::string &stringValue) override;

    void trimLeft() override;

    void trimRight() override;

    BaseLine *clone() override;

    long long getNumericValue() const;

    ~NumberLine() override = default;
};


#endif //TEXT_PROCESSOR_BASELINEDERIVEDCLASSES_H
