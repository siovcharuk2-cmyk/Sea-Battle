#include <iostream>
#include "board.h"

void initBoard(char board[BOARD_SIZE][BOARD_SIZE])
{
	for (int i = 0; i < BOARD_SIZE; i++)
	{
		for (int j = 0; j < BOARD_SIZE; j++)
		{
			board[i][j] = EMPTY;
		}
	}
}

void printBoard(char pBoard[BOARD_SIZE][BOARD_SIZE], char cBoard[BOARD_SIZE][BOARD_SIZE])
{
	std::cout << "    ГРАВЕЦЬ              БОТ" << std::endl;
	std::cout << "  0 1 2 3 4 5 6 7 8 9    0 1 2 3 4 5 6 7 8 9" << std::endl;

	for (int i = 0; i < BOARD_SIZE; i++)
	{
		std::cout << i << " ";
		for (int j = 0; j < BOARD_SIZE; j++)
			std::cout << pBoard << " ";
		std::cout << "  " << i << " ";
		for (int j = 0; j < BOARD_SIZE; j++)
		{
			if (cBoard[i][j] == SHIP) std::cout << EMPTY << " ";
			else std::cout << cBoard[i][j] << " ";
		}
		std::cout << std::endl;
	}
}