#include "raylib.h"
#include <stdio.h>
#include <stdlib.h>
#include "jogo.h"

void Settings(){
    //Initialization
    Windows();

    //Carregando mídias
    Texture2D config = LoadTexture("Imagens/Credits/Config.png");
    Music music = LoadMusicStream("Imagens/Music/Juhani Junkala 5.wav");
    
    SetTargetFPS(50);

    while (!WindowShouldClose()){
        SetMusicVolume(music, volume); //Definindo volume da música
        PlayMusicStream(music);

        if (IsKeyReleased(KEY_BACKSPACE)){
            CloseWindow();
            Menu();   
        }


        if (IsKeyPressed(KEY_D) || IsKeyPressed(KEY_RIGHT)){
            PosX += 30;
            if (PosX>550){
                PosX = 550;
            } 
        }
        else if (IsKeyPressed(KEY_A) || IsKeyPressed(KEY_LEFT)){
            PosX -= 30;
            if (PosX<250){
                PosX = 250;
            } 
        }
        
        if (PosX == 550)
            volume = 0.30;
        else if (PosX == 520)
            volume = 0.27;
        else if (PosX == 490)
            volume = 0.24;
        else if (PosX == 460)
            volume = 0.21;
        else if (PosX == 430)
            volume = 0.18;
        else if (PosX == 400)
            volume = 0.15;
        else if (PosX == 370)
            volume = 0.12;
        else if (PosX == 340)
            volume = 0.09;
        else if (PosX == 310)
            volume = 0.06;
        else if (PosX == 280)
            volume = 0.03;
        else if (PosX == 250)
            volume = 0;


        BeginDrawing();
            ClearBackground(BLACK);
            DrawTextureV(config, (Vector2) {0, 0}, WHITE);
            DrawCircleLines(PosX, 203, 20, WHITE);
            DrawCircleV((Vector2) {PosX, 203}, 15, WHITE);
        EndDrawing();

        UpdateMusicStream(music);
    }
    UnloadTexture(config);
    UnloadMusicStream(music);
    CloseWindow();
}
