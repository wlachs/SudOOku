//
// Created by Borbély László on 2018. 10. 22..
//

#include <gtest/gtest.h>
#include <solvers/solver.h>
#include <strategies/rowStrategy.h>
#include <strategies/columnStrategy.h>
#include <strategies/groupStrategy.h>
#include <matrix/matrixReader.h>

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
        for (auto p : rules) {
            delete p;
        }
    }
};

TEST_F(SolverTests, small_solvable_test) {
    Matrix matrix = (Matrix) MatrixReader{"small1.mat"};

    s1.setInitialMatrix(matrix);
    s1.solve();

    auto solutions = s1.getSolutions();
    ASSERT_GT(solutions.size(), 1);
}

TEST_F(SolverTests, small_not_solvable_test) {
    Matrix matrix = (Matrix) MatrixReader{"invalid1.mat"};

    s1.setInitialMatrix(matrix);
    s1.solve();

    auto solutions = s1.getSolutions();
    ASSERT_EQ(solutions.size(), 0);
}

TEST_F(SolverTests, each_solution_is_unique_test) {
    Matrix matrix = (Matrix) MatrixReader{"test3.mat"};

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