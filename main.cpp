//
// Created by Borbély László on 2018. 09. 15..
//

#include "sudooku_core/matrix/field.h"
#include "sudooku_core/matrix/matrix.h"
#include "sudooku_core/solvers/solver.h"
#include "sudooku_core/strategies/strategies.h"
#include "sudooku_core/matrix/matrixReader.h"

std::vector<Matrix> getTests() {
    return {
            (Matrix) MatrixReader{"../sudooku_tests/testInputs/test1.mat"},
            (Matrix) MatrixReader{"../sudooku_tests/testInputs/test2.mat"},
            (Matrix) MatrixReader{"../sudooku_tests/testInputs/test3.mat"},
            (Matrix) MatrixReader{"../sudooku_tests/testInputs/test4.mat"},
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