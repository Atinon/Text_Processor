#ifndef TEXT_PROCESSOR_BASELINE_H
#define TEXT_PROCESSOR_BASELINE_H

#include <string>

/**
 * @class BaseLine
 * @brief Base class for different types of lines.
 *
 * This class serves as the base for various line types such as Regular, Quoted, Bullet Point, and Number lines.
 */
class BaseLine {
protected:
    std::string stringValue_;

    BaseLine() = default;
public:
    /**
     * @enum LineTypes
     * @brief Enumeration of different line types.
     */
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
