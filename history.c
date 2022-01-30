#include "raylib.h"
#include "jogo.h"


void History(){

    Windows();

    Music music = LoadMusicStream("Imagens/Music/Theme.wav");
    
    while (!WindowShouldClose()){
        SetMusicVolume(music, volume);
        PlayMusicStream(music);


        UpdateMusicStream(music);
    }

    UnloadMusicStream(music);
}
