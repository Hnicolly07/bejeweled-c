#ifndef INTERFACE_H
#define INTERFACE_H

#include <stdbool.h>

/* BOTÕES DA TELA INICIAL */
#define MENU_BOTAO_LARGURA 200
#define MENU_BOTAO_ALTURA 45
#define MENU_BOTAO_X ((800 - MENU_BOTAO_LARGURA) / 2) /* centralizado na largura */
#define MENU_BOTAO_JOGAR_Y 130
#define MENU_BOTAO_INSTRUCOES_Y 195
#define MENU_BOTAO_CONFIGURACOES_Y 260
#define CONFIG_BOTAO_SOM_Y 160

void interface_tela_inicial();   

void interface_tela_instrucoes();

void interface_tela_configuracoes(bool somaAtivo); 

void interface_tela_final(int pontuacaoFinal, int recorde);

#endif