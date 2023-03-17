/*
** EPITECH PROJECT, 2023
** Gomoku [WSL : Ubuntu]
** File description:
** Board
*/

#include <map>
#include "Board.hpp"

Board::Board(std::vector<std::vector<std::int32_t>> map)
    :   _map(map)
{
}

Board::~Board()
{
}

std::vector<std::vector<std::int32_t>> Board::getMap(void)
const {
    return this->_map;
}

void Board::setMap(std::vector<std::vector<std::int32_t>> map)
{
    this->_map = map;
}

void Board::printMap(void)
{
    const std::map<const std::int32_t, const uint8_t> convert = {
        {Positions_t::INVALID,  '.'},
        {Positions_t::PLAYER,   'x'},
        {Positions_t::AI,       'o'},
    };
    const std::vector<std::vector<std::int32_t>> map = this->getMap();

    for (std::size_t i = 0; i < map.size(); i++) {
        for (std::size_t j = 0; j < map[i].size(); j++)
            std::cout << "[" << static_cast<char>(convert.at(map[i][j])) << "]";
        std::cout << std::endl;
    }
}

std::uint8_t Board::isMovesInMap(void)
{
    const std::vector<std::vector<std::int32_t>> map = this->getMap();

    for (std::size_t i = 0; i < map.size(); i++) {
        for (std::size_t j = 0; j < map[i].size(); j++) {
            if (map[i][j] == INVALID)
                return SUCCESS;
        }
    }
    return FAILURE;
}

std::int32_t Board::isWinning(const Positions_t player)
{
    const std::vector<std::vector<std::int32_t>> map = this->getMap();

    for (std::size_t i = 0; i < map.size(); i++) {
        for (std::size_t j = 5 - 1; j < map[i].size(); j++) {
            if (map[i][j - 4] == player && map[i][j - 3] == player && map[i][j - 2] == player
                && map[i][j - 1] == player && map[i][j] == player)
                return player == Positions_t::PLAYER ? 10 : -10;
        }
    }
    for (std::size_t i = 5 - 1; i < map.size(); i++) {
        for (std::size_t j = 0; j < map[i].size(); j++) {
            if (map[i - 4][j] == player && map[i - 3][j] == player && map[i - 2][j] == player
                && map[i - 1][j] == player && map[i][j] == player)
                return player == Positions_t::PLAYER ? 10 : -10;
        }
    }
    for (std::size_t i = 0; i < map.size() - 5 + 1; i++) {
        for (std::size_t j = 0; j < map.size() - 5 + 1; j++) {
            if (map[i][j] == player && map[i + 1][j + 1] == player && map[i + 2][j + 2] == player
                && map[i + 3][j + 3] == player && map[i + 4][j + 4] == player)
                return player == Positions_t::PLAYER ? 10 : -10;
        }
    }
    for (std::size_t i = 0; i < map.size() - 5 + 1; i++) {
        for (std::size_t j = 5 - 1; j < map.size(); j++) {
            if (map[i][j] == player && map[i + 1][j - 1] == player && map[i + 2][j - 2] == player
                && map[i + 3][j - 3] == player && map[i + 4][j - 4] == player)
                return player == Positions_t::PLAYER ? 10 : -10;
        }
    }
    return 0;
}

std::vector<std::vector<std::int32_t>> Board::changePositionsInMap(const BestScore_t bestScore, const Positions_t player)
{
    std::vector<std::vector<std::int32_t>> map = this->getMap();

    map[bestScore._x][bestScore._y] = player;
    return map;
}

std::int32_t evaluateLine(const std::vector<std::int32_t>& line)
{
    std::int32_t score = 0;
    std::size_t numPlayer = 0;
    std::size_t numAI = 0;
    std::size_t numEmpty = 0;

    for (const auto& pos : line) {
        if (pos == Positions_t::PLAYER) {
            numPlayer++;
        } else if (pos == Positions_t::AI) {
            numAI++;
        } else if (pos == Positions_t::INVALID) {
            numEmpty++;
        }
    }

    // Evaluate based on number of pieces in the line
    if (numPlayer == 5) {
        score = 1000000;
    } else if (numPlayer == 4 && numEmpty == 1) {
        score = 10000;
    } else if (numPlayer == 3 && numEmpty == 2) {
        score = 1000;
    } else if (numPlayer == 2 && numEmpty == 3) {
        score = 100;
    } else if (numPlayer == 1 && numEmpty == 4) {
        score = 10;
    }

    if (numAI == 5) {
        score = -1000000;
    } else if (numAI == 4 && numEmpty == 1) {
        score = -10000;
    } else if (numAI == 3 && numEmpty == 2) {
        score = -1000;
    } else if (numAI == 2 && numEmpty == 3) {
        score = -100;
    } else if (numAI == 1 && numEmpty == 4) {
        score = -10;
    }

    return score;
}

std::int32_t evaluateScoreInLines(const std::vector<std::vector<std::int32_t>>& map, const std::int32_t dx, const std::int32_t dy, const std::int32_t offset)
{
    std::int32_t evaluation = 0;
    const std::size_t size = map.size();

    for (std::size_t i = 0; i < size; i++) {
        for (std::size_t j = 0; j < size; j++) {
            const std::size_t x = i + offset * dx;
            const std::size_t y = j + offset * dy;

            if (x >= size || y >= size) {
                continue;
            }

            std::vector<std::int32_t> line;
            for (std::size_t k = 0; k < 5 && x + k * dx < size && y + k * dy < size; k++) {
                line.push_back(map[x + k * dx][y + k * dy]);
            }

            evaluation += evaluateLine(line);
        }
    }

    return evaluation;
}

std::int32_t Board::evaluateScoreInMap(void)
{
    const std::vector<std::vector<std::int32_t>> map = this->getMap();
    std::int32_t evaluation = 0;

    evaluation += evaluateScoreInLines(map, 1, 0, 0); // Rows
    evaluation += evaluateScoreInLines(map, 0, 1, 0); // Columns
    evaluation += evaluateScoreInLines(map, 1, 1, 0); // Diagonals
    evaluation += evaluateScoreInLines(map, 1, -1, 0); // Anti-diagonals

    return evaluation;
}
