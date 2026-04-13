#pragma once

const int BOARD_SIZE = 10;
enum CellState { EMPTY = '~', SHIP = 'S', HIT = 'X', MISS = '*' };
enum BotState { SEARCH, HUNT };

struct Bot {
    BotState state;
    int lastX, lastY;
    int dir;
};