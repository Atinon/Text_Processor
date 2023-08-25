#ifndef TEXT_PROCESSOR_BASELINE_H
#define TEXT_PROCESSOR_BASELINE_H

#include <string>

/**
 * Abstract Line class for shared functionality for all of it's derived ones.
 */
class BaseLine {
protected:
    std::string stringValue_;

public:
    enum LineTypes {
        REGULAR,
        QUOTED,
        BULLET_POINT,
        NUMBER,
    };

    explicit BaseLine(const std::string &stringValue) : stringValue_(stringValue) {};

    virtual LineTypes getType() const = 0;

    const std::string &getStringValue() const;

    virtual void setStringValue(const std::string &stringValue) = 0;

    virtual BaseLine *clone() = 0;

    virtual ~BaseLine() = default;
};


#endif //TEXT_PROCESSOR_BASELINE_H
