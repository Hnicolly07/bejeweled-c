// CONTROLA TUDO DO JOGO, FAZENDO AS CHAMADAS FUNCIONAIS DOS MÓDULOS INDIVIDUAIS
#include <jogo.h>
#include <raylib.h>
#include <render.h>
#include <interface.h>

Gema tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO];
int linha1 = -1; //um valor que não está entre os possiveis indices pra linha e coluna
int coluna1 = -1;

int pontuacao = 0;

EstadoJogo estadoAtual = ESTADO_TELA_INICIAL; //primeira tela lá do enum, ainda n foi definida em interface

void jogo_inicializar(){
    tabuleiro_inicializar(tabuleiro);
}

//parte q emilly tinha colocado no loop principal, só passei pra cá pra ficar mais separado pq essa parte ainda vai aumentar
void jogo_atualizar(){
    //se apertar pra pausar
    if(IsKeyPressed(KEY_P)){
        estadoAtual = ESTADO_PAUSADO;
        return;
    }

    int lin, col;
        
        if(obter_gema_clicada(&lin, &col)){
            if(linha1 == -1){
                linha1 = lin;
                coluna1 = col;
            } else{
                int linha2 = lin;
                int coluna2 = col;

                if(gemas_vizinhas(linha1,coluna1,linha2,coluna2) && troca_gera_trio(tabuleiro,linha1,coluna1,linha2,coluna2)){
                    trocar_gemas(tabuleiro,linha1, coluna1,linha2,coluna2);
                    bool marcado[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO]; 
                    
                    do{
                        for(int i = 0; i < TAMANHO_TABULEIRO; i++){
                            for(int j = 0; j < TAMANHO_TABULEIRO; j++){
                                if(marcado[i][j]){
                                    pontuacao += 5; //adicionar +5 no score pra cara posição marcada com true (q são as q forma combinação)
                                } 
                            }
                        }

                        tabuleiro_remover_combinacoes(tabuleiro);
                        efeito_cascata(tabuleiro);
                        tabuleiro_detectar_combinacoes(tabuleiro, marcado);
                    }while(tabuleiro_tem_combinacao(marcado));
                }

                linha1 = -1; //reiniciar os valores 
                coluna1 = -1;
            }
            
        }

        if(!tabuleiro_existe_jogada_possivel(tabuleiro)){
            estadoAtual = ESTADO_GAME_OVER; //se n tiver mais jogada possivel, atualiza pra poder desenhar a tela final
        }
}

void jogo_atualizar_telas(){
    switch(estadoAtual){
        case ESTADO_TELA_INICIAL:
        case ESTADO_INSTRUCOES:
        case ESTADO_CONFIGURACOES:
        case ESTADO_GAME_OVER:
            break;

        case ESTADO_JOGANDO:
            jogo_atualizar();
            break;

        case ESTADO_PAUSADO:
            if(IsKeyPressed(KEY_P)){ //se tiver oausado e clicar dnv pra despausar
                estadoAtual = ESTADO_JOGANDO; 
            }
            break;
    }
}

void jogo_renderizar(){
    switch(estadoAtual){
        case ESTADO_TELA_INICIAL:
            interface_tela_inicial();
            break;

        case ESTADO_INSTRUCOES:
            interface_tela_instrucoes();
            break;

        case ESTADO_CONFIGURACOES:
            interface_tela_configuracoes();
            break;

        case ESTADO_JOGANDO:
            renderizar(tabuleiro);
            break;

        case ESTADO_PAUSADO:
            renderizar(tabuleiro);
            DrawText("PAUSADO - aperte P para continuar", 20, 20, 20, WHITE); //ainda atualizar
            break;

        case ESTADO_GAME_OVER:
            interface_tela_final(pontuacao);
            break;
    }
    //renderizar(tabuleiro);
}
    

//aqui colocar a função de jogo encerrado
bool jogo_encerrar(){
     //ainda vai ser atualizada em jogo qd houver uma condição maior de parada do jogo, por enquanto ta aqui
    if(!tabuleiro_existe_jogada_possivel(tabuleiro)){ 
        return true;
    }
    return false;
}

EstadoJogo obter_estado(){
    return estadoAtual;
}

void jogo_definir_estado(EstadoJogo novoEstado){
    estadoAtual = novoEstado;
}

void jogo_reiniciar(){
    tabuleiro_inicializar(tabuleiro);
    pontuacao = 0;
    linha1 = -1;
    coluna1 = -1;
    estadoAtual = ESTADO_JOGANDO;
}

int jogo_obter_pontuacao(){
    return pontuacao;
}

