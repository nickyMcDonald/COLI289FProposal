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
    for (int y = 0; y < GAME_HEIGHT; y++)
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
Rectangle* game_area_get()
{
    // Static area to return
    static Rectangle area = {0};
    return &area;
}

/// @brief Update the rectangular area where the game is drawn
/// @param screenWidth The current screen width
/// @param screenHeight The current screen height
void game_area_update(int screenWidth, int screenHeight)
{
    // Get the area to update
    Rectangle* area = game_area_get();
    
    // Use minimal dimension to create a square area
    if (screenWidth < screenHeight)
    {
        area->x = 0;
        area->y = (screenHeight - screenWidth) / 2;
        area->width = screenWidth;
        area->height = screenWidth;
    }
    else
    {
        area->x = (screenWidth - screenHeight) / 2;
        area->y = 0;
        area->width = screenHeight;
        area->height = screenHeight;
    }
}

/// @brief Draw the current state of the game
/// @param game The game to draw
void game_redraw(const Game* game)
{
    // Get the area where the game is drawn, and calculate sizes
    const Rectangle* area = game_area_get();
    const float Thick = (area->width + area->height) / (2 * 100);
    const float CellHeight = area->height / GAME_HEIGHT;
    
    // Draw horizontal grid lines
    for (int y = 1; y < GAME_HEIGHT; y++)
    {
        const Vector2 StartPos = {area->x, area->y + y * CellHeight};
        const Vector2 EndPos = {area->x + area->width, area->y + y * CellHeight};
        DrawLineEx(StartPos, EndPos, Thick, GAME_COLOR);
    }
    const float CellWidth = area->width / GAME_WIDTH;

    // Draw vertical grid lines
    for (int x = 1; x < GAME_WIDTH; x++)
    {
        const Vector2 StartPos = {area->x + x * CellWidth, area->y};
        const Vector2 EndPos = {area->x + x * CellWidth, area->y + area->height};
        DrawLineEx(StartPos, EndPos, Thick, GAME_COLOR);
    }
    const float Radius = (CellWidth + CellHeight) / 3;
    const float OffsetX = (CellWidth - Radius) / 2;
    const float OffsetY = (CellHeight - Radius) / 2;

    // Draw the X and O marks in the cells
    for (int y = 0; y < GAME_HEIGHT; y++)
    {
        for (int x = 0; x < GAME_WIDTH; x++)
        {
            const Vector2 TopLeft = { area->x + x * CellWidth + OffsetX, area->y + y * CellHeight + OffsetY };
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
    static State cells[GAME_WIDTH][GAME_HEIGHT] = {0};

    // Swap cell states
    for (int y = 0; y < GAME_HEIGHT; y++)
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
    if ((move.x < GAME_WIDTH) && (move.y < GAME_HEIGHT) && (game->cells[move.x][move.y] == STATE_NONE))
    {
        game->cells[move.x][move.y] = game->isOTurn ? STATE_O : STATE_X;
        game->isOTurn = !game->isOTurn;

        // Check for a win or a draw
        bool isDraw = true;
        for (int y = 0; y < GAME_HEIGHT; y++)
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
        
        // Check rows for a win
        for (int y = 0; y < GAME_HEIGHT; y++)
        {
            if (game->cells[0][y] == STATE_NONE)
            {
                continue;
            }
            bool isWin = true;

            for (int x = 1; x < GAME_WIDTH; x++)
            {
                if (game->cells[x][y] != game->cells[0][y])
                {
                    isWin = false;
                    break;
                }
            }
            if (isWin)
            {
                game->isOver = true;
            }
        }

        // Check columns for a win
        for (int x = 0; x < GAME_WIDTH; x++)
        {
            if (game->cells[x][0] == STATE_NONE)
            {
                continue;
            }
            bool isWin = true;

            for (int y = 1; y < GAME_HEIGHT; y++)
            {
                if (game->cells[x][y] != game->cells[x][0])
                {
                    isWin = false;
                    break;
                }
            }
            if (isWin)
            {
                game->isOver = true;
            }
        }

        // Check diagonals for a win
        bool isWinDown = game->cells[0][0] != STATE_NONE;
        bool isWinUp = game->cells[0][GAME_HEIGHT - 1] != STATE_NONE;
        for (int i = 1; (i < GAME_WIDTH) && (i < GAME_HEIGHT); i++)
        {
            if (game->cells[i][i] != game->cells[0][0])
            {
                isWinDown = false;
            }
            if (game->cells[i][GAME_HEIGHT - 1 - i] != game->cells[0][GAME_HEIGHT - 1])
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
