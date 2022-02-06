#include "raylib.h"
#include <stdio.h>
#include <stdlib.h>
#include "jogo.h"

void Credits(){
    // Initialization 
    Windows();

    //Plano De Fundo
    Texture2D background = LoadTexture("Imagens/Credits/Credits.png");

    //Música
    Music music = LoadMusicStream("Imagens/Music/Juhani Junkala 1.wav");

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
