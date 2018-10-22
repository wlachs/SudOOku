//
// Created by Borbély László on 2018. 09. 15..
//

#ifndef SUDOOKU_FIELD_H
#define SUDOOKU_FIELD_H


#include <vector>

class Matrix;

class Field {
private:
    std::vector<unsigned short int> possibleValues = {};

public:
    Field() = default;

    explicit Field(std::vector<unsigned short int> const &);

    explicit Field(unsigned short int);

    Field &operator=(Field const &) = default;

    virtual ~Field() = default;

    virtual std::vector<unsigned short int> const &getPossibleValues() const;

    virtual void fixValue();

    virtual void fixValue(unsigned short int);

    virtual void removeValue();

    virtual bool removeValue(unsigned short int);

    virtual bool contains(unsigned short int) const;
};


#endif //SUDOOKU_FIELD_H
