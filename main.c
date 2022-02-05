#include "raylib.h"
#include <stdio.h>
#include <stdlib.h>
#include <game.c>
#include <credits.c>
#include <shop.c>
#include <history.c>
#include <settings.c>
#include "jogo.h"

void Menu(){
        // Initialization 
        Windows();
        int PosY = 137; 

        //Plano De Fundo
        Music music = LoadMusicStream("Imagens/Music/Theme.wav");
        Texture2D background = LoadTexture("Imagens/Menu/MainMenu-1.png");
        SetTargetFPS(50);
        
        // Main game loop
        while (!WindowShouldClose() || IsKeyPressed(KEY_ENTER)){// Detect window close button or ESC key
            PlayMusicStream(music);
            SetMusicVolume(music, volume);
            if (IsKeyPressed(KEY_S) || IsKeyPressed(KEY_DOWN)){
                PosY += 60;
                if (PosY>377){
                    PosY = 377;
                } 
            }
            else if (IsKeyPressed(KEY_W) || IsKeyPressed(KEY_UP)){
                PosY -= 60;
                if (PosY<137){
                    PosY = 137;
                } 
            }


            if (PosY == 137 &&  IsKeyReleased(KEY_ENTER)){
                CloseWindow();
                History();
            }

            else if (PosY == 197 && IsKeyReleased(KEY_ENTER)){
                CloseWindow();
                shop();
            }
            
            else if (PosY == 257 && IsKeyReleased(KEY_ENTER)){
                CloseWindow();
                Game();
            }

            else if (PosY == 317 && IsKeyReleased(KEY_ENTER)){
                CloseWindow();
                Credits();
            }
            
            else if (PosY == 377 && IsKeyReleased(KEY_ENTER)){
                CloseWindow();
                Settings();
            }

            BeginDrawing();
                ClearBackground(BLACK);
                DrawTextureV(background, (Vector2) {0, 0},WHITE);
                DrawRectangleRoundedLines((Rectangle){280, PosY, 240, 30},0.3,5,5,LIGHTGRAY);
            EndDrawing();  
            UpdateMusicStream(music);
        }

        
        UnloadTexture(background);
        UnloadMusicStream(music);
        CloseWindow();// Close window and OpenGL context
    }

int main(){
    InitAudioDevice();
    Menu();
    CloseAudioDevice();
    return 0;
}
