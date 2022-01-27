#ifndef Ritmo
#define Ritmo

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