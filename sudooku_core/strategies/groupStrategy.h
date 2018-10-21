//
// Created by Borbély László on 2018. 10. 21..
//

#ifndef SUDOOKU_GROUPSTRATEGY_H
#define SUDOOKU_GROUPSTRATEGY_H

#include "solvingStrategy.h"

class GroupStrategy : public SolvingStrategy {
private:
    std::vector<Matrix> separateToGroups(Matrix const &) const;

    bool singular(Matrix const &) const;

    std::vector<std::vector<std::pair<unsigned short int, unsigned short int>>>
    getGroupCoordinates(Matrix const &) const;

    bool simplifyGroup(Matrix &, std::vector<std::pair<unsigned short int, unsigned short int>> const &) const;

    bool optimizeUnique(Matrix &,
                        std::vector<std::pair<unsigned short int, unsigned short int>> const &,
                        std::pair<unsigned short int, unsigned short int> const &,
                        std::vector<unsigned short int> const &) const;

    bool removeFromGroup(Matrix &, std::vector<std::pair<unsigned short int, unsigned short int>> const &,
                         std::pair<unsigned short int, unsigned short int> const &, unsigned short int) const;

    bool isUniqueInGroup(Matrix const &, std::vector<std::pair<unsigned short int, unsigned short int>> const &,
                         unsigned short int) const;

public:
    bool validate(Matrix const &matrix) const override;

    bool simplify(Matrix &) const override;
};

#endif //SUDOOKU_GROUPSTRATEGY_H
