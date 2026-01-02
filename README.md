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

## Example

### The Game starts with the player or computer playing first. Here, the player goes first
- They can go anywhere on the board
<img width="448" height="253" alt="Screenshot 2026-01-02 121246" src="https://github.com/user-attachments/assets/9c5c9461-df65-4be7-9138-be2e797108a5" />

### The player chooses to go in the top left corner, and it's now the computer's turn
- The computer also gets to go anywhere on the board for its first turn
<img width="448" height="253" alt="Screenshot 2026-01-02 121335" src="https://github.com/user-attachments/assets/dd396a1d-b3ac-44a3-919b-c15138269d1d" />

### The computer takes the center, the die is rolled for the first time, and the player is given two options to move to
- The player can take the top right corner
- The player can take the bottom left corner
- All other spaces are out of reach, taken, or not an even number of spaces away from the player's last move
<img width="448" height="253" alt="Screenshot 2026-01-02 121340" src="https://github.com/user-attachments/assets/75b37d35-c8ad-4e61-80d7-054b62359b3e" />

### The player chooses to go to the top right corner, the die is rolled again, and the computer has four options to move to
- The computer can go to any of the edges directly adjacent to the middle
- All other squares are out of reach since the computer rolled a 1
<img width="448" height="253" alt="Screenshot 2026-01-02 121352" src="https://github.com/user-attachments/assets/c5dbc62d-84cb-4563-9a84-c24860e60e14" />

### The computer takes the bottom edge, and the player is given only one place to go
- The player can go to the bottom right corner
<img width="448" height="253" alt="Screenshot 2026-01-02 121410" src="https://github.com/user-attachments/assets/ee4fe1aa-9f12-4032-8fc4-a82a5eb39f52" />

### After the player takes this square, the computer has only one place to go
- The computer can take the bottom left corner
<img width="448" height="253" alt="Screenshot 2026-01-02 121415" src="https://github.com/user-attachments/assets/13e0d8b2-3656-4ca8-b092-d8d08ab0aa25" />

### After the computer's move, the player can take any of the remaining squares
- The top, left, or right edges
<img width="448" height="253" alt="Screenshot 2026-01-02 121425" src="https://github.com/user-attachments/assets/b3fd8d44-727b-44a0-af50-d3012a1ca48e" />

### The player goes on the right edge and wins the game!
- If the player clicks anywhere again, a new game will begin
<img width="448" height="253" alt="Screenshot 2026-01-02 121432" src="https://github.com/user-attachments/assets/9b76158c-6d50-4eb0-bd1f-9969bbb437e4" />
