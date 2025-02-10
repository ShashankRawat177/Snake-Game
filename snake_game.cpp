#include "SnakeGame.h"

using namespace std;

SnakeGame::SnakeGame() : rng(random_device{}()), distX(1, GridWidth - 2), distY(1, GridLength - 2), distChance(1, 100) {}

void SnakeGame::gotoxy(int x, int y) {
    // ANSI escape codes use 1-indexed coordinates.
    cout << "\033[" << y+1 << ";" << x+1 << "H";
}

void SnakeGame::hideCursor() {
    cout << "\033[?25l";
    cout.flush();
}

void SnakeGame::showCursor() {
    cout << "\033[?25h";
    cout.flush();
}

void SnakeGame::spawnFruit() {
    fruitx = distX(rng);
    fruity = distY(rng);

    hasSpecialA = (distChance(rng) <= 30);  // 30% chance for Special A
    hasSpecialB = (distChance(rng) <= 20);   // 20% chance for Special B

    if (hasSpecialA) {
        do {
            specialAx = distX(rng);
            specialAy = distY(rng);
        } while ((specialAx == fruitx && specialAy == fruity));
    }

    if (hasSpecialB) {
        do {
            specialBx = distX(rng);
            specialBy = distY(rng);
        } while ((specialBx == fruitx && specialBy == fruity) || 
                 (hasSpecialA && specialBx == specialAx && specialBy == specialAy));
    }
}

void SnakeGame::startup() {
    cout << "\033[2J\033[H";
    isGameOver = false;
    x = GridWidth / 2;
    y = GridLength / 2;
    dir = RIGHT;  // Ensure the snake starts moving

    nTail = 3;  // Set initial tail length

    // Initialize the tail right behind the head
    for (int i = 0; i < nTail; i++) {
        TailX[i] = x - (i + 1);  // Position tail to the left of the head
        TailY[i] = y;
    }

    do {
        fruitx = distX(rng);
        fruity = distY(rng);
    } while (fruitx == x && fruity == y);
    Score = 0;
}

void SnakeGame::MainMenu() {
    cout << "\033[2J\033[H"; // Clears screen
    cout << " _______  __    _  _______  ___   _  _______ " << endl;
    cout << "|       ||  |  | ||   _   ||   | | ||       |" << endl;
    cout << "|  _____||   |_| ||  |_|  ||   |_| ||    ___|" << endl;
    cout << "| |_____ |       ||       ||      _||   |___ " << endl;
    cout << "|_____  ||  _    ||       ||     |_ |    ___|" << endl;
    cout << " _____| || | |   ||   _   ||    _  ||   |___ " << endl;
    cout << "|_______||_|  |__||__| |__||___| |_||_______|" << endl;

    cout << "\n=========== SNAKE GAME ===========\n";
    cout << "1. Start Game\n";
    cout << "2. Instructions\n";
    cout << "3. Exit\n";
    cout << "===================================\n";
    cout << "Enter your choice: ";
    
    char choice;
    cin >> choice;
    
    if (choice == '1') {
        cout << "\033[2J\033[H";
        return;
    }
    else if (choice == '2') {
        cout << "\033[2J\033[H";
        cout << "========== HOW TO PLAY ==========\n";
        cout << "Use 'W' 'A' 'S' 'D' to move the snake.\n";
        cout << "Eat 'F' (Normal Fruit) for +10 points.\n";
        cout << "Eat 'S' (Special Fruit A) for +40 points & -1 length (10% chance).\n";
        cout << "Eat 'G' (Special Fruit B) for +60 points & +2 length (3% chance).\n";
        cout << "Avoid hitting walls and yourself!\n";
        cout << "Press 'X' anytime to quit.\n";
        cout << "==================================\n";
        cout << "Press any key to return to the menu...";
        _getch();
        MainMenu();
    }
    else if (choice == '3') {
        cout << "\033[2J\033[H";  
        cout << "Thanks for playing! Goodbye.\n";
        exit(0);
    }
    else {
        cout << "Invalid choice! Try again.\n";
        this_thread::sleep_for(chrono::seconds(1));  
        MainMenu();
    }
}

void SnakeGame::draw() {
    gotoxy(0, 0);
    for (int j = 0; j < GridWidth; j++) cout << "_";     //First Line of Grid
    cout << endl;
    for (int i = 1; i < GridLength-1; i++) {
        for (int j = 0; j < GridWidth; j++) {
            if (j == 0 || j == GridWidth-1) cout << "|";
            else if (j == x && i == y) cout << "O"; //Head
            else if (j == fruitx && i == fruity) cout << "F"; //Fruit
            else if (hasSpecialA && j == specialAx && i == specialAy) cout << "S";
            else if (hasSpecialB && j == specialBx && i == specialBy) cout << "G";
            else {
                bool printTail = false;
                for (int k = 0; k < nTail; k++) {
                    if (TailX[k] == j && TailY[k] == i) {
                        cout << "o";
                        printTail = true;
                        break;
                    }
                }
                if (!printTail) cout << " ";
            }
        }
        cout << endl;
    }
    for (int j = 0; j < GridWidth; j++) {    //Last Line of Grid
        if (j == 0 || j == GridWidth-1) cout << "|";
        else cout << "_";
    }
    cout << endl;
    cout << "Current Score: " << Score;
    cout << endl;
}

void SnakeGame::input() {
    if (_kbhit()) {
        switch (_getch()) {
            case 'w':
                dir = UP;
                break;
            case 's':
                dir = DOWN;
                break;
            case 'a':
                dir = LEFT;
                break;
            case 'd':
                dir = RIGHT;
                break;
            case 'x':
                isGameOver = true;
                break;
        }
    }
}

void SnakeGame::logic() {
    int prevX = TailX[0];
    int prevY = TailY[0];
    int prev2X, prev2Y;
    TailX[0] = x;
    TailY[0] = y;
    for (int i = 1; i < nTail; i++) {
        prev2X = TailX[i];
        prev2Y = TailY[i];
        TailX[i] = prevX;
        TailY[i] = prevY;
        prevX = prev2X;
        prevY = prev2Y;
    }

    // Updating the location once a direction key is pressed
    switch (dir) {
        case UP:
            y--;
            break;
        case DOWN:
            y++;
            break;
        case LEFT:
            x--;
            break;
        case RIGHT:
            x++;
            break;
        default:
            break;
    }

    // Collision detection
    for (int i = 0; i < nTail; i++) {
        if (TailX[i] == x && TailY[i] == y) {
            isGameOver = true;
        }
    }

    // Wall collision
    if (x == 0 || x == GridWidth - 1 || y == 0 || y == GridLength - 1) {
        isGameOver = true;
    }

    // Check if the snake eats any fruit
    if (x == fruitx && y == fruity) {
        Score += 10;
        nTail++;
        spawnFruit();
    } else if (hasSpecialA && x == specialAx && y == specialAy) {
        Score += 30;
        if (nTail > 1) nTail--;  // Ensure snake doesn't disappear
        spawnFruit();
    } else if (hasSpecialB && x == specialBx && y == specialBy) {
        Score += 40;
        nTail += 2;
        spawnFruit();
    }
}

void SnakeGame::run() {
    hideCursor();
    MainMenu();
    startup();
    while (!isGameOver) {
        draw();
        input();
        logic();
        if (isGameOver) break;
        this_thread::sleep_for(chrono::milliseconds(100));
    }
    showCursor();
    cout << "\033[2J\033[H";
    cout << endl << "Game Over! Press any key to exit..." << endl;
    _getch(); 
    exit(0);  
}
