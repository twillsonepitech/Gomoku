/*
** EPITECH PROJECT, 2023
** Gomoku [WSL : Ubuntu]
** File description:
** define
*/

#ifndef DEFINE_H_
#define DEFINE_H_

#include <iostream>

#define MAX_LINES       (15)
#define MAX_COLS        (15)
#define SUCCESS         (0)
#define FAILURE         (1)
#define MAX_DEPTH       (5)
#define MAX_DELAY       (4.5)

typedef enum Positions_e {
    INVALID = -1,
    PLAYER  = 1,
    AI      = 2
} Positions_t;

typedef struct BestScore_s {
    std::int32_t _x;
    std::int32_t _y;
} BestScore_t;

#endif /* !DEFINE_H_ */
