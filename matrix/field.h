//
// Created by Borbély László on 2018. 09. 15..
//

#ifndef SUDOOKU_FIELD_H
#define SUDOOKU_FIELD_H


#include <vector>
#include <iostream>

class Matrix;

class Field {
private:
    std::vector<unsigned short int> possibleValues = {};

public:
    Field() = default;

    Field(std::vector<unsigned short int> const &);

    Field(unsigned short int);

    Field(Field const &);

    Field &operator=(Field const &);

    void setPossibleValues(std::vector<unsigned short int> &);

    std::vector<unsigned short int> const &getPossibleValues() const;

    void fixValue();

    void fixValue(unsigned short int);

    void removeValue();

    void removeValue(unsigned short int);
};


#endif //SUDOOKU_FIELD_H
