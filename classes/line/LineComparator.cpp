#include "LineComparator.h"
#include "BaseLineDerivedClasses.h"

bool LineComparator::operator()(const BaseLine *lineOne, const BaseLine *lineTwo) {
    bool lineOneIsNumberAndDot = lineOne->getType() == BaseLine::NUMBER_AND_DOT;
    bool lineTwoIsNumberAndDot = lineTwo->getType() == BaseLine::NUMBER_AND_DOT;

    bool lineOneIsNumberLine = lineOne->getType() == BaseLine::NUMBER;
    bool lineTwoIsNumberLine = lineTwo->getType() == BaseLine::NUMBER;

    if(lineOneIsNumberAndDot && !lineTwoIsNumberAndDot){
        // lineOne is special and should not be moved (not placed before lineTwo)
        return false;
    }

    else if (!lineOneIsNumberAndDot && lineTwoIsNumberAndDot){
        // lineTwo is special and should not be moved (lineTwo is in the right place after lineOne)
        return true;
    }

    else if(lineOneIsNumberLine && lineTwoIsNumberLine){
        const NumberLine* numberOne = dynamic_cast<const NumberLine*>(lineOne);
        const NumberLine* numberTwo = dynamic_cast<const NumberLine*>(lineTwo);

        if(numberOne && numberTwo){
            return numberOne->getNumericValue() < numberTwo->getNumericValue();
        }
        else{
            return true;
        }
    }

    else {
        // Lexicographical comparison
        return lineOne->getStringValue() < lineTwo->getStringValue();
    }
}
