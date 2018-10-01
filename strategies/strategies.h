//
// Created by Borbély László on 2018. 09. 15..
//

#ifndef SUDOOKU_STRATEGIES_H
#define SUDOOKU_STRATEGIES_H


#include "solvingStrategy.h"

class RowStrategy : public SolvingStrategy {
public:
    virtual bool validate(Matrix const &matrix) const;
};

class ColumnStrategy : public SolvingStrategy {
public:
    virtual bool validate(Matrix const &matrix) const;
};

class GroupStrategy : public SolvingStrategy {
private:
    std::vector<Matrix> separateToGroups(Matrix const &) const;

    bool singular(Matrix const &) const;

public:
    virtual bool validate(Matrix const &matrix) const;
};


#endif //SUDOOKU_STRATEGIES_H
