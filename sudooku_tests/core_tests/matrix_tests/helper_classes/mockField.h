//
// Created by Borbély László on 2018. 10. 21..
//

#ifndef SUDOOKU_MOCKFIELD_H
#define SUDOOKU_MOCKFIELD_H

#include <sudooku_core/matrix/field.h>
#include "gmock/gmock.h"

class MockField : public Field {
public:
    MOCK_CONST_METHOD0(getPossibleValues, std::vector<unsigned short int> const &());

    MOCK_METHOD0(fixValue, void());

    MOCK_METHOD1(fixValue, void(unsigned short int));

    MOCK_METHOD0(removeValue, void());

    MOCK_METHOD1(removeValue, bool(unsigned short int));

    MOCK_CONST_METHOD1(contains, bool(unsigned short int));
};

#endif //SUDOOKU_MOCKFIELD_H
