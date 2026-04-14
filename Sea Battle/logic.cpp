#include <iostream>
#include "logic.h"

bool canPlaceShip(char board[BOARD_SIZE][BOARD_SIZE], int x, int y, int size, bool horizontal)
{
	if (horizontal)
	{
		if (y + size > BOARD_SIZE)
			return false;
	}
	else
	{
		if (x + size > BOARD_SIZE)
			return false;
	}

    int startX = (x > 0) ? x - 1 : 0;
    int startY = (y > 0) ? y - 1 : 0;
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
                    if (randHoriz)
                        board[randX][randY + j] = SHIP;
                    else
                        board[randX + j][randY] = SHIP;
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
        if (isSunk(board, x, y))
            markAroundSunk(board, x, y);
        return true;
    }
    else if (board[x][y] == EMPTY)
        board[x][y] = MISS;

    return false;
}

bool isSunk(char board[BOARD_SIZE][BOARD_SIZE], int x, int y)
{
    for (int i = x; i >= 0 && board[i][y] == HIT; i--) {
        if (i > 0 && board[i - 1][y] == SHIP) return false;
    }
    for (int i = x; i < BOARD_SIZE && board[i][y] == HIT; i++) {
        if (i < BOARD_SIZE - 1 && board[i + 1][y] == SHIP) return false;
    }

    for (int j = y; j >= 0 && board[x][j] == HIT; j--) {
        if (j > 0 && board[x][j - 1] == SHIP) return false;
    }
    for (int j = y; j < BOARD_SIZE && board[x][j] == HIT; j++) {
        if (j < BOARD_SIZE - 1 && board[x][j + 1] == SHIP) return false;
    }

    return true;
}

void markAroundSunk(char board[BOARD_SIZE][BOARD_SIZE], int x, int y)
{
    int minX = x, maxX = x, minY = y, maxY = y;

    while (minX > 0 && board[minX - 1][y] == HIT) minX--;
    while (maxX < BOARD_SIZE - 1 && board[maxX + 1][y] == HIT) maxX++;

    while (minY > 0 && board[x][minY - 1] == HIT) minY--;
    while (maxY < BOARD_SIZE - 1 && board[x][maxY + 1] == HIT) maxY++;

    for (int i = minX - 1; i <= maxX + 1; i++)
    {
        for (int j = minY - 1; j <= maxY + 1; j++)
        {
            if (i >= 0 && i < BOARD_SIZE && j >= 0 && j < BOARD_SIZE)
            {
                if (board[i][j] == EMPTY)
                    board[i][j] = MISS;
            }
        }
    }
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