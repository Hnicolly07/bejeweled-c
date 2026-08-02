#include "raylib.h"
#include "audio.h"
#include <stdio.h>
#include <stdbool.h>

/*Definição da música a ser tocada e o efeito sonoro a ser tocado quado as gemas quebram*/
static Music musica_jogo;
static Sound som_gemas_quebram;

void carregar_sons(void){
    musica_jogo = LoadMusicStream("assets/sounds/musica_bejeweled.mp3");
    som_gemas_quebram = LoadSound("assets/sounds/gemas_quebrando.mp3");
}

void tocar_som_gemas_quebrando(bool gemas_quebram) {
    if (gemas_quebram == true) {
        PlaySound(som_gemas_quebram);
    }
}

void descarregar_sons(void) {
    UnloadMusicStream(musica_jogo);
    UnloadSound(som_gemas_quebram);
    CloseAudioDevice();
}

void ativar_ou_desativar_musica(bool pausar) {
    if(pausar == true) {
        StopMusicStream(musica_jogo);
    }
    else {
        PlayMusicStream(musica_jogo);
    }
}

void atualizar_musica_no_jogo(void) {
    UpdateMusicStream(musica_jogo);
}
void tocar_musica_jogo(void){
    PlayMusicStream(musica_jogo);
}
    