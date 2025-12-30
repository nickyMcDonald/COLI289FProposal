#pragma once
#include "game.h"

Point computer_player_play(const Game* game)
{
    // Placeholder implementation
    return (Point){GetRandomValue(0, GAME_WIDTH - 1), GetRandomValue(0, GAME_HEIGHT - 1)};
}
