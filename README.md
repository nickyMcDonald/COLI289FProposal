# Tic-Tac-Toe With a Twist

A reimagined version of Tic-Tac-Toe written in C using raylib.

## Features

- **A digital Tic-Tac-Toe game board** - There are Xs and Os that can be played on it, with a winning condition of three-in-a-row
- **Intelligent AI bot** - The bot will play against the player and attempt to win
- **A die** - A single die is rolled for a specific number of steps, dictating where a player can move

## Building

```bash
# Clone this repository to your PC
# GCC for Windows and Linux, or Clang for macOS, must be installed
# Make must be installed
# This project has been tested to work for Windows, but may not work for Linux and Mac
# Navigate to the cloned repository folder in a terminal or cmd window
# Use the make command to build and run the game
make
```

## Controls

- **Left mouse button**: Use the mouse to place an X or O.

## Rules

The rules are the same as Tic-Tac-Toe, with a few exceptions.
- Every player's turn, there is a "die" rolled in the top left corner
- The die can be any number from 1 to 4
- The die number represents the number of spaces the player must move to from their last placed X or O
- Moves can go anywhere over the board, jumping over Xs and Os is allowed
- The first round starts with no die number, which means both players can make their opening move anywhere
