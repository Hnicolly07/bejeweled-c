#include "raylib.h"
/*Definição da música a ser tocada e o efeito sonoro a ser tocado quado as gemas quebram*/
Music musica_jogo;
Sound som_gemas_quebram;
/* Usar essa função quando ouver eliminação de gemas*/
void Tocar_som_gemas_quebrando(bool gemas_quebram);