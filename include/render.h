#ifndef RENDER_H
#define RENDER_H

#include <tabuleiro.h>
#include <gema.h>

void renderizar(Gema tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO]);
bool obterGemaClicada(int *linha,int *coluna);

#endif