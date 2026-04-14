#include <iostream>
#include <windows.h>
#include "board.h"
#include "logic.h"
#include "bot.h"

int main() {
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);
    setlocale(LC_ALL, ".UTF8");

    srand(time(NULL));

    char pBoard[BOARD_SIZE][BOARD_SIZE];
    char cBoard[BOARD_SIZE][BOARD_SIZE];
    
    initBoard(pBoard);
    initBoard(cBoard);

    Bot computerBrain = { SEARCH, 0, 0, 0 };

    std::cout << "=== МОРСЬКИЙ БІЙ ===\n\n";
    std::cout << "Виберіть спосіб розстановки кораблів:\n";
    std::cout << "1. Автоматично" << std::endl;
    std::cout << "2. Вручну" << std::endl;
    std::cout << "> ";
    
    short choice;
    std::cin >> choice;

    if (choice == 2)
    {
        for (int i = 0; i < TOTAL_SHIPS; i++) {
            int currentSize = SHIP_TYPES[i];
            bool placed = false;

            while (!placed)
            {
                printBoard(pBoard, cBoard);

                int x, y;
                bool hor;

                std::cout << "Розмір: " << currentSize << " (" << i + 1 << " з " << TOTAL_SHIPS << ")" << std::endl;
                std::cout << "Введіть координати (x y) та напрямок (1 - гориз, 0 - верт): ";

                std::cin >> x >> y >> hor;

                if (canPlaceShip(pBoard, x, y, currentSize, hor))
                {
                    for (int j = 0; j < currentSize; j++)
                    {
                        if (hor) pBoard[x][y + j] = SHIP;
                        else pBoard[x + j][y] = SHIP;
                    }
                    placed = true;
                }
                else
                {
                    std::cout << "Сюди не можна поставити!" << std::endl;
                    Sleep(2000);
                }
            }
        }
        std::cout << "\nВсі кораблі успішно розставлено!\n";
    }
    else
        placeShipsAuto(pBoard);

    placeShipsAuto(cBoard);

    bool playerTurn = true;

    while (true)
    {
        printBoard(pBoard, cBoard);

        if (playerTurn)
        {
            int x, y;

            std::cout << "\n--- ВАШ ХІД ---\n";
            std::cout << "Введіть координати для пострілу (x y): ";
            std::cin >> x >> y;
            system("cls");

            if (!canShoot(cBoard, x, y))
            {
                std::cout << "Сюди не можна стріляти! Спробуйте ще раз." << std::endl;
                Sleep(1000);
                continue;
            }

            if (processShot(cBoard, x, y))
            {
                std::cout << "Є ВЛУЧАННЯ! Ви стріляєте знову." << std::endl;
                if (checkWin(cBoard)) break;
                Sleep(1000);
            }
            else
            {
                std::cout << "Мимо!" << std::endl;
                playerTurn = false;
                Sleep(1000);
            }
        } 
        else
        {
            system("cls");
            std::cout << "\n--- ХІД КОМП'ЮТЕРА ---\n";

            bool botHit = true;
            while (botHit)
            {
                Sleep(1000);

                botHit = botAction(pBoard, computerBrain);
                printBoard(pBoard, cBoard);

                if (botHit)
                {
                    std::cout << "Бот влучив і стріляє знову!\n";
                    Sleep(2000);
                    system("cls");
                    if (checkWin(pBoard)) break;
                }
                else
                {
                    std::cout << "Бот промахнувся. Ваш хід!\n";
                    Sleep(2000);
                    system("cls");
                    playerTurn = true;
                }
            }
        }
    }

    printBoard(pBoard, cBoard);

    if (checkWin(cBoard))
    {
        std::cout << "\n==============================\n";
        std::cout << "   ВІТАЄМО! ВИ ПЕРЕМІГЛИ!   \n";
        std::cout << "==============================\n";
    }
    else
    {
        std::cout << "\n==============================\n";
        std::cout << "   БОТ ПЕРЕМІГ  \n";
        std::cout << "==============================\n";
    }
}