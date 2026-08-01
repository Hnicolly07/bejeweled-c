#ifndef TABULEIRO_H
#define TABULEIRO_H

#include <gema.h>

#define TAMANHO_TABULEIRO 8

// função pra inicializar o tabuleiro 8x8 do tipo Gema que emilly criou
void tabuleiro_inicializar(Gema tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO]);

//função pra encontrar as combinações tanto hotizontais tanto verticais
void tabuleiro_detectar_combinacoes(Gema tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO], bool marcado[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO]);

bool troca_gera_trio(Gema tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO],int linha1,int coluna1,int linha2,int coluna2);

void trocar_gemas(Gema tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO], int linha1, int coluna1, int linha2, int coluna2);

bool possui_trio_local(Gema tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO], int linha, int coluna);

// remove as gemas que fazem parte de trios detectados no tabuleiro
void tabuleiro_remover_combinacoes(Gema tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO]);

bool tabuleiro_tem_combinacao(bool marcado[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO]);

bool tabuleiro_existe_jogada_possivel(Gema tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO]);

bool gemas_vizinhas(int linha1, int coluna1, int linha2, int coluna2);

void efeito_cascata(Gema tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO]);

#endif 