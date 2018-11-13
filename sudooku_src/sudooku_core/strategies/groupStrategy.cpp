//
// Created by Borbély László on 2018. 09. 30..
//

#include "groupStrategy.h"
#include <math.h>
#include <algorithm>

/**
 * Check whether Matrix is singluar
 * Each value in the Matrix should be present maximum once
 * Note that this only applies to distributed groups, doesn't apply for the whole puzzle
 * @param matrix_
 * @return
 */
bool
GroupStrategy::singular(std::vector<std::pair<unsigned short int, unsigned short int>> const &groupCoordinates) const {
    /* Initialize vector of visited elements */
    std::vector<unsigned short int> elements = {};

    /* Iterate through Matrix coordinates */
    for (auto const &coordinate : groupCoordinates) {
        /* Get possible values */
        auto const &list = (*constMatrix)[coordinate].getPossibleValues();

        /* If the Field value is fixed, check whether we already visited it once */
        if (list.size() == 1) {
            auto const result = std::find(std::begin(elements), std::end(elements), list[0]);

            /* If yes, the Matrix isn't singular */
            if (result != std::end(elements)) {
                return false;
            }

            /* Otherwise add it to the visited values vector */
            elements.push_back(list[0]);
        }
    }

    return true;
}

/**
 * Validate matrix
 * A Matrix is valid if each of it's groups contains every possible value maximum once
 * @param m
 * @return
 */
bool GroupStrategy::validate(Matrix const &m) {
    /* Save Matrix const reference and dimension as class variables */
    constMatrix = &m;
    dimension = constMatrix->getDimension();
    groupDimension = static_cast<unsigned short>(sqrt(dimension));

    /* Get group coordinates */
    auto const &groups = getGroupCoordinates();

    /* Check whether every group is valid */
    for (auto const &group : groups) {
        if (!singular(group)) {
            return false;
        }
    }

    return true;
}

/**
 * Simplify matrix
 * Go through each group and try to simplify the according to the rules
 * @param m
 * @return
 */
bool GroupStrategy::simplify(Matrix &m) {
    /* Save Matrix reference and dimension as class variables */
    matrix = &m;
    dimension = matrix->getDimension();
    groupDimension = static_cast<unsigned short>(sqrt(dimension));

    /* Store whether the Matrix has been successfully simplified */
    bool simplified = false;

    /* Get vector of vectors for each coordinate in the groups */
    auto const groupCoordinates = getGroupCoordinates();

    /* Try to simplify each group */
    for (auto const &group : groupCoordinates) {
        if (simplifyGroup(group)) {
            simplified = true;
        }
    }

    return simplified;
}

/**
 * Simplify group
 * The simplification uses two different strategies
 * 1. Find singular values
 * 2. Find unique values
 * @return
 */
bool GroupStrategy::simplifyGroup(std::vector<std::pair<unsigned short int, unsigned short int>> const &group) {
    /* Store whether the group has been successfully simplified */
    bool simplified = false;

    /* Check each group separately */
    for (auto const &coordinate : group) {
        /* Store group values */
        auto const &values = (*matrix)[coordinate].getPossibleValues();

        if (values.size() == 1) {
            /* If there is only one possible value in the Field, remove it from all other positions in the group */
            simplified = removeFromGroup(group, coordinate, values[0]) || simplified;
        } else if (values.size() > 1) {
            /* If there are multiple values in the Field, try finding unique values */
            simplified = optimizeUnique(group, coordinate, values) || simplified;
        }
    }

    return simplified;
}

/**
 * Optimize unique values of the group
 * Check whether a value is unique in the group, if yes, replaces the Field with the singular value
 * @param group
 * @param coordinate
 * @param values
 * @return
 */
bool GroupStrategy::optimizeUnique(std::vector<std::pair<unsigned short int, unsigned short int>> const &group,
                                   std::pair<unsigned short int, unsigned short int> const &coordinate,
                                   std::vector<unsigned short int> const &values) const {
    /* Iterate over each value in the vector of values */
    for (auto const &value : values) {
        /* If a unique value is found, fix it */
        if (isUniqueInGroup(group, value)) {
            (*matrix)[coordinate].fixValue(value);

            /* Fixing a value means the optimization was successful */
            return true;
        }
    }

    return false;
}

/**
 * Check whether a value is unique in a group or not
 * Counts how many times each value is visited in a group. If this number is equal to 1, it is unique
 * @param group
 * @param value
 * @return
 */
bool GroupStrategy::isUniqueInGroup(std::vector<std::pair<unsigned short int, unsigned short int>> const &group,
                                    unsigned short const int value) const {
    /* Initialize hit counter */
    unsigned short int count = 0;

    /* Check for each coordinate in the group whether it possibly contains the searched value */
    for (auto const &coordinate : group) {
        /* Increase hit count if yes */
        if ((*matrix)[coordinate].contains(value)) {
            ++count;
        }
    }

    /* If the hit count equals 1, a unique value was found */
    return count == 1;
}

/**
 * Remove a certain value from each Field of a group except one specified by the ignore parameter
 * @param group
 * @param ignore
 * @param value
 * @return
 */
bool GroupStrategy::removeFromGroup(std::vector<std::pair<unsigned short int, unsigned short int>> const &group,
                                    std::pair<unsigned short int, unsigned short int> const &ignore,
                                    unsigned short const int value) const {
    /* Store whether the group has been successfully simplified */
    bool simplified = false;

    /* Iterate over each coordinate of the group */
    for (auto const &coordinate : group) {
        /* If the coordinate is not equal to the one in the ignore parameter, try to remove value from it */
        if (coordinate != ignore && (*matrix)[coordinate].removeValue(value)) {
            /* If a value was successfully removed, it means the optimization was successful */
            simplified = true;
        }
    }

    return simplified;
}

/**
 * Returns a vector of vectors containing the coordinates for each group in the Matrix
 * @return
 */
std::vector<std::vector<std::pair<unsigned short int, unsigned short int>>> GroupStrategy::getGroupCoordinates() const {
    /* Initialize result vector */
    std::vector<std::vector<std::pair<unsigned short int, unsigned short int>>> result = {};

    /* Iterate over each group */
    for (unsigned short int horizontalGroups = 0; horizontalGroups < groupDimension; ++horizontalGroups) {
        for (unsigned short int verticalGroups = 0; verticalGroups < groupDimension; ++verticalGroups) {
            /* Initialize vector containing the coordinates of a certain group */
            std::vector<std::pair<unsigned short int, unsigned short int>> group = {};

            /* Calculate Field coordinates based on group index and group dimension */
            for (unsigned short int x = 1; x <= groupDimension; ++x) {
                for (unsigned short int y = 1; y <= groupDimension; ++y) {
                    /* Construct Field coordinates with the certain values in the vector */
                    group.emplace_back(horizontalGroups * groupDimension + x, verticalGroups * groupDimension + y);
                }
            }

            /* Place group Field coordinates vector to the result vector */
            result.push_back(group);
        }
    }

    return result;
}