#pragma once
#include "def.h"

/// @brief Reset the game state
/// @param game The game to reset
/// @param play1 The first player's play function
/// @param play2 The second player's play function
void game_reset(Game* game, Play play1, Play play2)
{
    // Randomly assign players
    const bool firstIsPlay1 = GetRandomValue(0, 1);
    game->playX = firstIsPlay1 ? play1 : play2;
    game->playO = firstIsPlay1 ? play2 : play1;

    // Clear the game board
    for (int y = 0; y < GAME_WIDTH; y++)
    {
        for (int x = 0; x < GAME_WIDTH; x++)
        {
            game->cells[x][y] = STATE_NONE;
        }
    }

    // Randomly decide who starts
    game->isOTurn = GetRandomValue(0, 1);
    game->isOver = false;
}

/// @brief Get the rectangular area where the game is drawn
/// @return The rectangular area of the game
Area* game_area_get()
{
    // Static area to return
    static Area area = {0};
    return &area;
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
}

/// @brief Let the player play their turn in the game
/// @param game The game state
void game_play_player(Game* game)
{
    // Do nothing if the game is over
    if (game->isOver)
    {
        return;
    }

    // Possibly swap the game state
    static State cells[GAME_WIDTH][GAME_WIDTH] = {0};

    // Swap cell states
    for (int y = 0; y < GAME_WIDTH; y++)
    {
        for (int x = 0; x < GAME_WIDTH; x++)
        {
            switch (game->cells[x][y])
            {
            case STATE_X:
                cells[x][y] = game->isOTurn ? STATE_O : STATE_X;
                break;
            case STATE_O:
                cells[x][y] = game->isOTurn ? STATE_X : STATE_O;
                break;
            default:
                cells[x][y] = game->cells[x][y];
                break;
            }
        }
    }

    // Call the player's play function
    const Point move = game->isOTurn ? game->playO(cells) : game->playX(cells);

    // Validate the move
    if ((move.x < GAME_WIDTH) && (move.y < GAME_WIDTH) && (game->cells[move.x][move.y] == STATE_NONE))
    {
        game->cells[move.x][move.y] = game->isOTurn ? STATE_O : STATE_X;
        game->isOTurn = !game->isOTurn;

        // Check for draw
        bool isDraw = true;
        for (int y = 0; y < GAME_WIDTH; y++)
        {
            for (int x = 0; x < GAME_WIDTH; x++)
            {
                if (game->cells[x][y] == STATE_NONE)
                {
                    isDraw = false;
                }
            }
        }
        if (isDraw)
        {
            game->isOver = true;
        }

        // Check for straight win
        for (int i = 0; i < GAME_WIDTH; i++)
        {
            bool isWinX = game->cells[i][0] != STATE_NONE;
            bool isWinY = game->cells[0][i] != STATE_NONE;
            for (int j = 1; j < GAME_WIDTH; j++)
            {
                if (game->cells[i][0] != game->cells[i][j])
                {
                    isWinX = false;
                }
                if (game->cells[0][i] != game->cells[j][i])
                {
                    isWinY = false;
                }
            }
            if (isWinX || isWinY)
            {
                game->isOver = true;
            }
        }

        // Check for diagonal win
        bool isWinDown = game->cells[0][0] != STATE_NONE;
        bool isWinUp = game->cells[0][GAME_WIDTH - 1] != STATE_NONE;
        for (int i = 1; i < GAME_WIDTH; i++)
        {
            if (game->cells[i][i] != game->cells[0][0])
            {
                isWinDown = false;
            }
            if (game->cells[i][GAME_WIDTH - 1 - i] != game->cells[0][GAME_WIDTH - 1])
            {
                isWinUp = false;
            }
        }
        if (isWinDown || isWinUp)
        {
            game->isOver = true;
        }
    }
}
