#ifndef SNAKEGAME_H
#define SNAKEGAME_H

#include <iostream>
#include <random>
#include <thread>
#include <conio.h>
#include <cstdlib>
#include <ctime>
#include <string>

class SnakeGame {
private:
    bool isGameOver;
    bool restart;
    int x, y, fruitx, fruity, specialAx, specialAy, specialBx, specialBy, Score;
    bool hasSpecialA, hasSpecialB;
    const int GridLength = 20;
    const int GridWidth = 20;
    int TailX[400], TailY[400];
    int nTail;
    enum Direction{STOP = 0, UP, DOWN, LEFT, RIGHT};
    Direction dir;
    std::mt19937 rng;  // Mersenne Twister RNG
    std::uniform_int_distribution<int> distX, distY, distChance;  // Distributions

public:
    SnakeGame();
    void gotoxy(int x, int y);
    void hideCursor();
    void showCursor();
    void spawnFruit();
    void startup();
    void MainMenu();
    void draw();
    void input();
    void logic();
    void run();
    void Restart();
    void displayScore();
};

#endif // SNAKEGAME_H
