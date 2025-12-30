#pragma once
#include "game.h"

/// @brief Let a computer player play their turn by selecting a cell
/// @param player The current player
/// @param cells The current game state
Point computer_player_play(State player, const State cells[GAME_WIDTH][GAME_WIDTH])
{
    // Get the current call stack base
    static bool nowInner = true;
    bool isInner = nowInner;
    nowInner = false;

    // Copy the current cells
    State c[GAME_WIDTH][GAME_WIDTH] = {0};
    memcpy(c, cells, sizeof(c));
    
    Point move;
    unsigned char maxWeight = 0;
    unsigned char moves[GAME_WIDTH][GAME_WIDTH] = {0};
    for (move = (Point){0, 0}; move.y < GAME_WIDTH; move.y++)
    {
        for (move.x = 0; move.x < GAME_WIDTH; move.x++)
        {
            // The favorably of the move
            unsigned char moveWeight;

            // Save the cell state
            const State Old = c[move.x][move.y];

            switch (evaluate_move(cells, move, player, &c[move.x][move.y]))
            {
            case STATE_X:
                moveWeight = (player == STATE_X) ? 254 : 1; // A win by X
                break;
            case STATE_O:
                moveWeight = (player == STATE_O) ? 254 : 1; // A win by O
                break;
            case STATE_DRAW:
                moveWeight = 127; // A draw between both players
                break;
            default:
                if (c[move.x][move.y] == STATE_NONE)
                {
                    moveWeight = 0; // Failed move, avoid this move
                    break;
                }

                // Gather enemy's best move weight
                moveWeight = 255 - computer_player_play(player ^ STATE_XO, c).x;
                break;
            }

            // Restore current cells and update weights
            c[move.x][move.y] = Old;
            maxWeight = (moveWeight > maxWeight) ? moveWeight : maxWeight;
            moves[move.x][move.y] = moveWeight;
        }
    }

    // Check for last call
    if (isInner)
    {
        // Select a random move among those with the highest weight
        move.x = GAME_WIDTH;
        while (move.x >= GAME_WIDTH)
        {
            move.x = GetRandomValue(0, GAME_WIDTH - 1);
            move.y = GetRandomValue(0, GAME_WIDTH - 1);

            if (moves[move.x][move.y] < maxWeight)
            {
                move.x = GAME_WIDTH;
            }
        }
        nowInner = true;
    }
    else
    {
        // Save the maximum weight
        move.x = maxWeight;
    }
    return move;
}
