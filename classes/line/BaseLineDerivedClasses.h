#ifndef TEXT_PROCESSOR_BASELINEDERIVEDCLASSES_H
#define TEXT_PROCESSOR_BASELINEDERIVEDCLASSES_H

#include "BaseLine.h"


class RegularLine : public BaseLine {

public:
    explicit RegularLine(const std::string &stringValue);

    LineTypes getType() const override;

    void setStringValue(const std::string &stringValue) override;

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

class NumberAndDotLine : public BaseLine {

public:
    explicit NumberAndDotLine(const std::string &stringValue);

    LineTypes getType() const override;

    void setStringValue(const std::string &stringValue) override;

    ~NumberAndDotLine() override = default;
};

// ---------------------------------------------------------------------------------------------------------------------

class NumberLine : public BaseLine {

public:
    explicit NumberLine(const std::string &stringValue);

    LineTypes getType() const override;

    void setStringValue(const std::string &stringValue) override;

    ~NumberLine() override = default;
};

#endif //TEXT_PROCESSOR_BASELINEDERIVEDCLASSES_H
