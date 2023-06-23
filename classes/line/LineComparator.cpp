#include "LineComparator.h"
#include "BaseLineDerivedClasses.h"

bool LineComparator::operator()(const BaseLine *lineOne, const BaseLine *lineTwo) {
    if (lineOne->getType() == BaseLine::NUMBER && lineTwo->getType() == BaseLine::NUMBER) {
        // Compare NumberLines numerically
        const NumberLine *numberOne = dynamic_cast<const NumberLine *>(lineOne);
        const NumberLine *numberTwo = dynamic_cast<const NumberLine *>(lineTwo);
        if (numberOne && numberTwo) {
            return numberOne->getNumericValue() < numberTwo->getNumericValue();
        } else {
            // lineOne and lineTwo are considered equal
            return false;
        }
    } else {
        // Lexicographical comparison
        return lineOne->getStringValue() < lineTwo->getStringValue();
    }
}
