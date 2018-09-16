//
// Created by Borbély László on 2018. 09. 15..
//

#include <iostream>
#include "matrix/field.h"
#include "matrix/matrix.h"

int main() {
    std::cout << "init" << std::endl;

    std::map<std::pair<unsigned short int, unsigned short int>, Field> input = {
            {{1, 1}, 1},
            {{1, 2}, 2},
            {{1, 4}, 4},
            {{3, 1}, 2},
            {{3, 4}, 1},
            {{4, 2}, 1},
            {{4, 4}, 3}
    };

    Matrix matrix1{4, input};
    Matrix matrix2{matrix1};

    return 0;
}