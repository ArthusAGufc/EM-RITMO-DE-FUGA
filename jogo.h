#ifndef Ritmo //Se não existir uma definição chamada Ritmo, está definição será criada
#define Ritmo //Caso a definição Ritmo já exista

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

#endif //Fim da Definição
