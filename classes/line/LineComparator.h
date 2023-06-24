#ifndef TEXT_PROCESSOR_LINECOMPARATOR_H
#define TEXT_PROCESSOR_LINECOMPARATOR_H


#include "BaseLine.h"

/**
 * This class provides a sorting operator to use with sorting functions.
 *
 * It fits the criteria required.
 */
struct LineComparator {
    bool operator()(const BaseLine* lineOne, const BaseLine* lineTwo);
};


#endif //TEXT_PROCESSOR_LINECOMPARATOR_H
