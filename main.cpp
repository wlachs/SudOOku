//
// Created by Borbély László on 2018. 09. 15..
//

#include <iostream>
#include "matrix/field.h"
#include "matrix/matrix.h"
#include "solvers/solver.h"
#include "strategies/strategies.h"
#include "matrix/matrixReader.h"

std::vector<Matrix> getTests() {
    return {
            (Matrix) MatrixReader{"../tests/test1.txt"},
            (Matrix) MatrixReader{"../tests/test2.txt"},
            (Matrix) MatrixReader{"../tests/test3.txt"},
            (Matrix) MatrixReader{"../tests/test4.txt"},
    };
}

void runTest(Solver &solver, Matrix const &matrix) {
    solver.setInitialMatrix(matrix);
    solver.solve();

    auto solutions = solver.getSolutions();

    for (Matrix const &solution : solutions) {
        std::cout << solution << std::endl;
    }
}

void test() {
    Solver solver{};

    RowStrategy rowStrategy{};
    ColumnStrategy columnStrategy{};
    GroupStrategy groupStrategy{};

    solver.addRule(&rowStrategy);
    solver.addRule(&columnStrategy);
    solver.addRule(&groupStrategy);

    auto tests = getTests();

    for (Matrix const &test : tests) {
        runTest(solver, test);
    }
}

int main() {
    test();
    return 0;
}