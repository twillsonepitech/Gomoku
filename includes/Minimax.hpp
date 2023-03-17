/*
** EPITECH PROJECT, 2023
** Gomoku [WSL : Ubuntu]
** File description:
** Minimax
*/

#ifndef MINIMAX_HPP_
#define MINIMAX_HPP_

#include <ctime>
#include "Board.hpp"

class Minimax {
    public:
        Minimax(Board board);
        ~Minimax();
        Board getBoard(void) const;
        std::clock_t getTimer(void) const;
        void setBoard(Board board);
        void setTimer(std::clock_t timer);
        void printBoard(void);
        BestScore_t findBestScore(void);
        std::int32_t minimaxAlgorithm(std::vector<std::vector<std::int32_t>> &map, std::uint32_t depth, bool isMaximizer, std::int32_t alpha, std::int32_t beta);
        void startTimer(void);
        std::clock_t stopTimer(void);
        void resetTimer(void);

    protected:
    private:
        Board _board;
        std::clock_t _timer;
};

#endif /* !MINIMAX_HPP_ */
