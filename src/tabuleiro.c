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

void tabuleiro_detectar_combinacoes(Gema tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO],
                                    bool marcado[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO]){

    for(int i=0; i<TAMANHO_TABULEIRO; i++){
        for(int j=0; j<TAMANHO_TABULEIRO; j++){
            marcado[i][j] = false;
        }
    }

    for(int i=0; i<TAMANHO_TABULEIRO; i++){
        int inicioSequencia = 0;

        for(int j=1; j<=TAMANHO_TABULEIRO; j++){
            bool sequenciaContinua = (j < TAMANHO_TABULEIRO) &&
                gema_igual(tabuleiro[i][j], tabuleiro[i][inicioSequencia]);

            if(!sequenciaContinua){
                int tamanhoSequencia = j - inicioSequencia;

                if(tamanhoSequencia >= 3){
                    for(int k=inicioSequencia; k<j; k++){
                        marcado[i][k] = true;
                    }
                }
                inicioSequencia = j;
            }
        }
    }

    for(int j=0; j<TAMANHO_TABULEIRO; j++){
        int inicioSequencia = 0;

        for(int i=1; i<=TAMANHO_TABULEIRO; i++){
            bool sequenciaContinua = (i < TAMANHO_TABULEIRO) &&
                gema_igual(tabuleiro[i][j], tabuleiro[inicioSequencia][j]);

            if(!sequenciaContinua){
                int tamanhoSequencia = i - inicioSequencia;

                if(tamanhoSequencia >= 3){
                    for(int k=inicioSequencia; k<i; k++){
                        marcado[k][j] = true;
                    }
                }
                inicioSequencia = i;
            }
        }
    }
}

bool tabuleiro_tem_combinacao(bool marcado[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO]){
    for(int i=0; i<TAMANHO_TABULEIRO; i++){
        for(int j=0; j<TAMANHO_TABULEIRO; j++){
            if(marcado[i][j]) return true;
        }
    }
    return false;
}