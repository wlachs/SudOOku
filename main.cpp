//
// Created by Borbély László on 2018. 09. 15..
//

#include <iostream>
#include "matrix/field.h"
#include "matrix/matrix.h"
#include "solvers/solver.h"
#include "strategies/rowStrategy.h"

int main() {
    std::map<std::pair<unsigned short int, unsigned short int>, Field> input = {
            {{1, 1}, 1},
            {{1, 2}, 2},
            {{1, 4}, 4},
            {{3, 1}, 2},
            {{3, 4}, 1},
            {{4, 2}, 1},
            {{4, 4}, 3}
    };

    Matrix matrix1{4, input};
    Solver solver{};
    RowStrategy rowStrategy{};

    solver.setInitialMatrix(matrix1);
    solver.addRule(&rowStrategy);

    solver.solve();

    auto solutions = solver.getSolutions();

    return 0;
}