#include "raylib.h"
#include <stdio.h>
#include <stdlib.h>
#include "jogo.h"


void History(){
    // Initialization 
    const int screenWidth = 800;
    const int screenHeight = 500;

    InitWindow(screenWidth, screenHeight, "Ritmo De Fuga");  

    //Plano De Fundo
    Texture2D background = LoadTexture("Imagens/History/historia.png");
    Music music = LoadMusicStream("Imagens/Music/Juhani Junkala 5.wav");

    SetTargetFPS(50);
    
    // Main game loop
    while (!WindowShouldClose()){// Detect window close button or ESC key
        
        SetMusicVolume(music, volume);
        PlayMusicStream(music);
        
        if (IsKeyReleased(KEY_BACKSPACE)){
            CloseWindow();
            Menu();   
        }
        
        BeginDrawing();
            ClearBackground(BLACK);
            DrawTextureV(background, (Vector2) {0,0},WHITE);
        EndDrawing();  
        
        UpdateMusicStream(music);
    }

    UnloadTexture(background);
    UnloadMusicStream(music);

    CloseWindow();
    
}
