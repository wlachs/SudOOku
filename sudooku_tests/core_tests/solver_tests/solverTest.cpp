//
// Created by Borbély László on 2018. 10. 22..
//

#include <gtest/gtest.h>
#include <sudooku_core/solvers/solver.h>
#include <sudooku_core/strategies/rowStrategy.h>
#include <sudooku_core/strategies/columnStrategy.h>
#include <sudooku_core/strategies/groupStrategy.h>
#include <sudooku_core/strategies/diagonalStrategy.h>
#include <sudooku_core/exceptions/noStrategiesException.h>
#include <sudooku_controller/handlers/input_handlers/fileInputHandler.h>
#include <sudooku_core/exceptions/noMatrixException.h>

/**
 * Solver test fixture class
 */
class SolverTests : public ::testing::Test {
protected:
    Solver s1;
    std::vector<SolvingStrategy *> rules;

    /**
     * Setup method running before the execution of each test case
     */
    void SetUp() override {
        /* Add SolvingStrategy pointers to the rule set */
        rules = {
                new RowStrategy{},
                new ColumnStrategy{},
                new GroupStrategy{}
        };

        /* Set rule vector of the Solver class */
        s1.setRules(rules);
    }

    /**
     * Teardown method running after the execution of each test case
     */
    void TearDown() override {
        /* Since there is no controller to free the pointers, we have to do it on our own */
        for (auto &p : rules) {
            delete p;
        }
    }
};

/**
 * Test case for solving a small solvable puzzle
 */
TEST_F(SolverTests, small_solvable_test) {
    /* Initialize puzzle */
    Matrix matrix = FileInputHandler{{false}, "small1.mat"}.readInput();

    /* Set it as the initial Matrix of the Solver */
    s1.setInitialMatrix(matrix);

    /* Execute solving method */
    s1.solve();

    /* Retrieve the solutions of the puzzle */
    auto solutions = s1.getSolutions();

    /* The puzzle should have at least one solution */
    ASSERT_GT(solutions.size(), 1);
}

/**
 * Test case for solving an unsolvable puzzle
 */
TEST_F(SolverTests, small_not_solvable_test) {
    /* Initialize puzzle */
    Matrix matrix = FileInputHandler{{false}, "invalid1.mat"}.readInput();

    /* Set it as the initial Matrix of the Solver */
    s1.setInitialMatrix(matrix);

    /* Execute solving method */
    s1.solve();

    /* Retrieve the solutions of the puzzle */
    auto solutions = s1.getSolutions();

    /* The puzzle shouldn't have any solutions */
    ASSERT_EQ(solutions.size(), 0);
}

/**
 * Test case for making sure each solution of a puzzle is unique
 */
TEST_F(SolverTests, each_solution_is_unique_test) {
    /* Initialize puzzle */
    Matrix matrix = FileInputHandler{{false}, "test3.mat"}.readInput();

    /* Set it as the initial Matrix of the Solver */
    s1.setInitialMatrix(matrix);

    /* Execute solving method */
    s1.solve();

    /* Retrieve the solutions of the puzzle */
    auto solutions = s1.getSolutions();

    /* The puzzle should have exactly 4 solutions */
    ASSERT_EQ(4, solutions.size());

    /* Check for each solution whether it's different from all other solutions */
    for (unsigned short int i = 0; i < 4; ++i) {
        for (unsigned short int j = 0; j < 4; ++j) {
            /* Don't compare to self */
            if (i != j) {
                EXPECT_NE(solutions[i], solutions[j]);
            }
        }
    }
}

/**
 * Test case to check solution using a special SolvingStrategy
 */
TEST_F(SolverTests, diagonal_test) {
    /* Initialize DiagonalStrategy */
    auto *diagonalStrategy = new DiagonalStrategy{};

    /* Add rule to the vector of strategies */
    rules.push_back(diagonalStrategy);

    /* Update vector in Solver */
    s1.addRule(diagonalStrategy);

    /* Read input puzzle */
    Matrix matrix = FileInputHandler{{false}, "test5.mat"}.readInput();

    /* Set it as the initial Matrix of the Solver */
    s1.setInitialMatrix(matrix);

    /* Execute solving method */
    s1.solve();

    /* Retrieve the solutions of the puzzle */
    auto solutions = s1.getSolutions();

    /* The puzzle should have exactly one solution, however more without the DiagonalStrategy */
    ASSERT_EQ(1, solutions.size());
}

/**
 * Test case to check what happens when a puzzle is solved without strategies
 */
TEST_F(SolverTests, solve_empty_strategies_test) {
    /* Initialize Solver */
    Solver solver{};

    /* Add initial Matrix to avoid getting different type of exception */
    solver.setInitialMatrix(Matrix{1, {{{1, 1}, Field{1}}}});

    /* Try running the solver without any strategies specified */
    try {
        /* Execute solving method */
        solver.solve();

        /* If the execution reaches this point, the test failed */
        FAIL() << "NoStrategiesException should have been thrown";
    }

        /* A specific type of exception should be thrown */
    catch (NoStrategiesException &e) {
        EXPECT_EQ(std::string{"No strategies specified!"}, e.what());
    }

        /* In case another type of exception is thrown, the test should fail */
    catch (...) {
        FAIL() << "Expected NoStrategiesException";
    }
}

/**
 * Test case to check what happens when a puzzle is solved without an initial Matrix
 */
TEST_F(SolverTests, solve_empty_matrix_test) {
    /* Initialize Solver */
    Solver solver{};

    /* Try running the solver without an initial Matrix specified */
    try {
        /* Execute solving method */
        solver.solve();

        /* If the execution reaches this point, the test failed */
        FAIL() << "NoMatrixException should have been thrown";
    }

        /* A specific type of exception should be thrown */
    catch (NoMatrixException &e) {
        EXPECT_EQ(std::string{"No initial Matrix provided!"}, e.what());
    }

        /* In case another type of exception is thrown, the test should fail */
    catch (...) {
        FAIL() << "Expected NoMatrixException";
    }
}