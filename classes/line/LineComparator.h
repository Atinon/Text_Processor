#ifndef TEXT_PROCESSOR_LINECOMPARATOR_H
#define TEXT_PROCESSOR_LINECOMPARATOR_H


#include "BaseLine.h"

/**
 * @struct LineComparator
 * @brief Provides a sorting operator for sorting functions to compare BaseLine objects.
 *
 * This struct defines a sorting operator that can be used with various sorting algorithms
 * to compare two BaseLine objects. It follows the required criteria for sorting.
 */
struct LineComparator {
    bool operator()(const BaseLine* lineOne, const BaseLine* lineTwo);
};


#endif //TEXT_PROCESSOR_LINECOMPARATOR_H
