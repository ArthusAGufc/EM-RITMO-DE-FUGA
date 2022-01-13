#include "raylib.h"

int main() 
{
    // Initialization 
    const int screenWidth = 900;
    const int screenHeight = 340;

    InitWindow(screenWidth, screenHeight, "Ritmo De Fuga");  

    //Personagem
    Image imageBandido = LoadImage("Imagens/SpriteIndividual/bandit1.png");
    ImageResize(&imageBandido, 50, 70);                                       
    Texture2D Bandido = LoadTextureFromImage(imageBandido);

    //Plano De Fundo
    Texture2D background = LoadTexture("Imagens/Maps/cidade.png");

    //Solo
    Texture2D retangulo = LoadTexture("Imagens/Maps/retangulo.png");

    SetTargetFPS(50);
    
    // Main game loop
    while (!WindowShouldClose()){// Detect window close button or ESC key
        
        BeginDrawing();
            ClearBackground(WHITE);
            DrawTextureV(background, (Vector2) {0,0},WHITE);
            DrawTextureV(retangulo, (Vector2) {0,265},WHITE);
            DrawTextureV(Bandido, (Vector2) {10,195},WHITE);
            //DrawRectangleRoundedLines((Rectangle){200, 100, 300, 50},0.1,5,3,WHITE);
        EndDrawing();  
    }

    UnloadTexture(background);
    UnloadTexture(retangulo);
    UnloadTexture(Bandido);

    CloseWindow();// Close window and OpenGL context
    
    return 0;
}
