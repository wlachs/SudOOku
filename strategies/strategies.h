//
// Created by Borbély László on 2018. 09. 15..
//

#ifndef SUDOOKU_STRATEGIES_H
#define SUDOOKU_STRATEGIES_H


#include "solvingStrategy.h"

class RowStrategy : public SolvingStrategy {
private:
    bool simplifyRow(Matrix &, unsigned short int, unsigned short int) const;

    bool optimizeSingular(Matrix &, unsigned short int, unsigned short int) const;

    bool optimizeUnique(Matrix &, unsigned short int, unsigned short int) const;

    bool recursiveRemove(Matrix &, unsigned short int, unsigned short int,
                         unsigned short int, short int, unsigned short int) const;

    bool isUniqueInRow(Matrix const &, unsigned short int, unsigned short int, unsigned short int) const;
public:
    bool validate(Matrix const &) const override;

    bool simplify(Matrix &) const override;
};

class ColumnStrategy : public SolvingStrategy {
private:
    bool simplifyColumn(Matrix &, unsigned short int, unsigned short int) const;

    bool optimizeSingular(Matrix &, unsigned short int, unsigned short int) const;

    bool optimizeUnique(Matrix &, unsigned short int, unsigned short int) const;

    bool recursiveRemove(Matrix &, unsigned short int, unsigned short int,
                         unsigned short int, short int, unsigned short int) const;

    bool isUniqueInColumn(Matrix const &, unsigned short int, unsigned short int, unsigned short int) const;
public:
    bool validate(Matrix const &matrix) const override;

    bool simplify(Matrix &) const override;
};

class GroupStrategy : public SolvingStrategy {
private:
    std::vector<Matrix> separateToGroups(Matrix const &) const;

    bool singular(Matrix const &) const;

    std::vector<std::vector<std::pair<unsigned short int, unsigned short int>>>
    getGroupCoordinates(Matrix const &) const;

    bool simplifyGroup(Matrix &, std::vector<std::pair<unsigned short int, unsigned short int>> const &) const;

    bool removeFromGroup(Matrix &, std::vector<std::pair<unsigned short int, unsigned short int>> const &,
                         std::pair<unsigned short int, unsigned short int> const &, unsigned short int) const;

public:
    bool validate(Matrix const &matrix) const override;

    bool simplify(Matrix &) const override;
};


#endif //SUDOOKU_STRATEGIES_H
