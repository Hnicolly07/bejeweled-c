#ifndef TABULEIRO_H
#define TABULEIRO_H

#include <gema.h>

#define TAMANHO_TABULEIRO 8

// função pra inicializar o tabuleiro 8x8 do tipo Gema que emilly criou
void tabuleiro_inicializar(Gema tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO]);

// só pra testar se tá tudo certo
//void tabuleiro_imprimir(Gema tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO]);

//função pra encontrar as combinações tanto hotizontais tanto verticais
void tabuleiro_detectar_combinacoes(Gema tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO],
                                    bool marcado[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO]);

bool tabuleiro_tem_combinacao(bool marcado[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO]);

#endif