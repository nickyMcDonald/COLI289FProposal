#pragma once
#include <raylib.h>

// Width of the game grid
#define GAME_WIDTH 3

// Height of the game grid
#define GAME_HEIGHT GAME_WIDTH

// Color used for drawing the game elements
#define GAME_COLOR WHITE

// Mouse button used for player input
#define MOUSE_BUTTON MOUSE_BUTTON_LEFT

/// @brief Enumeration representing the state of a cell
typedef enum State
{
    // Empty state for a cell
    STATE_NONE,
    
    // X marked cell
    STATE_X,
    
    // O marked cell
    STATE_O,
} State;

/// @brief Structure representing a point in 2D space
typedef struct Point
{
    // The X coordinate
    unsigned char x;

    // The Y coordinate
    unsigned char y;
} Point;

/// @brief Function pointer type for player actions, the player is assumed to play 'X'
typedef Point (*Play)(const State** cells);

/// @brief Structure representing the game state
typedef struct Game
{
    Play playX;
    Play playO;
    State cells[GAME_WIDTH][GAME_HEIGHT];
    bool isOTurn;
    bool isOver;
} Game;
