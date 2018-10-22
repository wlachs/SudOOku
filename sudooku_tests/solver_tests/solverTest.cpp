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
    Matrix m1;
    Solver s1;
    std::vector<SolvingStrategy *> rules;

    void SetUp() override {
        m1 = (Matrix) MatrixReader{"small1.mat"};
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
    s1.setInitialMatrix(m1);
    s1.solve();
    auto solutions = s1.getSolutions();

    ASSERT_GT(solutions.size(), 1);
}