//
// Created by Borbély László on 2018. 09. 15..
//

#include <utility>
#include "matrix.h"

/**
 * Matrix copy constructor
 * Initialize new Matrix with new ForkHelper
 * @param matrix
 */
Matrix::Matrix(Matrix const &matrix) {
    dimension = matrix.dimension;
    fields = matrix.fields;
    forkHelper = new ForkHelper{this};
}

/**
 * Populate all Fields with possible values from 1 to 'dimension'
 */
void Matrix::populateEmptyFields() {
    /* Vector containing all possible values for Field */
    std::vector<unsigned short int> allValues = {};

    /* Add elements to vector one-by-one */
    for (unsigned short int i = 1; i <= dimension; ++i) {
        allValues.push_back(i);
    }

    /* For every coordinate not containing a value, set the vector as the vector of possible values */
    for (unsigned short int row = 1; row <= dimension; ++row) {
        for (unsigned short int column = 1; column <= dimension; ++column) {
            if (fields.find(std::pair<unsigned short int, unsigned short int>(row, column)) == fields.end()) {
                fields[{row, column}] = Field(allValues);
            }
        }
    }
}

/**
 * Matrix 2param constructor
 * The "real" constructor of the Matrix class.
 * Takes the parameters: dimension and a prepopulated map of given values
 * @param dimension_
 * @param fields_
 */
Matrix::Matrix(unsigned short const int dimension_,
               std::map<std::pair<unsigned short int, unsigned short int>, Field> const &fields_)
        : dimension(dimension_), fields(fields_) {
    /* Populate empty fields */
    populateEmptyFields();

    /* Create a ForkHelper object */
    this->forkHelper = new ForkHelper{this};
}

/**
 * Matrix assignment operator
 * Assign the value of a matrix to the current one
 * @param matrix
 * @return reference of current object
 */
Matrix &Matrix::operator=(Matrix const &matrix) {
    /* Self assignment check
     * It is necessary otherwise the ForkHelper instance would be freed and never reallocated */
    if (this != &matrix) {
        delete forkHelper;
        dimension = matrix.dimension;
        fields = matrix.fields;
        forkHelper = new ForkHelper{this};
    }

    return *this;
}

/**
 * Matrix equality operator
 * Checks whether the values of two Matrices are identical
 * The instance of *ForkHelper is an exception, those two don't have to match
 * @param matrix
 * @return
 */
bool Matrix::operator==(Matrix const &matrix) const {
    /* First check whether the dimension of the two matrices match
     * If the values are already different, there is no point in proceeding */
    if (dimension != matrix.getDimension()) {
        return false;
    }

    /* Check the values at all coordinates and only proceed if identical */
    for (unsigned short int row = 1; row <= dimension; ++row) {
        for (unsigned short int column = 1; column <= dimension; ++column) {
            auto values1 = (*this)[{row, column}].getPossibleValues();
            auto values2 = matrix[{row, column}].getPossibleValues();

            /* Again first vector size check */
            if (values1.size() != values2.size()) {
                return false;
            }

            /* If both the dimensions and the vector sizes of possible values are matching,
             * check each values one by one */
            for (unsigned short int i = 0; i < values1.size(); ++i) {
                if (values1[i] != values2[i]) {
                    return false;
                }
            }
        }
    }

    return true;
}

/**
 * Matrix nequality operator
 * Exactly the opposite of the equality operator
 * Only needed for testing purposes
 * @param matrix
 * @return
 */
bool Matrix::operator!=(Matrix const &matrix) const {
    return !((*this) == matrix);
}

/**
 * Matrix destructor
 * Deallocate ForkHelper object
 */
Matrix::~Matrix() {
    delete forkHelper;
}

/**
 * Get matrix dimension
 * Since it was saved in the constructor, there is no further calculation needed
 * @return
 */
unsigned short int Matrix::getDimension() const {
    return dimension;
}

/**
 * Matrix at operator
 * Returns a reference of the Field object on the coordinates passed as a parameter
 * @param coordinates
 * @return
 */
Field &Matrix::operator[](std::pair<unsigned short int, unsigned short int> const &coordinates) {
    return fields.at(coordinates);
}

/**
 * Matrix at const operator
 * Returns a const reference of the Field object on the coordinates passed as a parameter
 * @param coordinates
 * @return
 */
Field const &Matrix::operator[](std::pair<unsigned short int, unsigned short int> const &coordinates) const {
    return fields.at(coordinates);
}

/**
 * Tricky function executing the fork function of the ForkHelper object
 * On the current instance (*this) fixFirst() will be executed, and a Matrix with the matching removeFirst()
 * is returned
 * @return
 */
Matrix Matrix::forkFirstReturnSecond() {
    return forkHelper->fork();
}

/**
 * To trigger a ForkHelper check, it is possible to do so with a function of Matrix
 * Mainly for testing purposes
 * @param coordinates
 */
void Matrix::notifyChangeAt(std::pair<unsigned short int, unsigned short int> const &coordinates) {
    forkHelper->notify(coordinates);
}