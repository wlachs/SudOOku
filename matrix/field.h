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
    Matrix *matrix = nullptr;
    std::vector<unsigned short int> possibleValues = {};
    std::pair<unsigned short int, unsigned short int> coordinates;

public:
    Field(Matrix &, unsigned short int, std::pair<unsigned short int, unsigned short int>);

    Field(unsigned short int);

    Field() = default;

    Field(Field const &);

    Field &operator=(Field const &);

    std::vector<unsigned short int> &getPossibleValues();

    std::vector<unsigned short int> const &getPossibleValues() const;

    void fixValue();

    void fixValue(unsigned short int);

    void removeValue();

    void removeValue(unsigned short int);

    bool isFixed() const;

    void setMatrix(Matrix &);

    void setCoordinates(std::pair<unsigned short int, unsigned short int>);
};


#endif //SUDOOKU_FIELD_H
