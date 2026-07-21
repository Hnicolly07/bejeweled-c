#include "raylib.h"
#include "sound.h"
#include <stdio.h>
#include <stdbool.h>

musica_jogo = LoadMusicStream("assets/sounds/musica_bejeweled.mp3");
som_gemas_quebram = LoadSound("assets/sounds/gemas_quebrando.mp3");

void Tocar_som_gemas_quebrando(bool gemas_quebram) {
    if (gemas_quebram == true) {
        PlaySound(som_gemas_quebram);
    };


}
    /* O caminho colocado do arquivo é provisório*/
    
    