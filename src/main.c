#include "real_player.h"
#include "computer_player.h"

// The first player uses real input
Play player1 = real_player_play;

// The second player is a computer
Play player2 = computer_player_play;

int main()
{
    // Initialize the window
    SetConfigFlags(FLAG_WINDOW_RESIZABLE);
    InitWindow(640, 480, "Tic-Tac-Toe");
    SetTargetFPS(30);
    
    // Center the window on the screen
    const int Monitor = GetCurrentMonitor();
    const int MonitorWidth = GetMonitorWidth(Monitor);
    const int MonitorHeight = GetMonitorHeight(Monitor);
    SetWindowSize(MonitorWidth / 2, MonitorHeight / 2);
    SetWindowPosition(MonitorWidth / 4, MonitorHeight / 4);

    // Game loop
    Game game = {0};
    game_reset(&game, player1, player2);
    while (!WindowShouldClose())
    {
        // Recalculate the rectangular area where the game will be drawn
        game_area_update(GetScreenWidth(), GetScreenHeight());

        // Clear the screen and draw the game
        BeginDrawing();
        ClearBackground(BLACK);
        game_redraw(&game);
        EndDrawing();

        // Let players play their turns
        game_play_player(&game);

        // Reset the game if it's over and the mouse button is pressed
        if (game.isOver && IsMouseButtonPressed(MOUSE_BUTTON))
        {
            game_reset(&game, player1, player2);
        }
    }

    // Clean up resources
    CloseWindow();
    return 0;
}
