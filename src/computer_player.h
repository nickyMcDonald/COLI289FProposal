#pragma once
#include "game.h"

/// @brief Let a computer player play their turn by selecting a cell
/// @param cells The current game state
Point computer_player_play(const State cells[GAME_WIDTH][GAME_WIDTH])
{
    (void)cells;  // Unused parameter

    // Placeholder implementation
    return (Point){GetRandomValue(0, GAME_WIDTH - 1), GetRandomValue(0, GAME_WIDTH - 1)};
}
