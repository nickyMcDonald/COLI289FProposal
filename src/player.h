#pragma once
#include "game.h"

typedef int (*player_play)(const Game* game);

typedef struct Player
{
    player_play action;
    PlayerType type;
} Player;

int player_play_game(const Player* player, const Game* game)
{
    static Game g = {0};
    if (player->type & PLAYER_TYPE_O)
    {
        game_swap_players(game, &g);
    }
    return player ? player->action(game) : 0;
}
