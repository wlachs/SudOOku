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
            {{3, 1}, 2},
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

void groupStrategyTest1() {
    std::map<std::pair<unsigned short int, unsigned short int>, Field> input = {
            {{1, 1}, 7},
            {{1, 2}, 2},
            {{1, 3}, 3},
            {{1, 4}, 4},
            {{1, 5}, 5},
            {{1, 5}, 1},
            {{1, 6}, 6},
            {{1, 8}, 9},
            {{1, 9}, 8},

            {{2, 1}, 6},
            {{2, 2}, 1},
            {{2, 3}, 5},
            {{2, 4}, 3},
            {{2, 5}, 9},
            {{2, 6}, 7},
            {{2, 7}, 4},
            {{2, 8}, 8},
            {{2, 9}, 2},

            {{3, 1}, 8},
            {{3, 2}, 4},
            {{3, 3}, 9},
            {{3, 4}, 2},
            {{3, 5}, 1},
            {{3, 6}, 3},
            {{3, 7}, 5},
            {{3, 8}, 6},
            {{3, 9}, 7},

            {{4, 1}, 3},
            {{4, 2}, 7},
            {{4, 3}, 4},
            {{4, 4}, 5},
            {{4, 5}, 2},
            {{4, 6}, 6},
            {{4, 7}, 8},
            {{4, 8}, 1},
            {{4, 9}, 9},

            {{5, 2}, 8},
            {{5, 3}, 1},
            {{5, 4}, 6},
            {{5, 5}, 7},
            {{5, 6}, 9},
            {{5, 7}, 2},
            {{5, 8}, 4},
            {{5, 9}, 5},

            {{6, 1}, 4},
            {{6, 2}, 5},
            {{6, 3}, 2},
            {{6, 4}, 9},
            {{6, 5}, 6},
            {{6, 6}, 8},
            {{6, 7}, 1},
            {{6, 8}, 7},
            {{6, 9}, 3},

            {{7, 1}, 5},
            {{7, 2}, 6},
            {{7, 3}, 7},
            {{7, 4}, 1},
            {{7, 5}, 3},
            {{7, 6}, 2},
            {{7, 7}, 9},
            {{7, 9}, 4},

            {{8, 1}, 2},
            {{8, 2}, 9},
            {{8, 3}, 8},
            {{8, 4}, 7},
            {{8, 6}, 4},
            {{8, 7}, 3},
            {{8, 8}, 5},
            {{8, 9}, 6},

            {{9, 1}, 9},
            {{9, 2}, 3},
            {{9, 3}, 6},
            {{9, 5}, 8},
            {{9, 6}, 5},
            {{9, 7}, 7},
            {{9, 8}, 2},
            {{9, 9}, 1},
    };

    Matrix matrix{9, input};
    GroupStrategy groupStrategy{};
    auto result = groupStrategy.validate(matrix);
    std::cout << result;
}

void groupStrategyTest2() {
    std::map<std::pair<unsigned short int, unsigned short int>, Field> input = {
            {{1, 1}, 7},
            {{1, 2}, 1},
            {{1, 3}, 6},
            {{1, 4}, 2},
            {{1, 5}, 5},
            {{1, 6}, 8},
            {{1, 7}, 4},
            {{1, 8}, 9},
            {{1, 9}, 3},

            {{2, 1}, 3},
            {{2, 2}, 4},
            {{2, 3}, 5},
            {{2, 4}, 6},
            {{2, 5}, 9},
            {{2, 6}, 7},
            {{2, 7}, 8},
            {{2, 8}, 1},
            {{2, 9}, 2},

            {{3, 1}, 8},
            {{3, 2}, 2},
            {{3, 3}, 9},
            {{3, 4}, 4},
            {{3, 5}, 1},
            {{3, 6}, 3},
            {{3, 7}, 7},
            {{3, 8}, 6},
            {{3, 9}, 5},

            {{4, 1}, 1},
            {{4, 2}, 5},
            {{4, 3}, 4},
            {{4, 4}, 8},
            {{4, 5}, 2},
            {{4, 6}, 6},
            {{4, 8}, 3},
            {{4, 9}, 7},

            {{5, 1}, 9},
            {{5, 2}, 8},
            {{5, 3}, 2},
            {{5, 4}, 3},
            {{5, 5}, 7},
            {{5, 6}, 1},
            {{5, 7}, 5},
            {{5, 8}, 4},
            {{5, 9}, 6},

            {{6, 1}, 6},
            {{6, 2}, 7},
            {{6, 3}, 3},
            {{6, 4}, 9},
            {{6, 5}, 4},
            {{6, 6}, 5},
            {{6, 7}, 1},
            {{6, 8}, 8},

            {{7, 1}, 5},
            {{7, 2}, 6},
            {{7, 3}, 8},
            {{7, 4}, 1},
            {{7, 5}, 3},
            {{7, 6}, 2},
            {{7, 7}, 9},
            {{7, 8}, 7},
            {{7, 9}, 4},

            {{8, 1}, 2},
            {{8, 2}, 9},
            {{8, 3}, 1},
            {{8, 4}, 7},
            {{8, 5}, 6},
            {{8, 6}, 4},
            {{8, 7}, 3},
            {{8, 8}, 5},
            {{8, 9}, 8},

            {{9, 1}, 4},
            {{9, 2}, 3},
            {{9, 3}, 7},
            {{9, 4}, 5},
            {{9, 5}, 8},
            {{9, 6}, 9},
            {{9, 7}, 6},
            {{9, 8}, 2},
            {{9, 9}, 1},
    };

    Matrix matrix{9, input};
    RowStrategy rowStrategy{};
    ColumnStrategy columnStrategy{};
    GroupStrategy groupStrategy{};

    auto result = rowStrategy.validate(matrix);
    std::cout << result;

    result = columnStrategy.validate(matrix);
    std::cout << result;

    result = groupStrategy.validate(matrix);
    std::cout << result;
}

int main() {
    groupStrategyTest2();
    exampleRun2();
    return 0;
}