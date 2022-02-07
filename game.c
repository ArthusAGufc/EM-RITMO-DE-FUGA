#include "raylib.h"
#include <stdio.h>
#include <stdlib.h>
#include "jogo.h"

typedef struct BandidoEhelicoptero
{
    Vector2 posicao; // denominar posiçao no canvas
    Texture2D personagem; // Carregar imagem
    Rectangle srect[7]; // Deve ser maior que o numero de sprites, o bandido tem 6

    int frames; 
    int frameAtual;
   
    int largurapersonagem; // Largura de uma sprite
    int alturapersonagem; // Altura de uma sprite

    int personagemEixoX;  // posiçao no canvas x
    int personagemEixoY;  // posiçao no canvas y

    long double tempo; // inicio da contagem, sempre 0
    float tempoParaAnimar; // velocidede de movimento da sprite

    int tempodepulo; // apenas para Bandido
 
}Spriteperson;

typedef struct Policial
{
    Vector2 Polpocicao[60];
    Texture2D Polpersonagem;
    Rectangle Polsrect[60];

    int larguraPolicial;
    int alturaPolicial;

    int PolicialEixoX;  
    int PolicialEixoY;  

    
    int Poltamanho;
    int Polvelocidade;

}Policial;

void animar_spritesperson(Spriteperson* b)
{
    b->tempo += GetFrameTime();

    if(b->tempo > b->tempoParaAnimar){
        b->frameAtual++;
        b->tempo = 0;
    }

    if(b->frameAtual >= b->frames){
        b->frameAtual = 0;
    }
}

