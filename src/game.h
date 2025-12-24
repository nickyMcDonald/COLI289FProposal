#pragma once
#include "area.h"

#define GAME_WIDTH 3
#define GAME_HEIGHT GAME_WIDTH

#define LINE_COLOR WHITE
#define X_COLOR RED
#define O_COLOR BLUE

typedef enum
{
    PLAYER_TYPE_X = 1,
    PLAYER_TYPE_O = 2,
    PLAYER_TYPE_ROCK = 4,
    PLAYER_TYPE_PAPER = 8,
    PLAYER_TYPE_SCISSORS = 16,
} PlayerType;

typedef struct Player Player;

typedef enum CellState
{
    CELL_STATE_EMPTY = 0,
    CELL_STATE_X = 1,
    CELL_STATE_O = 2,
} CellState;

typedef struct Game
{
    Player* Player1;
    Player* Player2;
    CellState cells[GAME_WIDTH][GAME_HEIGHT];
} Game;

void game_swap_players(const Game* source, Game* target)
{
    target->Player1 = source->Player2;
    target->Player2 = source->Player1;
    for (int y = 0; y < GAME_HEIGHT; y++)
    {
        for (int x = 0; x < GAME_WIDTH; x++)
        {
            switch (source->cells[x][y])
            {
            case CELL_STATE_X:
                target->cells[x][y] = CELL_STATE_O;
                break;
            case CELL_STATE_O:
                target->cells[x][y] = CELL_STATE_X;
                break;
            default:
                target->cells[x][y] = CELL_STATE_EMPTY;
                break;
            }
        }
    }
}

void game_redraw(const Game* game)
{
    const Rectangle* area = area_get();
    const float Thick = (area->width + area->height) / (2 * 100);
    const float CellHeight = area->height / GAME_HEIGHT;
    
    for (int y = 1; y < GAME_HEIGHT; y++)
    {
        const Vector2 StartPos = {area->x, area->y + y * CellHeight};
        const Vector2 EndPos = {area->x + area->width, area->y + y * CellHeight};
        DrawLineEx(StartPos, EndPos, Thick, LINE_COLOR);
    }
    const float CellWidth = area->width / GAME_WIDTH;

    for (int x = 1; x < GAME_WIDTH; x++)
    {
        const Vector2 StartPos = {area->x + x * CellWidth, area->y};
        const Vector2 EndPos = {area->x + x * CellWidth, area->y + area->height};
        DrawLineEx(StartPos, EndPos, Thick, LINE_COLOR);
    }
    const float Radius = (CellWidth + CellHeight) / 3;
    const float OffsetX = (CellWidth - Radius) / 2;
    const float OffsetY = (CellHeight - Radius) / 2;

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
            case CELL_STATE_X:
                DrawLineEx(TopLeft, BottomRight, Thick, X_COLOR);
                DrawLineEx(TopRight, BottomLeft, Thick, X_COLOR);
                break;
            case CELL_STATE_O:
                DrawRectangleRoundedLinesEx(Rect, 1.0f, 6, Thick, O_COLOR);
                break;
            default:
                break;
            }
        }
    }
}
