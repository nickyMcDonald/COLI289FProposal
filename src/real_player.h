#pragma once
#include "game.h"

/// @brief Let a real player play their turn by clicking on the game grid
/// @param game The current game state
Point real_player_play(const Game* game)
{
    // Check for mouse input
    if (IsMouseButtonPressed(MOUSE_BUTTON))
    {
        // Get the area where the game is drawn
        const Rectangle* area = game_area_get();
        const float CellWidth = area->width / GAME_WIDTH;
        const float CellHeight = area->height / GAME_HEIGHT;

        // Calculate the cell coordinates based on mouse position
        const Vector2 MousePos = GetMousePosition();
        const int x = (int)((MousePos.x - area->x) / CellWidth);
        const int y = (int)((MousePos.y - area->y) / CellHeight);

        // Return the cell coordinates if they are within bounds
        if ((x < GAME_WIDTH) && (y < GAME_HEIGHT))
        {
            PollInputEvents();
            return (Point){x, y};
        }
    }
    
    // No valid move made
    return (Point){GAME_WIDTH, GAME_HEIGHT};
}
