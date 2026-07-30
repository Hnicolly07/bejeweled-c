#ifndef TABULEIRO_H
#define TABULEIRO_H

#include <gema.h>

#define TAMANHO_TABULEIRO 8

// função pra inicializar o tabuleiro 8x8 do tipo Gema que emilly criou
void tabuleiro_inicializar(Gema tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO]);

//função pra encontrar as combinações tanto hotizontais tanto verticais
void tabuleiro_detectar_combinacoes(Gema tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO], bool marcado[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO]);

// remove as gemas que fazem parte de trios detectados no tabuleiro
void tabuleiro_remover_combinacoes(Gema tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO], bool marcado[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO]);

bool tabuleiro_tem_combinacao(bool marcado[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO]);

/*
 * Verifica se existe pelo menos uma jogada possível.
 * A função testa trocas entre gemas vizinhas e verifica
 * se alguma delas gera uma combinação de 3 ou mais.
 */
bool tabuleiro_existe_jogada_possivel(
    Gema tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO]);

#endif 