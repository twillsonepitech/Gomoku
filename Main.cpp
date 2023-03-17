/**
 * @file Main.cpp
 * @author Thomas Willson (thomas.willson@epitech.eu)
 * @brief 
 * @version 0.1
 * @date 2023-03-15
 * 
 * @copyright Copyright (c) 2023
 * 
 */

#include <sstream>
#include "define.h"
#include "Minimax.hpp"

int main(__attribute__((unused)) int argc, __attribute__((unused)) char const *argv[])
{
    std::vector<std::vector<std::int32_t>> map(MAX_LINES, std::vector<std::int32_t>(MAX_COLS, Positions_t::INVALID));
    Board board(map);
    Minimax minimaxAlgo(board);
    std::string input;
    std::int32_t x, y;

    while (true) {
        minimaxAlgo.printBoard();
        std::cout << "Enter x and y positions (e.g. \"1 2\"):\n";
        std::getline(std::cin, input);
        std::istringstream iss(input);
        iss >> x >> y;
        minimaxAlgo.setBoard(minimaxAlgo.getBoard().changePositionsInMap({._x = x, ._y = y}, Positions_t::PLAYER));
        minimaxAlgo.startTimer();
        BestScore_t bestScore = minimaxAlgo.findBestScore();
        minimaxAlgo.resetTimer();
        minimaxAlgo.setBoard(minimaxAlgo.getBoard().changePositionsInMap(bestScore, Positions_t::AI));
    }
    return 0;
}
