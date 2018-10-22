//
// Created by Borbély László on 2018. 10. 21..
//

#ifndef SUDOOKU_GROUPSTRATEGY_H
#define SUDOOKU_GROUPSTRATEGY_H

#include "solvingStrategy.h"

class GroupStrategy : public SolvingStrategy {
private:
    const Matrix *constMatrix;
    Matrix *matrix;
    unsigned short int dimension;

    std::vector<Matrix> separateToGroups();

    bool singular(Matrix const &) const;

    std::vector<std::vector<std::pair<unsigned short int, unsigned short int>>> getGroupCoordinates() const;

    bool simplifyGroup(std::vector<std::pair<unsigned short int, unsigned short int>> const &);

    bool optimizeUnique(std::vector<std::pair<unsigned short int, unsigned short int>> const &,
                        std::pair<unsigned short int, unsigned short int> const &,
                        std::vector<unsigned short int> const &) const;

    bool removeFromGroup(std::vector<std::pair<unsigned short int, unsigned short int>> const &,
                         std::pair<unsigned short int, unsigned short int> const &, unsigned short int) const;

    bool isUniqueInGroup(std::vector<std::pair<unsigned short int, unsigned short int>> const &,
                         unsigned short int) const;

public:
    bool validate(Matrix const &matrix) override;

    bool simplify(Matrix &) override;
};

#endif //SUDOOKU_GROUPSTRATEGY_H
