#ifndef RENDER_H
#define RENDER_H

#include <tabuleiro.h>

#define TAMANHO_CELULA 40

void renderizar_fundo(bool desfocado);

//pra descarregar o fundo no final
void renderizar_fundo_descarregar();

// posições/tamanhos fixos dos botões (lado direito da tela, onde sobra espaço)
#define BOTAO_X 580
#define BOTAO_LARGURA 190
#define BOTAO_ALTURA 45
#define BOTAO_DICA_Y 60
#define BOTAO_DESFAZER_Y 120
#define BOTAO_ENCERRAR_X 20
#define BOTAO_ENCERRAR_Y 320

// desenha os botões de Dica e Desfazer na tela
void renderizar_botoes_jogo();

// desenha o destaque (contorno) nas duas células da dica
void renderizar_dica(int linha1, int coluna1, int linha2, int coluna2);

//desenhar contorno na gema selecionada
void renderizar_selecao(int linha, int coluna);

//animação de gemas trocadas
void renderizar_animacao_troca(int linha1, int coluna1, int linha2, int coluna2, float progresso);

void renderizar(Gema tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO]);
bool obter_gema_clicada(int *linha,int *coluna);

#endif