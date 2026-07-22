#include <stdio.h>
#include <tabuleiro.h>


void tabuleiro_inicializar(Gema tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO]){

    for(int i=0; i<TAMANHO_TABULEIRO; i++){
        for(int j=0; j<TAMANHO_TABULEIRO;j++){
            tabuleiro[i][j] = gema_criarAleatoria();
        }
    }
}

//só pra testar se tá funcionando
void tabuleiro_imprimir(Gema tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO]){
    for(int i=0; i<TAMANHO_TABULEIRO; i++){
        for(int j=0; j<TAMANHO_TABULEIRO;j++){
            printf("%d ", tabuleiro[i][j].tipo);
        }
        printf("\n");
    }
}