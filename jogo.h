#ifndef Ritmo
#define Ritmo

float volume = 0.15;
int PosX = 400; 

//Arquivo
FILE *arquivo;

//Pontuação
int score = 0, selecao = 1;
int highscore = 0;

void Menu();
void Game();
void Windows(){
    const int screenWidth = 800;
    const int screenHeight = 500;
    InitWindow(screenWidth, screenHeight, "Ritmo De Fuga");
}
void Credits();
void Shop();
void History();
void Settings();

#endif