void Game()
{
    // Inicio da parte grafica
    //--------------------------------------------------------------------------------------

    const int larguraTela = 800; // medida da tela 
    const int alturaTela = 450; // medida da tela

    InitWindow(larguraTela, alturaTela, "Ritmo De Fuga");
    SetTargetFPS(60);

    //Música
    Music music = LoadMusicStream("Imagens/Music/battleThemeA.MP3");

    arquivo = fopen("HighScore.txt","r");
    fscanf(arquivo,"%d",&highscore);
    fclose(arquivo);

    // Posicao, movimentos, texturas
    //--------------------------------------------------------------------------------------
    Texture2D background = LoadTexture("Imagens/Maps/Mapa.png");
    Texture2D background2 = LoadTexture("Imagens/Maps/Mapa.png");

    int PosXBackGround = 0;
    int PosXBackGround2 = 800;

    
    Spriteperson Skin1;
    
    //modificando as 'skin' do personagem
    if (selecao == 1)
        Skin1.personagem = LoadTexture("Imagens/Sprites/Skin1.png");
    
    if (selecao == 2)
        Skin1.personagem = LoadTexture("Imagens/Sprites/Skin3.png");
    
    if (selecao == 3)
        Skin1.personagem = LoadTexture("Imagens/Sprites/Skin2.png");
    
    //Bandido
    Skin1.frames = 6;
    Skin1.frameAtual = 0;
    
    Skin1.largurapersonagem = 46;
    Skin1.alturapersonagem = 57;

    Skin1.posicao = (Vector2) {Skin1.personagemEixoX = 100, Skin1.personagemEixoY = 370};

    for(int i = 0; i < Skin1.frames; i++)
    {
        Skin1.srect[i] = (Rectangle) { Skin1.largurapersonagem * i, 0, Skin1.largurapersonagem, Skin1.alturapersonagem };
    }

    Skin1.tempo = 0;
    Skin1.tempoParaAnimar = 0.09;

    Skin1.tempodepulo = 0; //Variável que irá contar o tempo no ar que o personagem está

    //Policial
    Policial Policial1;
    Policial1.Polpersonagem = LoadTexture("Imagens/Sprites/Carro.png");

    Policial1.Poltamanho =  sizeof(Policial1.Polsrect)/sizeof(Policial1.Polsrect[0]);

    Policial1.larguraPolicial = 139;
    Policial1.alturaPolicial = 47;

    Policial1.Polpocicao[0] = (Vector2) {Policial1.PolicialEixoX = 200, Policial1.PolicialEixoY = 380};
    Policial1.Polsrect[0] = (Rectangle) {(rand()%3)*Policial1.larguraPolicial, 0, Policial1.larguraPolicial, Policial1.alturaPolicial};

    for(int i = 0; i < Policial1.Poltamanho; i++){
        Policial1.Polpocicao[i] = (Vector2) { Policial1.Polpocicao[i-1].x + rand() % larguraTela + larguraTela/2, Policial1.PolicialEixoY = 380  };

        Policial1.Polsrect[i] = (Rectangle) { (rand()%3)*Policial1.larguraPolicial, 0, Policial1.larguraPolicial, Policial1.alturaPolicial };
    }
    Policial1.Polvelocidade = 7;

    bool Pular = false;
    bool FimDeJogo = false;

    // Lopp para rodar game
    //--------------------------------------------------------------------------------------

     while(!WindowShouldClose())
    {

        SetMusicVolume(music, volume);
        PlayMusicStream(music);

        if (IsKeyReleased(KEY_BACKSPACE)){
            score = 0;
            CloseWindow();
            Menu();   
        }
        
        //Quando a tecla de pulo for pressionada
        if(IsKeyPressed(KEY_SPACE) || IsKeyPressed(KEY_UP))
            Pular = true;

        if(!FimDeJogo)
        {
            animar_spritesperson(&Skin1);
    
            // Pular o personagem
            if(Pular)
            {
                Skin1.tempodepulo += 3; // Aumentando o tempo no ar
                
                //Definindo um limite para o personagem subir
                if(Skin1.tempodepulo < 90 ) 
                    Skin1.posicao.y -= 5;
                
                //Quando atinge 90 o personagem desce 
                else
                    Skin1.posicao.y += 5;
            }
            
            //Quando tempo atingir o limite desativa o bool Pular e define o tempo de pulo para 0
            if(Skin1.tempodepulo >= 172.5)
            {
                Skin1.tempodepulo = 0;
                Pular = false;
            }

            for( int i = 0; i < Policial1.Poltamanho; i++ )
            {
                if(Policial1.Polpocicao[i].x < -Policial1.larguraPolicial*2)
                {
                    continue;
                }
                Policial1.Polpocicao[i].x -= Policial1.Polvelocidade;
            }

            for( int i = 0; i < Policial1.Poltamanho; i++)
            {
                if( Policial1.Polpocicao[i].x > 0 && Policial1.Polpocicao[i].x < larguraTela )
                {
                    if(CheckCollisionRecs( (Rectangle) { Skin1.posicao.x, Skin1.posicao.y, Skin1.largurapersonagem, Skin1.alturapersonagem },
                                           (Rectangle) { Policial1.Polpocicao[i].x, Policial1.Polpocicao[i].y, Policial1.larguraPolicial, Policial1.alturaPolicial} ))
                    {
                        FimDeJogo = true;
                    }         
                }
            }
        }
        
        //FUNDO DO JOGO
        if(!FimDeJogo){
            PosXBackGround = PosXBackGround - 2;
            PosXBackGround2 = PosXBackGround2 - 2;
        }

        if (PosXBackGround <= -800) PosXBackGround = 800;
        if (PosXBackGround2 <= -800) PosXBackGround2 = 800; 
        
        if(!FimDeJogo){
            score++;
            if(score > highscore){
                highscore = score;
                arquivo = fopen("HighScore.txt","w");
                if(arquivo== NULL){
                    printf("\nO Arquivo Não Pode Ser Aberto");
                }else{
                    fprintf(arquivo,"%d",highscore);
                    fclose(arquivo);
                }
            }
        }

        // Carregar na tela
        //----------------------------------------------------------------------------------
        BeginDrawing(); 

            ClearBackground(GetColor(0x052c46ff));

            DrawTexture(background,PosXBackGround,0, WHITE);     
            DrawTexture(background2,PosXBackGround2,0, WHITE);  
                
            DrawTextureRec(Skin1.personagem, Skin1.srect[Skin1.frameAtual], Skin1.posicao, WHITE); // carregar skin na tela

            for( int i = 0; i < Policial1.Poltamanho; i++ )
            {
                if(Policial1.Polpocicao[i].x > -Policial1.larguraPolicial && Policial1.Polpocicao[i].x < larguraTela)
                {
                    DrawTextureRec(Policial1.Polpersonagem, Policial1.Polsrect[i], Policial1.Polpocicao[i], WHITE);
                }
            }

            DrawFPS(10,0);
            DrawText(TextFormat("Score: %d",score),280,0,28,WHITE);
            DrawText(TextFormat("HighScore: %d",highscore),520,0,28,WHITE);

            if(FimDeJogo) {
                DrawText("CAPTURADO!", 200, 200, 60, LIGHTGRAY);
                StopMusicStream(music);
                DrawText ("APERTE 'ENTER' PARA JOGAR NOVAMENTE",200,250,18,LIGHTGRAY);
                if ( IsKeyReleased(KEY_ENTER) ){
                    score = 0;
                    CloseWindow();
                    Game();
                }

            }
        EndDrawing();

        UpdateMusicStream(music);
    }

     // Desligar da tela
    //--------------------------------------------------------------------------------------
    UnloadMusicStream(music);
    UnloadTexture(Skin1.personagem);
    UnloadTexture(Policial1.Polpersonagem);
    
    CloseWindow();

    Menu();

}
