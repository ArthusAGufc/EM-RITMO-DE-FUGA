#include "raylib.h"
#include "jogo.h"

void shop(){

    const int screenWidth=800, screenHeight=500;
    int PosY=395, PosX=17;
    int pts=0; //variavel temporaria, mudar pelos pontos quando feitos.
    
    InitWindow(screenWidth,screenHeight, "Shop");
    
    //Imagem de fundo
    Texture2D tipeone = LoadTexture("Imagens/Shop/loja_tipo_1.png");
    Texture2D tipetwo = LoadTexture("Imagens/Shop/loja_tipo_2.png");
    Texture2D tipetree = LoadTexture("Imagens/Shop/loja_tipo_3.png");
    Music music = LoadMusicStream("Imagens/Music/Theme.wav");

    SetTargetFPS(60);

    //Loop da loja
    while(!WindowShouldClose()){
        
        SetMusicVolume(music, volume);
        PlayMusicStream(music);

        //Escolhendo os botões
        if((IsKeyPressed(KEY_W)||IsKeyPressed(KEY_UP)) && PosX==282){
            PosY -= 56;
            if(PosY<395)
                PosY=395;
        }else if((IsKeyPressed(KEY_S)||IsKeyPressed(KEY_DOWN)) && PosX==282){
            PosY += 56;
            if(PosY>451)
                PosY=451;
        }else if((IsKeyPressed(KEY_D)||IsKeyPressed(KEY_RIGHT)) && PosY==395){
            PosX += 265;
            if(PosX>547)
                PosX=547;
        }else if((IsKeyPressed(KEY_A)||IsKeyPressed(KEY_LEFT)) && PosY==395){
            PosX -= 265;
            if(PosX<17)
                PosX=17;
        }

        //Clicando nos botões.
        if((PosY==451 && IsKeyPressed(KEY_ENTER)) || IsKeyPressed(KEY_BACKSPACE)){
            CloseWindow();
            Menu();
        }else if(PosX==17 && IsKeyPressed(KEY_ENTER)){
            /*
                code
                        */
        }else if(PosX==282 && IsKeyPressed(KEY_ENTER)){
            /*
                code
                        */
        }else if(PosX==547 && IsKeyPressed(KEY_ENTER)){
            /*
                code
                        */
        }

        BeginDrawing();
            ClearBackground(BLACK);

            if(pts>=5400){
                DrawTextureV(tipetree, (Vector2) {0,0},WHITE);
            }else if(pts>=2700){
                DrawTextureV(tipetwo, (Vector2) {0,0},WHITE);
            }else{
                DrawTextureV(tipeone, (Vector2) {0,0},WHITE);
            }
            
            DrawRectangleRoundedLines((Rectangle){PosX, PosY, 235, 30},0.3,5,5,LIGHTGRAY);
        EndDrawing();
        
        UpdateMusicStream(music);

    }


    UnloadMusicStream(music);
    UnloadTexture(tipeone);

    CloseWindow();
}
