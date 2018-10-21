//
// Created by Borbély László on 2018. 09. 15..
//

#include <matrix/matrixReader.h>
#include <solvers/solver.h>
#include <strategies/rowStrategy.h>
#include <strategies/groupStrategy.h>
#include <strategies/columnStrategy.h>

Matrix getFromFile(char *location) {
    return (Matrix) MatrixReader{location};
}

void runTest(Solver &solver, Matrix const &matrix) {
    solver.setInitialMatrix(matrix);
    solver.solve();

    auto solutions = solver.getSolutions();

    for (Matrix const &solution : solutions) {
        std::cout << solution << std::endl;
    }
}

void run(std::vector<Matrix> const &tests) {
    Solver solver{};

    RowStrategy rowStrategy{};
    ColumnStrategy columnStrategy{};
    GroupStrategy groupStrategy{};

    solver.addRule(&rowStrategy);
    solver.addRule(&columnStrategy);
    solver.addRule(&groupStrategy);

    for (Matrix const &test : tests) {
        runTest(solver, test);
    }
}

int main(int argc, char *argv[]) {
    if (argc > 1) {
        std::vector<Matrix> matrix = {getFromFile(argv[1])};
        run({matrix});
    }

    return 0;
}