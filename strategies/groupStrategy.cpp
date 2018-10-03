//
// Created by Borbély László on 2018. 09. 30..
//

#include "strategies.h"
#include <cmath>

std::vector<Matrix> GroupStrategy::separateToGroups(Matrix const &matrix) const {
    auto dimension = matrix.getDimension();
    auto groupDimension = sqrt(dimension);
    std::vector<Matrix> result = {};

    for (unsigned short int horizontalGroups = 0; horizontalGroups < groupDimension; ++horizontalGroups) {
        for (unsigned short int verticalGroups = 0; verticalGroups < groupDimension; ++verticalGroups) {
            std::map<std::pair<unsigned short int, unsigned short int>, Field> group = {};

            for (unsigned short int x = 1; x <= groupDimension; ++x) {
                for (unsigned short int y = 1; y <= groupDimension; ++y) {
                    std::pair<unsigned short int, unsigned short int> coordinates =
                            {horizontalGroups * groupDimension + x, verticalGroups * groupDimension + y};
                    auto possibleValues = matrix[coordinates].getPossibleValues();
                    if (possibleValues.size() == 1) {
                        group.insert({{x, y}, possibleValues[0]});
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
    auto dimension = matrix.getDimension();

    for (unsigned short int x = 1; x <= dimension; ++x) {
        for (unsigned short int y = 1; y <= dimension; ++y) {
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

bool GroupStrategy::validate(Matrix const &matrix) const {
    auto groups = separateToGroups(matrix);

    for (Matrix const &group : groups) {
        if (!singular(group)) {
            return false;
        }
    }

    return true;
}

bool GroupStrategy::simplify(Matrix &matrix) const {
    bool simplified = false;
    std::vector<std::vector<std::pair<unsigned short int, unsigned short int>>> groupCoordinates = getGroupCoordinates(
            matrix);

    for (auto const &group : groupCoordinates) {
        if (simplifyGroup(matrix, group)) {
            simplified = true;
        }
    }

    return simplified;
}

bool GroupStrategy::simplifyGroup(Matrix &matrix,
                                  std::vector<std::pair<unsigned short int, unsigned short int>> const &group) const {
    bool singularResult = optimizeSingular(matrix, group);
    bool uniqueResult = optimizeUnique(matrix, group);

    return singularResult || uniqueResult;
}

bool GroupStrategy::optimizeSingular(Matrix &matrix,
                                     std::vector<std::pair<unsigned short int, unsigned short int>> const &group) const {
    bool simplified = false;

    for (auto const &coordinate : group) {
        auto values = matrix[coordinate].getPossibleValues();

        if (values.size() == 1) {
            if (removeFromGroup(matrix, group, coordinate, values[0])) {
                simplified = true;
            }
        }
    }

    return simplified;
}

bool GroupStrategy::optimizeUnique(Matrix &matrix,
                                   std::vector<std::pair<unsigned short int, unsigned short int>> const &group) const {
    for (auto const &coordinate : group) {
        auto possibleValues = matrix[coordinate].getPossibleValues();
        if (possibleValues.size() > 1) {
            for (auto value : matrix[coordinate].getPossibleValues()) {
                if (isUniqueInGroup(matrix, group, value)) {
                    matrix[coordinate].fixValue(value);
                    return true;
                }
            }
        }
    }

    return false;
}

bool GroupStrategy::isUniqueInGroup(Matrix const &matrix,
                                    std::vector<std::pair<unsigned short int, unsigned short int>> const &group,
                                    unsigned short const int value) const {
    unsigned short int count = 0;

    for (auto const &coordinate : group) {
        if (matrix[coordinate].contains(value)) {
            ++count;
        }
    }

    return count == 1;
}

bool GroupStrategy::removeFromGroup(Matrix &matrix,
                                    std::vector<std::pair<unsigned short int, unsigned short int>> const &group,
                                    std::pair<unsigned short int, unsigned short int> const &ignore,
                                    unsigned short const int value) const {
    bool simplified = false;

    for (auto const &coordinate : group) {
        if (coordinate != ignore) {
            if (matrix[coordinate].removeValue(value)) {
                simplified = true;
            }
        }
    }

    return simplified;
}

std::vector<std::vector<std::pair<unsigned short int, unsigned short int>>> GroupStrategy::getGroupCoordinates(
        Matrix const &matrix) const {
    auto dimension = matrix.getDimension();
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