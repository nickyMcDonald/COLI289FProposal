#include "raylib.h"

int main()
{
    // Initialize the window
    InitWindow(800, 600, "Raylib Example");

    // Set the target frames per second
    SetTargetFPS(60);

    // Main game loop
    while (!WindowShouldClose())
    {
        // Clear the screen with a background color
        BeginDrawing();
        ClearBackground(RAYWHITE);

        // Draw a rectangle
        DrawRectangle(100, 100, 200, 100, BLUE);

        // Draw a circle
        DrawCircle(400, 300, 50, RED);

        // Draw text
        DrawText("Hello, Raylib!", 300, 500, 20, BLACK);

        // End drawing
        EndDrawing();
    }

    // Close the window and clean up resources
    CloseWindow();

    return 0;
}
