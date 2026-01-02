#pragma once
#include "rules.h"

/// @brief Reset the game state
/// @param game The game to reset
/// @param play1 The first player's play function
/// @param play2 The second player's play function
void game_reset(Game* game, Play play1, Play play2)
{
    // Randomly assign players
    const State One = GetRandomValue(STATE_X, STATE_O);
    game->plays[One] = play1;
    game->plays[One ^ STATE_XO] = play2;
    
    // Clear the game board
    for (int y = 0; y < GAME_WIDTH; y++)
    {
        for (int x = 0; x < GAME_WIDTH; x++)
        {
            game->cells[x][y] = STATE_NONE;
        }
    }
    
    // Randomly decide who starts
    game->current = GetRandomValue(STATE_X, STATE_O);
    game->winner = STATE_NONE;

    // Assign middle as starting point
    for (int i = 0; i < (int)(sizeof(game->positions) / sizeof(*game->positions)); i++)
    {
        game->positions[i].x = 1;
        game->positions[i].y = 1;
    }

    for (int i = 0; i < (int)(sizeof(game->rolls) / sizeof(*game->rolls)); i++)
    {
        game->rolls[i] = 0;
    }
    
}

/// @brief Get the rectangular area where the game is drawn
/// @return The rectangular area of the game
Area* game_area_get()
{
    // Static area to return
    static Area area = {0};
    return &area;
}

/// @brief Let the player play their turn in the game
/// @param game The game state
void game_play(Game* game)
{
    // Do nothing if the game is over
    if (game->winner != STATE_NONE)
    {
        return;
    }

    // Call the player's play function
    const Point move = game->plays[game->current](game);
    
    // Evaluate the move
    State result;
    game->winner = evaluate_move(game, move, &result);

    // If the move was valid, update the game state
    if (result & STATE_XO)
    {
        game->cells[move.x][move.y] = result;
        if (game->winner == STATE_NONE)
        {
            game->positions[game->current] = move;
            game->rolls[game->current] = roll_dice();
            game->current ^= STATE_XO;
            while (!move_available(game))
            {
                game->rolls[game->current] = roll_dice();
            }
        }
    }
}

/// @brief Update the rectangular area where the game is drawn
/// @param screenWidth The current screen width
/// @param screenHeight The current screen height
void game_area_update(int screenWidth, int screenHeight)
{
    // Get the area to update
    Area* area = game_area_get();
    
    // Use minimal dimension to create a square area
    if (screenWidth < screenHeight)
    {
        area->x = 0;
        area->y = (screenHeight - screenWidth) / 2;
        area->width = screenWidth / GAME_WIDTH;
    }
    else
    {
        area->x = (screenWidth - screenHeight) / 2;
        area->y = 0;
        area->width = screenHeight / GAME_WIDTH;
    }
}

/// @brief Draw the current state of the game
/// @param game The game to draw
void game_redraw(const Game* game)
{
    // Get the area where the game is drawn, and calculate sizes
    const Area* area = game_area_get();
    const int Thick = area->width / 100;
    const int Radius = area->width * 2 / 3;
    const int Offset = (area->width - Radius) / 2;
    
    // Draw grid lines
    Vector2 startPos, endPos;
    for (int i = 1; i < GAME_WIDTH; i++)
    {
        const int Delta = i * area->width;
        startPos = (Vector2){area->x, area->y + Delta};
        endPos = (Vector2){area->x + area->width * GAME_WIDTH, area->y + Delta};
        DrawLineEx(startPos, endPos, Thick, GAME_COLOR);
        startPos = (Vector2){area->x + Delta, area->y};
        endPos = (Vector2){area->x + Delta, area->y + area->width * GAME_WIDTH};
        DrawLineEx(startPos, endPos, Thick, GAME_COLOR);
    }

    // Draw the X and O marks in the cells
    for (int y = 0; y < GAME_WIDTH; y++)
    {
        for (int x = 0; x < GAME_WIDTH; x++)
        {
            const Vector2 TopLeft = { area->x + x * area->width + Offset, area->y + y * area->width + Offset };
            const Vector2 TopRight = { TopLeft.x + Radius, TopLeft.y };
            const Vector2 BottomLeft = { TopLeft.x, TopLeft.y + Radius };
            const Vector2 BottomRight = { TopRight.x, BottomLeft.y };
            const Rectangle Rect = { TopLeft.x, TopLeft.y, Radius, Radius };

            switch (game->cells[x][y])
            {
            case STATE_X:
                DrawLineEx(TopLeft, BottomRight, Thick, GAME_COLOR);
                DrawLineEx(TopRight, BottomLeft, Thick, GAME_COLOR);
                break;
            case STATE_O:
                DrawRectangleRoundedLinesEx(Rect, 1.0f, 16, Thick, GAME_COLOR);
                break;
            default:
                break;
            }
        }
    }

    // Draw the current dice roll
    DrawRectangle(0, 0, Radius, Radius, BLACK);
    DrawText(TextFormat("%d", game->rolls[game->current]), 0, 0, Radius, WHITE);
}
