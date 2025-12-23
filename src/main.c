#include "raylib.h"
#define TITLE "Raylib Example"

int main()
{
    // Initialize the window
    SetConfigFlags(FLAG_WINDOW_RESIZABLE);
    InitWindow(640, 480, TITLE);
    SetTargetFPS(30);

    // Center the window on the screen
    const int Monitor = GetCurrentMonitor();
    const int MonitorWidth = GetMonitorWidth(Monitor);
    const int MonitorHeight = GetMonitorHeight(Monitor);
    SetWindowSize(MonitorWidth / 2, MonitorHeight / 2);
    SetWindowPosition(MonitorWidth / 4, MonitorHeight / 4);

    // Game loop
    while (!WindowShouldClose())
    {
        // Clear the screen with a background color
        BeginDrawing();
        ClearBackground(BLACK);

        // Draw a rectangle
        DrawRectangle(100, 100, 200, 100, BLUE);

        // Draw a circle
        DrawCircle(400, 300, 50, RED);

        // Draw text
        DrawText("Hello, Raylib!", 300, 500, 20, BLACK);

        // End drawing
        EndDrawing();
    }

    // Clean up resources
    CloseWindow();
    return 0;
}
