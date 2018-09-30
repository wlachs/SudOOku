//
// Created by Borbély László on 2018. 09. 30..
//

#include "strategies.h"

std::vector<Matrix> GroupStrategy::separateToGroups(Matrix matrix) const {
    auto dimension = matrix.getDimension();
    auto groupDimension = lround(sqrt(dimension));
    std::vector<Matrix> result = {};

    for (unsigned short int horizontalGroups = 0; horizontalGroups < groupDimension; ++horizontalGroups) {
        for (unsigned short int verticalGroups = 0; verticalGroups < groupDimension; ++verticalGroups) {
            std::map<std::pair<unsigned short int, unsigned short int>, Field> group = {};

            for (unsigned short int x = 1; x <= groupDimension; ++x) {
                for (unsigned short int y = 1; y <= groupDimension; ++y) {
                    std::pair<unsigned short int, unsigned short int> coords =
                            {horizontalGroups * groupDimension + x, verticalGroups * groupDimension + y};
                    if (matrix[coords].getPossibleValues().size() == 1) {
                        group.insert({coords, matrix[coords].getPossibleValues()[0]});
                    }
                }
            }

            result.emplace_back((unsigned short int) groupDimension, group);
        }
    }

    return result;
}

bool GroupStrategy::singular(Matrix &matrix) const {
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

    for (Matrix &group : groups) {
        if (!singular(group)) {
            return false;
        }
    }

    return true;
}