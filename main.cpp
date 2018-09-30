//
// Created by Borbély László on 2018. 09. 15..
//

#include <iostream>
#include "matrix/field.h"
#include "matrix/matrix.h"
#include "solvers/solver.h"
#include "strategies/strategies.h"

void exampleRun1() {
    std::map<std::pair<unsigned short int, unsigned short int>, Field> input = {
            {{1, 1}, 1},
            {{1, 2}, 2},
            {{1, 4}, 4},
            {{3, 4}, 1},
            {{4, 2}, 1},
            {{4, 4}, 3}
    };

    Matrix matrix1{4, input};
    Solver solver{};
    solver.setInitialMatrix(matrix1);

    RowStrategy rowStrategy{};
    ColumnStrategy columnStrategy{};
    GroupStrategy groupStrategy{};

    solver.addRule(&rowStrategy);
    solver.addRule(&columnStrategy);
    solver.addRule(&groupStrategy);

    solver.solve();

    auto solutions = solver.getSolutions();

    for (auto solution : solutions) {
        auto dimension = solution.getDimension();
        for (unsigned short int x = 1; x <= dimension; ++x) {
            for (unsigned short int y = 1; y <= dimension; ++y) {
                std::cout << solution[{x, y}].getPossibleValues()[0] << " ";
            }
            std::cout << std::endl;
        }
        std::cout << std::endl;
    }
}

void exampleRun2() {
    std::map<std::pair<unsigned short int, unsigned short int>, Field> input = {
            {{1, 1}, 7},
            {{1, 5}, 5},
            {{1, 8}, 9},

            {{2, 3}, 5},
            {{2, 6}, 7},
            {{2, 9}, 2},

            {{3, 3}, 9},
            {{3, 6}, 3},
            {{3, 8}, 6},

            {{4, 3}, 4},
            {{4, 6}, 6},

            {{5, 2}, 8},
            {{5, 5}, 7},
            {{5, 8}, 4},

            {{6, 4}, 9},
            {{6, 7}, 1},

            {{7, 2}, 6},
            {{7, 4}, 1},
            {{7, 7}, 9},

            {{8, 1}, 2},
            {{8, 4}, 7},
            {{8, 7}, 3},

            {{9, 2}, 3},
            {{9, 5}, 8},
            {{9, 9}, 1},
    };

    Matrix matrix1{9, input};
    Solver solver{};
    solver.setInitialMatrix(matrix1);

    RowStrategy rowStrategy{};
    ColumnStrategy columnStrategy{};
    GroupStrategy groupStrategy{};

    solver.addRule(&rowStrategy);
    solver.addRule(&columnStrategy);
    solver.addRule(&groupStrategy);

    solver.solve();

    auto solutions = solver.getSolutions();

    for (auto solution : solutions) {
        auto dimension = solution.getDimension();
        for (unsigned short int x = 1; x <= dimension; ++x) {
            for (unsigned short int y = 1; y <= dimension; ++y) {
                std::cout << solution[{x, y}].getPossibleValues()[0] << " ";
            }
            std::cout << std::endl;
        }
        std::cout << std::endl;
    }
}

int main() {
    exampleRun1();
    exampleRun2();
    return 0;
}