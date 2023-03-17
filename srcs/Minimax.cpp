/*
** EPITECH PROJECT, 2023
** Gomoku [WSL : Ubuntu]
** File description:
** Minimax
*/

#include "Minimax.hpp"

Minimax::Minimax(Board board)
    :   _board(board)
{
}

Minimax::~Minimax()
{
}

Board Minimax::getBoard(void) const
{
    return this->_board;
}

std::clock_t Minimax::getTimer(void) const
{
    return this->_timer;
}

void Minimax::setBoard(Board board)
{
    this->_board = board;
}

void Minimax::setTimer(std::clock_t timer)
{
    this->_timer = timer;
}

void Minimax::printBoard(void)
{
    return this->getBoard().printMap();
}

BestScore_t Minimax::findBestScore(void)
{
    BestScore_t bestScore = {
        ._x = Positions_t::INVALID,
        ._y = Positions_t::INVALID,
    };
    std::int32_t maxScore = -1000;
    std::int32_t score = 0;
    std::vector<std::vector<std::int32_t>> map = this->getBoard().getMap();

    for (std::size_t i = 0; i < map.size(); i++) {
        for (std::size_t j = 0; j < map[i].size(); j++) {
            if (map[i][j] == Positions_t::INVALID) {
                map[i][j] = Positions_t::AI;
                score = this->minimaxAlgorithm(map, 0, false, -1000, 1000);
                map[i][j] = Positions_t::INVALID;
                if (score > maxScore) {
                    bestScore._x = i;
                    bestScore._y = j;
                    maxScore = score;
                }
                std::cout << bestScore._x << ";" << bestScore._y << std::endl;
            }
        }
    }
    return bestScore;
}

std::int32_t Minimax::minimaxAlgorithm(std::vector<std::vector<std::int32_t>> &map, std::uint32_t depth, bool isMaximizer, std::int32_t alpha, std::int32_t beta)
{
    std::int32_t maxScore = 0;
    std::int32_t evaluation = 0;

    evaluation = this->getBoard().isWinning(Positions_t::PLAYER);
    if (evaluation == 10)
        return evaluation;
    evaluation = this->getBoard().isWinning(Positions_t::AI);
    if (evaluation == -10)
        return evaluation;
    if (this->getBoard().isMovesInMap() == FAILURE)
        return 0;
    if (depth == 5 || this->stopTimer() > MAX_DELAY * CLOCKS_PER_SEC)
        return this->getBoard().evaluateScoreInMap();
    maxScore = isMaximizer == true ? -1000 : 1000;
    for (std::size_t i = 0; i < map.size(); i++) {
        for (std::size_t j = 0; j < map[i].size(); j++) {
            if (map[i][j] == Positions_t::INVALID) {
                map[i][j] = isMaximizer == true ? Positions_t::AI : Positions_t::PLAYER;
                maxScore = std::max(maxScore, this->minimaxAlgorithm(map, depth + 1, !isMaximizer, alpha, beta));
                map[i][j] = Positions_t::INVALID;
                if (isMaximizer == true) { alpha = std::max(alpha, maxScore); }
                else { beta = std::max(beta, maxScore); }
                if (beta <= alpha)
                    return maxScore;
            }
        }
    }
    return maxScore;
}

void Minimax::startTimer(void)
{
    this->_timer = clock();
}

std::clock_t Minimax::stopTimer(void)
{
    return clock() - this->_timer;
}

void Minimax::resetTimer(void)
{
    this->_timer = 0;
}

