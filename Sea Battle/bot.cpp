#include <random>
#include "bot.h"
#include "logic.h"

void botAction(char pBoard[BOARD_SIZE][BOARD_SIZE], Bot& bot) {
    int x, y;

    if (bot.state == SEARCH)
    {
        do
        {
            x = rand() % BOARD_SIZE;
            y = rand() % BOARD_SIZE;
        } while (pBoard[x][y] == HIT || pBoard[x][y] == MISS);

        if (pBoard[x][y] == SHIP)
        {
            pBoard[x][y] = HIT;

            if (isSunk(pBoard, x, y))
            {
                markAroundSunk(pBoard, x, y);
                bot.state = SEARCH;
            }
            else
            {
                bot.state = HUNT;
                bot.lastX = x;
                bot.lastY = y;
                bot.dir = 0;
            }
        }
        else
            pBoard[x][y] = MISS;
    }
    else if (bot.state == HUNT)
    {
        int dx[] = { -1, 1, 0, 0 };
        int dy[] = { 0, 0, -1, 1 };

        bool madeShot = false;
        while (!madeShot)
        {
            int targetX = bot.lastX + dx[bot.dir];
            int targetY = bot.lastY + dy[bot.dir];

            if (targetX >= 0 && targetX < BOARD_SIZE && targetY >= 0 && targetY < BOARD_SIZE &&
                pBoard[targetX][targetY] != HIT && pBoard[targetX][targetY] != MISS)
            {
                if (pBoard[targetX][targetY] == SHIP)
                {
                    pBoard[targetX][targetY] = HIT;
                    bot.lastX = targetX;
                    bot.lastY = targetY;

                    if (isSunk(pBoard, targetX, targetY))
                    {
                        bot.state = SEARCH;
                        markAroundSunk(pBoard, targetX, targetY);
                    }
                }
                else
                {
                    pBoard[targetX][targetY] = MISS;
                    bot.dir = (bot.dir + 1) % 4;
                }
                madeShot = true;
            }
            else
            {
                bot.dir = (bot.dir + 1) % 4;
                if (bot.dir == 0)
                {
                    bot.state = SEARCH;
                    botAction(pBoard, bot);
                    madeShot = true;
                }
            }
        }
    }
}