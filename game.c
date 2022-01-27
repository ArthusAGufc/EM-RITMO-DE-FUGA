#include "raylib.h"
#include "jogo.h"

void Game(){
    // Initialization 
    const int screenWidth = 900;
    const int screenHeight = 340;

    InitWindow(screenWidth, screenHeight, "Ritmo De Fuga");  

    //Personagem
    Image imageBandido = LoadImage("Imagens/SpriteIndividual/SpriteSheet-Bandit-1-1.png");
    ImageResize(&imageBandido, 50, 70);                                       
    Texture2D Bandido = LoadTextureFromImage(imageBandido);

    //Plano De Fundo
    Texture2D background = LoadTexture("Imagens/Maps/cidade.png");

    //Solo
    Texture2D retangulo = LoadTexture("Imagens/Maps/retangulo-2.png");

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
            DrawTextureV(retangulo, (Vector2) {0,265},WHITE);
            DrawTextureV(Bandido, (Vector2) {10,195},WHITE);
            //DrawRectangleRoundedLines((Rectangle){200, 100, 300, 50},0.1,5,3,WHITE);
        EndDrawing();  
    }

    UnloadTexture(background);
    UnloadTexture(retangulo);
    UnloadTexture(Bandido);

    CloseWindow();
    
    Menu();
}