//
// Created by Borbély László on 2018. 09. 30..
//

//
// Created by Borbély László on 2018. 09. 15..
//

#include "strategies.h"

bool ColumnStrategy::validate(Matrix const &matrix) const {
    auto dimension = matrix.getDimension();
    auto cloned = matrix.clone();

    for (unsigned short int column = 1; column <= dimension; ++column) {
        std::vector<unsigned short int> fixValues = {};
        for (unsigned short int row = 1; row <= dimension; ++row) {
            if (cloned[{row, column}].getPossibleValues().size() == 1) {
                auto fixValue = cloned[{row, column}].getPossibleValues()[0];
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