//
// Created by Borbély László on 2018. 10. 21..
//

#include <gtest/gtest.h>
#include <sudooku_core/matrix/field.h>
#include <vector>

/**
 * Field test fixture class
 */
class FieldTests : public ::testing::Test {
protected:
    Field f1;

    /**
     * Setup method running before the execution of each test case
     */
    void SetUp() override {
        /* Initialize vector with the possible values of a 'dimension = 4' Matrix */
        std::vector<unsigned short int> possibleValues = {1, 2, 3, 4};

        /* Construct Field with the given base vector */
        f1 = Field{possibleValues};
    }
};

/**
 * Test case for the getter function of Field
 */
TEST_F(FieldTests, getter_test) {
    /* Get possible values */
    auto values = f1.getPossibleValues();

    /* The size of the retrieved vector must match the size of the vector constructed in the SetUp() function */
    ASSERT_EQ(4, values.size());

    /* If the vector size matches, check each value individually */
    for (unsigned short int i = 0; i < 4; ++i) {
        EXPECT_EQ(i + 1, values[i]);
    }
}

/**
 * Test case for the fixValue() method
 */
TEST_F(FieldTests, fixvalue_noarg_test) {
    /* Execute method */
    f1.fixValue();

    /* TODO: getPossibleValues() is called twice though it would be enough once */
    /* The length of the vector should equal 1 */
    ASSERT_EQ(1, f1.getPossibleValues().size());

    /* The value should be the first value of the vector defined in the SetUp() function */
    ASSERT_EQ(1, f1.getPossibleValues()[0]);
}

/**
 * Test case for the fixValue(...) method
 */
TEST_F(FieldTests, fixvalue_witharg_test) {
    /* Execute method */
    f1.fixValue(3);

    /* TODO: getPossibleValues() is called twice though it would be enough once */
    /* The length of the vector should equal 1 */
    ASSERT_EQ(1, f1.getPossibleValues().size());

    /* The value should be the value passed */
    ASSERT_EQ(3, f1.getPossibleValues()[0]);
}

/**
 * Test case for the removeValue() method
 */
TEST_F(FieldTests, removevalue_noarg_test) {
    /* Execute method */
    f1.removeValue();

    /* Store possible values */
    auto &values = f1.getPossibleValues();

    /* The size of the vector should be equal to 3 */
    ASSERT_EQ(3, values.size());

    /* The elements of the vector should be the three values in the base vector without the first one */
    for (unsigned short int i = 0; i < 3; ++i) {
        EXPECT_EQ(i + 2, values[i]);
    }
}

/**
 * Test case for the removeValue(...) method
 */
TEST_F(FieldTests, removevalue_witharg_test) {
    /* Execute method */
    f1.removeValue(4);

    /* Store possible values */
    auto values = f1.getPossibleValues();

    /* The size of the vector should be equal to 3 */
    ASSERT_EQ(3, values.size());

    /* The elements of the vector should be the three values in the base vector without the 3 */
    for (unsigned short int i = 0; i < 3; ++i) {
        EXPECT_EQ(i + 1, values[i]);
    }
}

/**
 * Test case for the removeValue(...) function where the value passed isn't a member of the Field vector
 */
TEST_F(FieldTests, removevalue_witharg_false_test) {
    /* Execute method
     * Should return false, as the value couldn't be removed */
    ASSERT_FALSE(f1.removeValue(5));

    /* Store possible values */
    auto values = f1.getPossibleValues();

    /* The size of the vector should remain 4 */
    ASSERT_EQ(4, values.size());

    /* The elements of the vector should be the four values in the base vector without any change */
    for (unsigned short int i = 0; i < 4; ++i) {
        EXPECT_EQ(i + 1, values[i]);
    }
}

/**
 * Test case for the contains(...) function of the Field class
 */
TEST_F(FieldTests, contains_test) {
    /* Initially the vector should contain the 4 values from the base vector */
    ASSERT_EQ(4, f1.getPossibleValues().size());

    /* For each of these values the contains function should return true */
    for (unsigned short int i = 1; i <= 4; ++i) {
        EXPECT_TRUE(f1.contains(i));
    }

    /* TODO: maybe a test with a false result would be nice too */
}