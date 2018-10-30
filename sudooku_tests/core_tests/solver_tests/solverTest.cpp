//
// Created by Borbély László on 2018. 10. 22..
//

#include <gtest/gtest.h>
#include <solvers/solver.h>
#include <strategies/rowStrategy.h>
#include <strategies/columnStrategy.h>
#include <strategies/groupStrategy.h>
#include <strategies/diagonalStrategy.h>
#include <exceptions/noStrategiesException.h>
#include <handlers/input_handlers/fileInputHandler.h>

class SolverTests : public ::testing::Test {
protected:
    Solver s1;
    std::vector<SolvingStrategy *> rules;

    void SetUp() override {
        rules = {
                new RowStrategy{},
                new ColumnStrategy{},
                new GroupStrategy{}
        };

        for (auto const rule : rules) {
            s1.addRule(rule);
        }
    }

    void TearDown() override {
        for (auto &p : rules) {
            delete p;
        }
    }
};

TEST_F(SolverTests, small_solvable_test) {
    Matrix matrix = FileInputHandler{{false}, "small1.mat"}.readInput();

    s1.setInitialMatrix(matrix);
    s1.solve();

    auto solutions = s1.getSolutions();
    ASSERT_GT(solutions.size(), 1);
}

TEST_F(SolverTests, small_not_solvable_test) {
    Matrix matrix = FileInputHandler{{false}, "invalid1.mat"}.readInput();

    s1.setInitialMatrix(matrix);
    s1.solve();

    auto solutions = s1.getSolutions();
    ASSERT_EQ(solutions.size(), 0);
}

TEST_F(SolverTests, each_solution_is_unique_test) {
    Matrix matrix = FileInputHandler{{false}, "test3.mat"}.readInput();

    s1.setInitialMatrix(matrix);
    s1.solve();

    auto solutions = s1.getSolutions();
    ASSERT_EQ(4, solutions.size());

    for (unsigned short int i = 0; i < 4; ++i) {
        for (unsigned short int j = 0; j < 4; ++j) {
            if (i != j) {
                EXPECT_NE(solutions[i], solutions[j]);
            }
        }
    }
}

TEST_F(SolverTests, diagonal_test) {
    auto *diagonalStrategy = new DiagonalStrategy{};
    rules.push_back(diagonalStrategy);
    s1.addRule(diagonalStrategy);

    Matrix matrix = FileInputHandler{{false}, "test5.mat"}.readInput();

    s1.setInitialMatrix(matrix);
    s1.solve();

    auto solutions = s1.getSolutions();
    ASSERT_EQ(1, solutions.size());
}

TEST_F(SolverTests, solve_empty_test) {
    Solver solver{};

    try {
        solver.solve();
    }
    catch (NoStrategiesException &e) {
        EXPECT_EQ(std::string{"No strategies specified!"}, e.what());
    }
    catch (...) {
        FAIL() << "Expected NoStrategiesException";
    }
}