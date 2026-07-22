//ESSE ARQUIVO SÓ PODERÁ SER TESTADO OU ALTERADO DEPOIS QUE A LÓGICA DE FUNCIONAMENTO DO JOGO ESTIVER FEITA

#ifndef AUDIO_H
#define AUDIO_H

#include "raylib.h"

/*Carregar os sons tanto da musica quanto ao som das gemas quebrando*/
void Carregar_sons(void);
/* Usar essa função quando ouver eliminação de gemas*/
void Tocar_som_gemas_quebrando(bool gemas_quebram);
/*Descarregar os ons tanto da musica quanto ao som das gemas quebrando*/
void Descarregar_sons_AudioDevice(void);
/*Opção para ativar ou desativar a música do jogo*/
void Ativar_ou_Desativar_musica(bool pausar);
/*Não acho necessário criar funções pros que já tem de tocar a música e colocar a música no 
loop principal, mas coloquei só pra garantir.*/
void Atualizar_musica_no_jogo(void);
void Tocar_musica_jogo(void);

#endif