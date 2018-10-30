//
// Created by Borbély László on 2018. 10. 21..
//

#ifndef SUDOOKU_MOCKMATRIX_H
#define SUDOOKU_MOCKMATRIX_H

#include <sudooku_core/matrix/matrix.h>
#include "gmock/gmock.h"
#include "mockField.h"

class MockMatrix : public Matrix {
private:
    MockField mockField;
public:
    MOCK_CONST_METHOD0(getDimension, unsigned short int());

    MOCK_METHOD0(forkFirstReturnSecond, Matrix());

    MOCK_METHOD1(notifyChangeAt, void(std::pair<unsigned short int, unsigned short int> const &));

    MOCK_METHOD1(at, Field &(std::pair<unsigned short int, unsigned short int> const &));

    MOCK_CONST_METHOD1(at_const, Field const &(std::pair<unsigned short int, unsigned short int> const &));

    virtual Field &operator[](std::pair<unsigned short int, unsigned short int> const &);

    virtual Field const &operator[](std::pair<unsigned short int, unsigned short int> const &) const;
};

#endif //SUDOOKU_MOCKMATRIX_H