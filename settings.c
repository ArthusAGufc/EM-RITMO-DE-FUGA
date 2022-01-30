#include "raylib.h"
#include "jogo.h"

void Settings(){
    //Initialization
    Windows();

    //Carregando mídias
    Texture2D config = LoadTexture("Imagens/Credits/Config.png");
    Music music = LoadMusicStream("Imagens/Music/Theme.wav");
    
    SetTargetFPS(50);

    while (!WindowShouldClose()){
        SetMusicVolume(music, volume); //Definindo volume da música
        PlayMusicStream(music);

        if (IsKeyPressed(KEY_BACKSPACE)){
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
            volume = 0.10;
        else if (PosX == 520)
            volume = 0.09;
        else if (PosX == 490)
            volume = 0.08;
        else if (PosX == 460)
            volume = 0.07;
        else if (PosX == 430)
            volume = 0.06;
        else if (PosX == 400)
            volume = 0.05;
        else if (PosX == 370)
            volume = 0.04;
        else if (PosX == 340)
            volume = 0.03;
        else if (PosX == 310)
            volume = 0.02;
        else if (PosX == 280)
            volume = 0.01;
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
