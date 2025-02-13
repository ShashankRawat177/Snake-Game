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
    cout << "\033[32m _______  __    _  _______  ___   _  _______ \033[0m" << endl;
    cout << "\033[32m|       ||  |  | ||   _   ||   | | ||       |\033[0m" << endl;
    cout << "\033[32m|  _____||   |_| ||  |_|  ||   |_| ||    ___|\033[0m" << endl;
    cout << "\033[32m| |_____ |       ||       ||      _||   |___ \033[0m" << endl;
    cout << "\033[32m|_____  ||  _    ||       ||     |_ |    ___|\033[0m" << endl;
    cout << "\033[32m _____| || | |   ||   _   ||    _  ||   |___ \033[0m" << endl;
    cout << "\033[32m|_______||_|  |__||__| |__||___| |_||_______|\033[0m" << endl;

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
        cout << "Eat \033[33m'F'\033[0m (Normal Fruit) for +10 points.\n";
        cout << "Eat \033[34m'S'\033[0m (Special Fruit A) for +40 points & -1 length (10% chance).\n";
        cout << "Eat \033[31m'G'\033[0m (Special Fruit B) for +60 points & +2 length (3% chance).\n";
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
            else if (j == x && i == y) cout << "\033[32mO\033[0m"; //Head
            else if (j == fruitx && i == fruity) cout << "\033[33mF\033[0m"; //Fruit
            else if (hasSpecialA && j == specialAx && i == specialAy) cout << "\033[34mS\033[0m";
            else if (hasSpecialB && j == specialBx && i == specialBy) cout << "\033[31mG\033[0m";
            else {
                bool printTail = false;
                for (int k = 0; k < nTail; k++) {
                    if (TailX[k] == j && TailY[k] == i) {
                        cout << "\033[32mo\033[0m";
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

void SnakeGame::Restart(){

    cout << "\033[31m"; // Set text color to red
    cout << " _______  _______  __   __  _______    _______  __   __  _______  ______      __ \n";
    cout << "|       ||   _   ||  |_|  ||       |  |       ||  | |  ||       ||    _ |    |  |\n";
    cout << "|    ___||  |_|  ||       ||    ___|  |   _   ||  |_|  ||    ___||   | ||    |  |\n";
    cout << "|   | __ |       ||       ||   |___   |  | |  ||       ||   |___ |   |_||_   |  |\n";
    cout << "|   ||  ||       ||       ||    ___|  |  |_|  ||       ||    ___||    __  |  |__|\n";
    cout << "|   |_| ||   _   || ||_|| ||   |___   |       | |     | |   |___ |   |  | |   __ \n";
    cout << "|_______||__| |__||_|   |_||_______|  |_______|  |___|  |_______||___|  |_|  |__|\n";
    
    cout << "\033[0m"; // Reset text color

    cout << "Final Score : " << Score << endl;

    cout << "Press 1 to restart.\n"
            "Press 2 to exit.\n"
            "Enter your choice : ";

    int input;
    cin >> input;
    if(input == 1){
        restart = true;
    }else if(input == 2){
        restart = false;
    }else{
        cout << "\033[2J\033[H";
        cout << "Invalid choice..... Please enter again\n";
        Restart();
    }
}

void SnakeGame::run() {
    hideCursor();
    MainMenu();
    restart = true;
    while(restart){
        
        
        startup();
        while (!isGameOver) {
            draw();
            input();
            logic();
            if (isGameOver) break;
            this_thread::sleep_for(chrono::milliseconds(100));
        }
        
        cout << "\033[2J\033[H";    
        Restart();
    }
    showCursor();
    exit(0);  
}
