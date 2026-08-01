#ifndef RENDER_H
#define RENDER_H

#include <tabuleiro.h>

#define TAMANHO_CELULA 40

void renderizar_fundo(bool desfocado);

void renderizar(Gema tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO]);
bool obter_gema_clicada(int *linha,int *coluna);

#endif