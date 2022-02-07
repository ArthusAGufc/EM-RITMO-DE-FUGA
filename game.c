#include "raylib.h"
#include <stdio.h>
#include <stdlib.h>
#include "jogo.h"

typedef struct Bandido
{
    Vector2 posicao; // denominar posiçao no canvas
    Texture2D personagem; // Carregar imagem
    Rectangle srect[7]; // Deve ser maior que o numero de sprites, o bandido tem 6

    int frames; // imagem inicial da spriteshet
    int frameAtual; // imagem atual mostrada na spriteshet
   
    int largurapersonagem; // Largura de uma sprite
    int alturapersonagem; // Altura de uma sprite

    int personagemEixoX;  // posiçao no canvas x
    int personagemEixoY;  // posiçao no canvas y

    long double tempo; // inicio da contagem, sempre 0
    float tempoParaAnimar; // velocidede de movimento da sprite

    int tempodepulo; // "gravidade do jogo"
 
}Spriteperson;

typedef struct Policial
{
    Vector2 Polpocicao[60]; // denominar posiçao no canvas
    Texture2D Polpersonagem; // Carregar imagem
    Rectangle Polsrect[60];

    int larguraPolicial;
    int alturaPolicial;

    int PolicialEixoX;  
    int PolicialEixoY;  

    
    int Poltamanho;
    int Polvelocidade;

}Policial;

void animar_spritesperson(Spriteperson* b) // funcao para fazer efeito de movimento da sprite
{
    b->tempo += GetFrameTime(); // setagem das variaves da struct Spriteperson

    if(b->tempo > b->tempoParaAnimar){ // essas codicionais servem para determinar a velocidade do movimento da sprite e a ordem de exibiçao
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

    //Pontuação
    arquivo = fopen("HighScore.txt","r"); //Abrir arquivo com a pontuação máxima
    fscanf(arquivo,"%d",&highscore); //Lê a pontuação máxima
    fclose(arquivo);

    // Posicao, movimentos, texturas
    //--------------------------------------------------------------------------------------
    Texture2D background = LoadTexture("Imagens/Maps/Mapa.png"); //Plano de fundo
    Texture2D background2 = LoadTexture("Imagens/Maps/Mapa.png"); //Cópia do plano de fundo

    int PosXBackGround = 0; //Posição do Plano de fundo 1
    int PosXBackGround2 = 800; //Posição do Plano de fundo 2

    
    Spriteperson Skin1; // Criacao de struct 
    
    //modificando as 'skin' do personagem
    if (selecao == 1)
        Skin1.personagem = LoadTexture("Imagens/Sprites/Skin1.png");
    
    if (selecao == 2)
        Skin1.personagem = LoadTexture("Imagens/Sprites/Skin3.png");
    
    if (selecao == 3)
        Skin1.personagem = LoadTexture("Imagens/Sprites/Skin2.png");
    
    //Bandido (Spritepersom)  atribuicao de valores as variaveis da struct
    Skin1.frames = 6;
    Skin1.frameAtual = 0;
    
    Skin1.largurapersonagem = 46;
    Skin1.alturapersonagem = 57;

    Skin1.posicao = (Vector2) {Skin1.personagemEixoX = 100, Skin1.personagemEixoY = 370}; // posicao no canvas

    for(int i = 0; i < Skin1.frames; i++) // laço para determinar o tamanho do retangulo ao redor da sprite
    {
        Skin1.srect[i] = (Rectangle) { Skin1.largurapersonagem * i, 0, Skin1.largurapersonagem, Skin1.alturapersonagem };
    }

    Skin1.tempo = 0;
    Skin1.tempoParaAnimar = 0.09;

    Skin1.tempodepulo = 0; //Variável que irá contar o tempo no ar que o personagem está

    //Policial (Policial)  atribuicao de valores as variaveis da struct
    Policial Policial1;
    Policial1.Polpersonagem = LoadTexture("Imagens/Sprites/Carro.png");

    Policial1.Poltamanho =  sizeof(Policial1.Polsrect)/sizeof(Policial1.Polsrect[0]);

    Policial1.larguraPolicial = 139;
    Policial1.alturaPolicial = 47;

    Policial1.Polpocicao[0] = (Vector2) {Policial1.PolicialEixoX = 200, Policial1.PolicialEixoY = 380};
    Policial1.Polsrect[0] = (Rectangle) {(rand()%3)*Policial1.larguraPolicial, 0, Policial1.larguraPolicial, Policial1.alturaPolicial};

    for(int i = 0; i < Policial1.Poltamanho; i++){ // laco for responsavel por movimentar no eixo x em direçao ao boneco
        Policial1.Polpocicao[i] = (Vector2) { Policial1.Polpocicao[i-1].x + rand() % larguraTela + larguraTela/2, Policial1.PolicialEixoY = 380  };
        // determinar o tamanho do retangulo ao redor da sprite
        Policial1.Polsrect[i] = (Rectangle) { (rand()%3)*Policial1.larguraPolicial, 0, Policial1.larguraPolicial, Policial1.alturaPolicial };
    }
    Policial1.Polvelocidade = 7; // velocidade de deslocamento do inimigo 

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
            // Esse laço determina que apos sair do canvas, as sprites de inimigos retornem do outro lado
            for( int i = 0; i < Policial1.Poltamanho; i++ )
            {
                if(Policial1.Polpocicao[i].x < -Policial1.larguraPolicial*2)
                {
                    continue;
                }
                Policial1.Polpocicao[i].x -= Policial1.Polvelocidade;
            }
            // Laco para identificar a colisao entre os retangulos que sercam a sprite do bandido e do carro
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
            //Diminuir 2 da posição do plano de fundo enquanto não houver colisão
            PosXBackGround = PosXBackGround - 2; 
            PosXBackGround2 = PosXBackGround2 - 2;
        }

        //Quando a imagem ultrapassar o inicio da janela, inserir novamente no final da tela
        if (PosXBackGround <= -800) PosXBackGround = 800;
        if (PosXBackGround2 <= -800) PosXBackGround2 = 800; 
        
        if(!FimDeJogo){
            score++;//Adiciona mais 1 a pontuação enquanto não houver colisão
            if(score > highscore){ //Caso a pontuação seja maior que a pontuação máxima
                highscore = score;//A pontuação máxima será igual a pontuação atual
                //Salva a pontuação máxima em um arquivo
                arquivo = fopen("HighScore.txt","w");
                if(arquivo== NULL){
                    printf("\nO Arquivo Não Pode Ser Aberto");
                }else{
                    fprintf(arquivo,"%d",highscore);
                    fclose(arquivo);
                }
            }
        }

        // Carregar na tela ( exibir )
        //----------------------------------------------------------------------------------
        BeginDrawing(); 

            ClearBackground(GetColor(0x052c46ff)); // cor de fundo(Azul claro)

            DrawTexture(background,PosXBackGround,0, WHITE);    
            DrawTexture(background2,PosXBackGround2,0, WHITE);  
                
            DrawTextureRec(Skin1.personagem, Skin1.srect[Skin1.frameAtual], Skin1.posicao, WHITE); // carregar skin na tela

            for( int i = 0; i < Policial1.Poltamanho; i++ ) // carregar skin na tela
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
