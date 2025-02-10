# Snake Game

## Lab Group Name - Dynamic Programmers
Members :
- Shashank Rawat - 202401183(G3)
- Shreyav Kumar - 202401206(G3)
- Anshuman Bhagat - 202301170(G2)

## Description

This is a classic Snake Game implemented in C++. The game features a dynamically growing snake that consumes different types of fruits to earn points. Special fruits provide unique effects, such as increasing or decreasing the snake's length.

## Features

- **Classic Snake Gameplay**: Navigate the snake using `WASD` controls.
- **Special Fruits**:
  - Normal Fruit (`F`): +10 points
  - Special Fruit A (`S`): +30 points and reduces length by 1
  - Special Fruit B (`G`): +40 points and increases length by 2
- **Wall Collision Detection**: Hitting the wall ends the game.
- **Self-Collision Detection**: Running into the snake's own tail ends the game.
- **Interactiv**e Main Menu

## Installation

1. Clone this repository:
   ```sh
   git clone https://github.com/your-username/snake-game.git
   ```
2. Navigate to the project directory:
   ```sh
   cd snake-game
   ```
3. Compile the program:
   ```sh
   g++ -o snake SnakeGame.cpp -std=c++11
   ```
4. Run the game:
   ```sh
   ./snake
   ```
The pre-compiled executable file is uploaded in the release section 

## Controls

- `W` - Move Up
- `S` - Move Down
- `A` - Move Left
- `D` - Move Right
- `X` - Quit the Game

## How to Play

- Move the snake around the grid to eat fruits and gain points.
- Avoid hitting walls and your own tail.
- Special fruits offer additional bonuses and penalties.
- Press `X` anytime to exit the game.

## Technologies Used

- **C++** (Standard Library for I/O and Randomization)
- **ANSI Escape Codes** (For Console Graphics)
- **Multi-threading** (For Delays and Sleep Functions)
