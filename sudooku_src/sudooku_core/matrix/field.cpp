//
// Created by Borbély László on 2018. 09. 15..
//

#include "field.h"
#include "matrix.h"
#include <algorithm>

/**
 * Initialize Field with a set of possible values
 * @param possibleValues_
 */
Field::Field(std::vector<unsigned short int> const &possibleValues_) : possibleValues(possibleValues_) {}

/**
 * Initialize Field with exactly one possible value
 * Gets called when the Field value is determined by the input
 * @param value
 */
Field::Field(unsigned short const int value) {
    /* Since the vector has initially no values, let's add only one */
    possibleValues.push_back(value);
}

/**
 * Returns a vector of all potential values in the Field
 * @return
 */
std::vector<unsigned short int> const &Field::getPossibleValues() const {
    return possibleValues;
}

/**
 * When the execution comes to a point where trivial simplification isn't possible any more
 * the Matrix will be forked. In this case all the values in the Field will be dropped except the first one
 */
void Field::fixValue() {
    /* Save the first value */
    auto value = possibleValues[0];

    /* Remove all elements of the vector */
    possibleValues.clear();

    /* Add the previously saved element */
    possibleValues.push_back(value);
}

/**
 * If fixing the first value isn't enough, this method overwrites the potential values with the
 * one passed as a parameter
 * @param value
 */
void Field::fixValue(unsigned short const int value) {
    /* TODO: Check if the value passed as a parameter is a member of possibleValues. If not: throw an exception */

    /* Remove all elements of the vector */
    possibleValues.clear();

    /* Add the value passed as a parameter */
    possibleValues.push_back(value);
}

/**
 * The counterpart of fixValue()
 * Removes the first element of the vector and leaves the rest
 * This way we can guarantee that there will be no solutions lost during the fork process
 */
void Field::removeValue() {
    /* Remove the first element from the vector by passing a begin iterator to the erase function */
    possibleValues.erase(std::begin(possibleValues));
}

/**
 * An improved version on the removeValue() method.
 * Tries to remove the value passed as a parameter and returns if the deletion was successful
 * This means the function returns true if the vector contained the passed value and false if not
 * @param value
 * @return
 */
bool Field::removeValue(unsigned short const int value) {
    /* TODO: contains function can be reused here */

    /* Try to find value in the vector */
    auto it = std::find(std::begin(possibleValues), std::end(possibleValues), value);

    /* If it's a member, delete it, otherwise leave as is */
    if (it != std::end(possibleValues)) {
        possibleValues.erase(it);
        return true;
    }

    return false;
}

/**
 * Function to determine whether a value is a member of the vector of potential values or not
 * @param value
 * @return
 */
bool Field::contains(unsigned short const int value) const {
    /* Iterators pointing to the beginning and the end of the vector */
    auto begin = std::begin(possibleValues);
    auto end = std::end(possibleValues);

    /* If the value isn't found, an iterator to the element after the last one is returned */
    return std::find(begin, end, value) != end;
}