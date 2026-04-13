#include <iostream>
#include "logic.h"

bool canPlaceShip(char board[BOARD_SIZE][BOARD_SIZE], int x, int y, int size, bool horizontal)
{
	if (horizontal)
	{
		if (x + size > BOARD_SIZE)
			return false;
	}
	else
	{
		if (y + size > BOARD_SIZE)
			return false;
	}

    int startX = (x - 1 > 0) ? x - 1 : 0;
    int startY = (y - 1 > 0) ? y - 1 : 0;

    int endX = horizontal ? x + 1 : x + size;
    int endY = horizontal ? y + size : y + 1;

    if (endX >= BOARD_SIZE) endX = BOARD_SIZE - 1;
    if (endY >= BOARD_SIZE) endY = BOARD_SIZE - 1;

    for (int i = startX; i <= endX; i++)
    {
        for (int j = startY; j <= endY; j++)
        {
            if (board[i][j] == SHIP)
                return false;
        }
    }

    return true;
}

void placeShipsAuto(char board[BOARD_SIZE][BOARD_SIZE])
{
    std::srand(time(NULL));

    for (int i = 0; i < TOTAL_SHIPS; i++)
    {
        int currentSize = SHIP_TYPES[i];
        bool placed = false;

        while (!placed)
        {
            int randX = rand() % BOARD_SIZE;
            int randY = rand() % BOARD_SIZE;
            bool randHoriz = (rand() % 2 == 1);

            if (canPlaceShip(board, randX, randY, currentSize, randHoriz))
            {
                for (int j = 0; j < currentSize; j++)
                {
                    if (randHoriz) board[randX][randY + j] = SHIP;
                    else board[randX + j][randY] = SHIP;
                }
                placed = true;
            }
        }
    }
}

bool canShoot(char board[BOARD_SIZE][BOARD_SIZE], int x, int y)
{
    if (x >= 0 && x < BOARD_SIZE && y >= 0 && y < BOARD_SIZE)
    {
        if (board[x][y] != HIT && board[x][y] != MISS)
            return true;
    }
    return false;
}

bool processShot(char board[BOARD_SIZE][BOARD_SIZE], int x, int y)
{
    if (board[x][y] == SHIP)
    {
        board[x][y] = HIT;
        return true;
    }

    if (board[x][y] == EMPTY)
    {
        board[x][y] = MISS;
        return true;
    }

    return false;
}

bool checkWin(char board[BOARD_SIZE][BOARD_SIZE])
{
    for (int i = 0; i < BOARD_SIZE; i++)
    {
        for (int j = 0; j < BOARD_SIZE; j++)
        {
            if (board[i][j] == SHIP) return false;
        }
    }

    return true;
}