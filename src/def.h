#pragma once
#include <raylib.h>
#include <string.h>

// Width and height of the game grid
#define GAME_WIDTH 3

// Color used for drawing the game elements
#define GAME_COLOR WHITE

// Mouse button used for player input
#define MOUSE_BUTTON MOUSE_BUTTON_LEFT

// Return the value which is greatest
#define abs(x) (((x) < 0) ? -(x) : (x))

/// @brief Enumeration representing the state of a cell
typedef enum State
{
    // Empty state for a cell
    STATE_NONE = 0,
    
    // X marked cell
    STATE_X = 1,
    
    // O marked cell
    STATE_O = 2,

    // Mask for both X and O states
    STATE_XO = STATE_X | STATE_O,

    // Draw state indicating a tie
    STATE_DRAW = 4,
} State;

/// @brief Structure representing a point in 2D space
typedef struct Point
{
    // The X coordinate
    unsigned char x;

    // The Y coordinate
    unsigned char y;
} Point;

/// @brief Forward declaration of game
typedef struct Game Game;

/// @brief Function pointer type for player actions, the player is assumed to play 'X'
typedef Point (*Play)(const Game* game);

/// @brief Structure representing the game state
typedef struct Game
{
    // Array of player functions indexed by State
    Play plays[STATE_O + 1];

    // Current state of the game cells
    State cells[GAME_WIDTH][GAME_WIDTH];

    // The current turn player
    State current;

    // The game winner state
    State winner;

    // The players last played positions
    Point positions[STATE_O + 1];

    // The current dice rolls
    unsigned char rolls[STATE_O + 1];
} Game;

/// @brief Structure representing a square area
typedef struct Area
{
    // Horizontal position
    unsigned short x;

    // Vertical position
    unsigned short y;

    // Height and width of the area
    unsigned short width;
} Area;
