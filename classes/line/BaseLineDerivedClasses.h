#ifndef TEXT_PROCESSOR_BASELINEDERIVEDCLASSES_H
#define TEXT_PROCESSOR_BASELINEDERIVEDCLASSES_H

#include "BaseLine.h"

class CaseConverter {
protected:
    static void toLower_(std::string &stringRef);

    static void toUpper_(std::string &stringRef);

public:
    virtual void toLower() = 0;

    virtual void toUpper() = 0;

    virtual ~CaseConverter() = default;
};

// ---------------------------------------------------------------------------------------------------------------------

class WhitespaceTrimmer {
protected:
    static void trimLeft_(std::string &stringRef);

    static void trimRight_(std::string &stringRef);

public:
    virtual void trimLeft() = 0;

    virtual void trimRight() = 0;

    virtual ~WhitespaceTrimmer() = default;
};

// ---------------------------------------------------------------------------------------------------------------------

class RegularLine : public BaseLine, public CaseConverter, public WhitespaceTrimmer {

public:
    explicit RegularLine(const std::string &stringValue);

    LineTypes getType() const override;

    void setStringValue(const std::string &stringValue) override;

    void toLower() override;

    void toUpper() override;

    void trimLeft() override;

    void trimRight() override;

    ~RegularLine() override = default;
};

// ---------------------------------------------------------------------------------------------------------------------

class QuotedLine : public BaseLine {

public:
    explicit QuotedLine(const std::string &stringValue);

    LineTypes getType() const override;

    void setStringValue(const std::string &stringValue) override;

    ~QuotedLine() override = default;
};

// ---------------------------------------------------------------------------------------------------------------------

class NumberAndDotLine : public BaseLine, public CaseConverter, public WhitespaceTrimmer {

public:
    explicit NumberAndDotLine(const std::string &stringValue);

    LineTypes getType() const override;

    void setStringValue(const std::string &stringValue) override;

    void toLower() override;

    void toUpper() override;

    void trimLeft() override;

    void trimRight() override;

    ~NumberAndDotLine() override = default;
};

// ---------------------------------------------------------------------------------------------------------------------

class NumberLine : public BaseLine, public WhitespaceTrimmer {

public:
    explicit NumberLine(const std::string &stringValue);

    LineTypes getType() const override;

    void setStringValue(const std::string &stringValue) override;

    void trimLeft() override;

    void trimRight() override;

    ~NumberLine() override = default;
};


#endif //TEXT_PROCESSOR_BASELINEDERIVEDCLASSES_H
