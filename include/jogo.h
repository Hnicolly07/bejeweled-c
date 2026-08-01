#ifndef JOGO_H
#define JOGO_H

#include <tabuleiro.h>

//qual tela o jogo ta no momento, aí a gente faz um switch
typedef enum {
    ESTADO_TELA_INICIAL, //nome do jogo, integrantes, botão de jogar
    ESTADO_INSTRUCOES,   //explicação de pontuação e controles
    ESTADO_CONFIGURACOES, //tela de configurações
    ESTADO_JOGANDO,      //partida em andamento (td q a gente já fez)
    ESTADO_PAUSADO,      //jogo pausado
    ESTADO_GAME_OVER     //placar final, opção de reiniciar
} EstadoJogo;

void jogo_inicializar();

void jogo_atualizar();

void jogo_atualizar_telas();

void jogo_renderizar();

bool jogo_encerrar();

EstadoJogo obter_estado(); //retornando o Estadojogo do typedef de telas

void jogo_definir_estado(EstadoJogo novoEstado);

void jogo_reiniciar();

int jogo_obter_pontuacao();

#endif