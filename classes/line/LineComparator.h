#ifndef TEXT_PROCESSOR_LINECOMPARATOR_H
#define TEXT_PROCESSOR_LINECOMPARATOR_H


#include "BaseLine.h"

struct LineComparator {
    bool operator()(const BaseLine* lineOne, const BaseLine* lineTwo);
};


#endif //TEXT_PROCESSOR_LINECOMPARATOR_H
