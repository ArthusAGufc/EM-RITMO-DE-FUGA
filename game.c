#include "raylib.h"
#include "jogo.h"

typedef struct personagem{
    bool jump;
    float Jump_Timer;
    int ret_x, ret_y;
}Personagem;

void Game(){
    //Criação de Personagem
    Personagem P1;
    P1.ret_x = 100;
    P1.ret_y = 215;

    // Initialization 
    const int screenWidth = 900;
    const int screenHeight = 340;

    InitWindow(screenWidth, screenHeight, "Ritmo De Fuga");  

    //Personagem
    //ImageResize(&imageBandido, 50, 70);                                  
    Texture2D Bandido = LoadTexture("Imagens/SpriteSheets/SpriteSheet-Bandit-1.png");

    //Plano De Fundo
    Texture2D background = LoadTexture("Imagens/Maps/cidade.png");

    //Música
    Music music = LoadMusicStream("Imagens/Music/Theme.wav");

    //Solo
    Texture2D retangulo = LoadTexture("Imagens/Maps/retangulo-2.png");

    SetTargetFPS(50);
    P1.jump = false;

    // Main game loop
    while (!WindowShouldClose()){// Detect window close button or ESC key
        SetMusicVolume(music, volume);
        PlayMusicStream(music);
        
        if (IsKeyPressed(KEY_BACKSPACE)){
            CloseWindow();
            Menu();   
        }

        if (IsKeyPressed(KEY_SPACE) || IsKeyPressed(KEY_UP))
                P1.jump = true;
        
        if (P1.jump){
            P1.Jump_Timer += 4;
            
            if (P1.Jump_Timer <= 90)
                P1.ret_y -= 5;
            else
                P1.ret_y += 5;
        }
        
        if (P1.Jump_Timer > 172.5){
            P1.Jump_Timer = 0;
            P1.jump = false;
        }
        
        BeginDrawing();
            ClearBackground(BLACK);
            DrawTextureV(background, (Vector2) {0,0},WHITE);
            DrawTextureV(retangulo, (Vector2) {0,265},WHITE);
            DrawTextureV(Bandido, (Vector2) {200, 200}, WHITE);
            DrawRectangle(P1.ret_x, P1.ret_y, 50, 50, WHITE);
        EndDrawing();  

        UpdateMusicStream(music);
    }

    UnloadMusicStream(music);
    UnloadTexture(background);
    UnloadTexture(retangulo);
    UnloadTexture(Bandido);

    CloseWindow();
    
    Menu();
}
