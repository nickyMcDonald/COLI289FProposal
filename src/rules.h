#pragma once
#include "def.h"

/// @brief Checks if a player was won
/// @param cells The board
/// @param player The last player to move
/// @return The winning player
State check_win(const State cells[GAME_WIDTH][GAME_WIDTH], State player)
{
    // Check for straight win
    for (int i = 0; i < GAME_WIDTH; i++)
    {
        bool isWinX = cells[i][0] & STATE_XO;
        bool isWinY = cells[0][i] & STATE_XO;
        for (int j = 1; j < GAME_WIDTH; j++)
        {
            if (cells[i][0] != cells[i][j])
            {
                isWinX = false;
            }
            if (cells[0][i] != cells[j][i])
            {
                isWinY = false;
            }
        }
        if (isWinX || isWinY)
        {
            return player;
        }
    }

    // Check for diagonal win
    bool isWinDown = cells[0][0] & STATE_XO;
    bool isWinUp = cells[0][GAME_WIDTH - 1] & STATE_XO;
    for (int i = 1; i < GAME_WIDTH; i++)
    {
        if (cells[i][i] != cells[0][0])
        {
            isWinDown = false;
        }
        if (cells[i][GAME_WIDTH - 1 - i] != cells[0][GAME_WIDTH - 1])
        {
            isWinUp = false;
        }
    }
    if (isWinDown || isWinUp)
    {
        return player;
    }
    
    // Check for draw
    player = STATE_DRAW;
    for (int y = 0; y < GAME_WIDTH; y++)
    {
        for (int x = 0; x < GAME_WIDTH; x++)
        {
            if (!(cells[x][y] & STATE_XO))
            {
                player = STATE_NONE;
            }
        }
    }
    return player;
}

/// @brief Evaluate a proposed move and determine if it results in a win or draw
/// @param cells The current game state
/// @param move The proposed move
/// @param player The player making the move
/// @param result Output parameter to hold the result cell state
/// @return The winning state if the move results in a win, draw if the move results in a draw, otherwise STATE_NONE
State evaluate_move(const State cells[GAME_WIDTH][GAME_WIDTH], Point move, State player, State* result)
{
    // Default to no result and get player symbol
    *result = STATE_NONE;

    // Validate the move
    if ((move.x < GAME_WIDTH) && (move.y < GAME_WIDTH) && (cells[move.x][move.y] == STATE_NONE))
    {
        // Set the result to the player's symbol
        *result = player;

        // Create a copy of the cells with the proposed move applied
        static State c[GAME_WIDTH][GAME_WIDTH] = {0};
        for (int y = 0; y < GAME_WIDTH; y++)
        {
            for (int x = 0; x < GAME_WIDTH; x++)
            {
                c[x][y] = cells[x][y];
            }
        }
        c[move.x][move.y] = player;
        return check_win(c, player);
    }
    return STATE_NONE;
}
