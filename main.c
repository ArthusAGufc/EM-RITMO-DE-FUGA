#include "raylib.h"

int main() 
{
    // Initialization 
    const int screenWidth = 800;
    const int screenHeight = 500;

    InitWindow(screenWidth, screenHeight, "Ritmo De Fuga");  

    //Plano De Fundo
    Texture2D background = LoadTexture("Imagens/Menu/MainMenu.png");

    SetTargetFPS(50);
    
    // Main game loop
    while (!WindowShouldClose()){// Detect window close button or ESC key
        BeginDrawing();
            ClearBackground(WHITE);
            DrawTextureV(background, (Vector2) {0,0},WHITE);
        EndDrawing();  
    }

    UnloadTexture(background);

    CloseWindow();// Close window and OpenGL context
    
    return 0;
}
