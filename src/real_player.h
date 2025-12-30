#pragma once
#include "game.h"

/// @brief Let a real player play their turn by clicking on the game grid
/// @param cells The current game state
Point real_player_play(const State cells[GAME_WIDTH][GAME_WIDTH])
{
    (void)cells;  // Unused parameter

    // Check for mouse input
    if (IsMouseButtonPressed(MOUSE_BUTTON))
    {
        // Get the area where the game is drawn
        const Area* area = game_area_get();

        // Calculate the cell coordinates based on mouse position
        const Vector2 MousePos = GetMousePosition();
        const int x = (int)((MousePos.x - area->x) / area->width);
        const int y = (int)((MousePos.y - area->y) / area->width);

        // Return the cell coordinates if they are within bounds
        if ((x < GAME_WIDTH) && (y < GAME_WIDTH))
        {
            PollInputEvents();
            return (Point){x, y};
        }
    }
    
    // No valid move made
    return (Point){GAME_WIDTH, GAME_WIDTH};
}
