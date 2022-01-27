#include "raylib.h"
#include "jogo.h"

void Credits(){
    // Initialization 
    const int screenWidth = 800;
    const int screenHeight = 500;

    InitWindow(screenWidth, screenHeight, "Ritmo De Fuga");  

    //Plano De Fundo
    Texture2D background = LoadTexture("Imagens/Credits/Credits.png");

    SetTargetFPS(50);
    
    // Main game loop
    while (!WindowShouldClose()){// Detect window close button or ESC key
        if (IsKeyPressed(KEY_BACKSPACE)){
            CloseWindow();
            Menu();   
        }
        
        BeginDrawing();
            ClearBackground(BLACK);
            DrawTextureV(background, (Vector2) {0,0},WHITE);
        EndDrawing();  
    }

    UnloadTexture(background);

    CloseWindow();
    
}