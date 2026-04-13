#pragma once

const int BOARD_SIZE = 10;

const int TOTAL_SHIPS = 10;
const int SHIP_TYPES[TOTAL_SHIPS] = { 4, 3, 3, 2, 2, 2, 1, 1, 1, 1 };

enum CellState { EMPTY = '~', SHIP = 'S', HIT = 'X', MISS = '*' };
enum BotState { SEARCH, HUNT };

struct Bot {
    BotState state;
    int lastX, lastY;
    int dir;
};