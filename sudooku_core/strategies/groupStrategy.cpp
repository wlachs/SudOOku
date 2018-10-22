//
// Created by Borbély László on 2018. 09. 30..
//

#include "groupStrategy.h"
#include <cmath>
#include <algorithm>

std::vector<Matrix> GroupStrategy::separateToGroups() {
    auto groupDimension = sqrt(dimension);
    std::vector<Matrix> result = {};

    for (unsigned short int horizontalGroups = 0; horizontalGroups < groupDimension; ++horizontalGroups) {
        for (unsigned short int verticalGroups = 0; verticalGroups < groupDimension; ++verticalGroups) {
            std::map<std::pair<unsigned short int, unsigned short int>, Field> group = {};

            for (unsigned short int x = 1; x <= groupDimension; ++x) {
                for (unsigned short int y = 1; y <= groupDimension; ++y) {
                    std::pair<unsigned short int, unsigned short int> coordinates =
                            {horizontalGroups * groupDimension + x, verticalGroups * groupDimension + y};
                    auto possibleValues = (*constMatrix)[coordinates].getPossibleValues();
                    if (possibleValues.size() == 1) {
                        group.insert({{x, y}, Field{possibleValues[0]}});
                    }
                }
            }

            Matrix temp{(unsigned short int) groupDimension, group};
            result.push_back(temp);
        }
    }

    return result;
}

bool GroupStrategy::singular(Matrix const &matrix) const {
    std::vector<unsigned short int> elements = {};
    auto group_dimension = matrix.getDimension();

    for (unsigned short int x = 1; x <= group_dimension; ++x) {
        for (unsigned short int y = 1; y <= group_dimension; ++y) {
            auto list = matrix[{x, y}].getPossibleValues();

            if (list.size() == 1) {
                auto result = std::find(std::begin(elements), std::end(elements), list[0]);

                if (result != std::end(elements)) {
                    return false;
                }

                elements.push_back(list[0]);
            }
        }
    }

    return true;
}

bool GroupStrategy::validate(Matrix const &m) {
    constMatrix = &m;
    dimension = constMatrix->getDimension();

    auto groups = separateToGroups();

    for (Matrix const &group : groups) {
        if (!singular(group)) {
            return false;
        }
    }

    return true;
}

bool GroupStrategy::simplify(Matrix &m) {
    matrix = &m;
    dimension = matrix->getDimension();
    bool simplified = false;

    auto groupCoordinates = getGroupCoordinates();

    for (auto const &group : groupCoordinates) {
        if (simplifyGroup(group)) {
            simplified = true;
        }
    }

    return simplified;
}

bool GroupStrategy::simplifyGroup(std::vector<std::pair<unsigned short int, unsigned short int>> const &group) {
    bool simplified = false;

    for (auto const &coordinate : group) {
        auto values = (*matrix)[coordinate].getPossibleValues();

        if (values.size() == 1) {
            simplified = removeFromGroup(group, coordinate, values[0]) || simplified;
        } else if (values.size() > 1) {
            simplified = optimizeUnique(group, coordinate, values) || simplified;
        }
    }

    return simplified;
}

bool GroupStrategy::optimizeUnique(std::vector<std::pair<unsigned short int, unsigned short int>> const &group,
                                   std::pair<unsigned short int, unsigned short int> const &coordinate,
                                   std::vector<unsigned short int> const &values) const {
    for (auto value : values) {
        if (isUniqueInGroup(group, value)) {
            (*matrix)[coordinate].fixValue(value);
            return true;
        }
    }

    return false;
}

bool GroupStrategy::isUniqueInGroup(std::vector<std::pair<unsigned short int, unsigned short int>> const &group,
                                    unsigned short const int value) const {
    unsigned short int count = 0;

    for (auto const &coordinate : group) {
        if ((*matrix)[coordinate].contains(value)) {
            ++count;
        }
    }

    return count == 1;
}

bool GroupStrategy::removeFromGroup(std::vector<std::pair<unsigned short int, unsigned short int>> const &group,
                                    std::pair<unsigned short int, unsigned short int> const &ignore,
                                    unsigned short const int value) const {
    bool simplified = false;

    for (auto const &coordinate : group) {
        if (coordinate != ignore && (*matrix)[coordinate].removeValue(value)) {
            simplified = true;
        }
    }

    return simplified;
}

std::vector<std::vector<std::pair<unsigned short int, unsigned short int>>> GroupStrategy::getGroupCoordinates() const {
    auto groupDimension = sqrt(dimension);
    std::vector<std::vector<std::pair<unsigned short int, unsigned short int>>> result = {};

    for (unsigned short int horizontalGroups = 0; horizontalGroups < groupDimension; ++horizontalGroups) {
        for (unsigned short int verticalGroups = 0; verticalGroups < groupDimension; ++verticalGroups) {
            std::vector<std::pair<unsigned short int, unsigned short int>> group = {};

            for (unsigned short int x = 1; x <= groupDimension; ++x) {
                for (unsigned short int y = 1; y <= groupDimension; ++y) {
                    group.emplace_back(horizontalGroups * groupDimension + x, verticalGroups * groupDimension + y);
                }
            }

            result.push_back(group);
        }
    }

    return result;
}