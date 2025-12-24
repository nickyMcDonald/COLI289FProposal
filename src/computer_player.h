#pragma once
#include "player.h"

int computer_rock_play(const Game* game)
{

}

int computer_paper_play(const Game* game)
{

}

int computer_scissors_play(const Game* game)
{

}

int computer_player_play(const Game* game)
{
    switch (game->Player1->type & (PLAYER_TYPE_ROCK | PLAYER_TYPE_PAPER | PLAYER_TYPE_SCISSORS))
    {
    case PLAYER_TYPE_ROCK:
        return computer_rock_play(game);
    case PLAYER_TYPE_PAPER:
        return computer_paper_play(game);
    default:
        return computer_scissors_play(game);
    }
}
