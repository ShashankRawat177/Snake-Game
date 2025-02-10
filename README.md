# Snake Game

## Lab Group Name - Dynamic Programmers
Members :
- Shashank Rawat - 202401183(G3)
- Shreyav Kumar - 202401206(G3)
- Anshuman Bhagat - 202301170(G2)

## Description
Implementation of the Snake Game in the C++ programming language. The game contains a snake of dynamically increasing length, which eats different types of fruits to score points. Special fruits bring unique effects, such as increasing or reducing snake length.

## Features

- **Classic Snake Gameplay**: Control snake using `WASD` controls
- **Special Fruits**
- Regular Fruit (`F`): +10 points
- Special Fruit A (`S`): +30 points and shortens length by 1
- Special Fruit B (`G`): +40 points and lengthens by 2
- **Wall Collision Detection**: Bouncing into the wall loses.
- **Self-Collision Detection**: Into the snake's own tail and it's game over.
- **Interactiv**e Main Menu

## Installation

1. Clone this repository:
```sh
git clone https://github.com/your-username/snake-game.git
2. Move into the project directory:
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

## Controls

- `W` - Move Up
- `S` - Move Down
- `A` - Move Left
- `D` - Move Right
- `X` - Quit the Game

## How to Play

- Use your snake to consume fruits in the grid to get points.
- Don't bump into walls and yourself.
- Some fruits bring more bonus/penalty points.
- Use `X` to quit at any time.

## Technologies

- **C++** - Standard Library for I/O and Randomization
- **ANSI Escape Codes** - Console Graphics
- **Multi-threading** - Delays and Sleep Functions

