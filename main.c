#include "raylib.h"
#include <game.c>
#include <credits.c>
#include <shop.c>
#include <history.c>
#include "jogo.h"

void Menu(){
        // Initialization 
        Windows();
        int PosY = 137; 

        //Plano De Fundo
        Texture2D background = LoadTexture("Imagens/Menu/MainMenu-1.png");

        SetTargetFPS(50);
        
        // Main game loop
        while (!WindowShouldClose() || IsKeyPressed(KEY_ENTER)){// Detect window close button or ESC key
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

            if (PosY == 137 && IsKeyPressed(KEY_ENTER)){
                /* code */
            }

            else if (PosY == 197 && IsKeyPressed(KEY_ENTER)){
                /* code */
            }
            
            else if (PosY == 257 && IsKeyPressed(KEY_ENTER)){
                CloseWindow();
                Game();
            }

            else if (PosY == 317 && IsKeyPressed(KEY_ENTER)){
                CloseWindow();
                Credits();
            }
            
            else if (PosY == 377 && IsKeyPressed(KEY_ENTER)){
                /* code */
            }
            
            BeginDrawing();
                ClearBackground(BLACK);
                DrawTextureV(background, (Vector2) {0,0},WHITE);
                DrawRectangleRoundedLines((Rectangle){280, PosY, 240, 30},0.3,5,5,LIGHTGRAY);
            EndDrawing();  
        }

        UnloadTexture(background);

        CloseWindow();// Close window and OpenGL context
    }

int main(){
    Menu();
    return 0;
}