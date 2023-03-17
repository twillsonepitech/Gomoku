/*
** EPITECH PROJECT, 2023
** Gomoku [WSL : Ubuntu]
** File description:
** Board
*/

#ifndef BOARD_HPP_
#define BOARD_HPP_

#include <vector>
#include "define.h"

class Board {
    public:
        Board(std::vector<std::vector<std::int32_t>> map);
        ~Board();
        std::vector<std::vector<std::int32_t>> getMap(void) const;
        void setMap(std::vector<std::vector<std::int32_t>> map);
        void printMap(void);
        std::uint8_t isMovesInMap(void);
        std::int32_t isWinning(const Positions_t player);
        std::vector<std::vector<std::int32_t>> changePositionsInMap(const BestScore_t bestScore, const Positions_t player);
        std::int32_t evaluateScoreInMap(void);

    protected:
    private:
        std::vector<std::vector<std::int32_t>> _map;
};

#endif /* !BOARD_HPP_ */
