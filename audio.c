#include "raylib.h"
#include "audio.h"
#include <stdio.h>
#include <stdbool.h>

void Carregar_sons_AudioDevice(void){
    musica_jogo = LoadMusicStream("assets/sounds/musica_bejeweled.mp3");
    som_gemas_quebram = LoadSound("assets/sounds/gemas_quebrando.mp3");
}

void Tocar_som_gemas_quebrando(bool gemas_quebram) {
    if (gemas_quebram == true) {
        PlaySound(som_gemas_quebram);
    }
}

void Descarregar_sons_AudioDevice(void) {
    CloseAudioDevice();
    UnloadMusicStream(musica_jogo);
    UnloadSound(som_gemas_quebram);
}
void Ativar_ou_Desativar_musica(bool pausar) {
    if(pausar == true) {
        StopMusicStream(musica_jogo);
    }
    else {
        PlayMusicStream(musica_jogo);
    }
}

void Atualizar_musica_no_jogo(void) {
    UpdateMusicStream(musica_jogo);
}
void Tocar_musica_jogo(void){
    PlayMusicStream(musica_jogo);
}
    
    
    