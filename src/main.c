#include "real_player.h"
#include "computer_player.h"

int main()
{
    // Initialize the window
    SetConfigFlags(FLAG_WINDOW_RESIZABLE);
    InitWindow(640, 480, "Raylib Example");
    SetTargetFPS(30);
    
    // Center the window on the screen
    const int Monitor = GetCurrentMonitor();
    const int MonitorWidth = GetMonitorWidth(Monitor);
    const int MonitorHeight = GetMonitorHeight(Monitor);
    SetWindowSize(MonitorWidth / 2, MonitorHeight / 2);
    SetWindowPosition(MonitorWidth / 4, MonitorHeight / 4);

    // Game loop
    Game game = {0};
    while (!WindowShouldClose())
    {
        // Recalculate the rectangular area where the game will be drawn
        area_update(GetScreenWidth(), GetScreenHeight());

        // Clear the screen and draw the game
        BeginDrawing();
        ClearBackground(BLACK);
        game_redraw(&game);
        EndDrawing();
    }

    // Clean up resources
    CloseWindow();
    return 0;
}
