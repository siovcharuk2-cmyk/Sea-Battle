#pragma once
#include "common.h"

bool canPlaceShip(char board[BOARD_SIZE][BOARD_SIZE], int x, int y, int size, bool horizontal);

void placeShipsAuto(char board[BOARD_SIZE][BOARD_SIZE]);

bool canShoot(char board[BOARD_SIZE][BOARD_SIZE], int x, int y);

bool processShot(char board[BOARD_SIZE][BOARD_SIZE], int x, int y);

bool checkWin(char board[BOARD_SIZE][BOARD_SIZE]);