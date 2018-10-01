//
// Created by Borbély László on 2018. 09. 15..
//

#include "strategies.h"

bool RowStrategy::validate(Matrix const &matrix) const {
    auto dimension = matrix.getDimension();

    for (unsigned short int row = 1; row <= dimension; ++row) {
        std::vector<unsigned short int> fixValues = {};
        for (unsigned short int column = 1; column <= dimension; ++column) {
            if (matrix[{row, column}].getPossibleValues().size() == 1) {
                auto fixValue = matrix[{row, column}].getPossibleValues()[0];
                auto result = std::find(std::begin(fixValues), std::end(fixValues), fixValue);

                if (result != std::end(fixValues)) {
                    return false;
                }

                fixValues.push_back(fixValue);
            }
        }
    }

    return true;
}