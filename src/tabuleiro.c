#include <stdio.h>
#include <tabuleiro.h>


void tabuleiro_inicializar(Gema tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO]){

    /*
     * Gera o tabuleiro evitando trios iniciais.
     * Antes de aceitar uma gema sorteada verificamos
     * se ela completaria 3 iguais na horizontal ou vertical.
     */
    for(int i=0; i<TAMANHO_TABULEIRO; i++){
        for(int j=0; j<TAMANHO_TABULEIRO;j++){

            do{
                tabuleiro[i][j] = gema_criarAleatoria();
            }
            while(
                (j >= 2 &&
                 gema_igual(tabuleiro[i][j], tabuleiro[i][j-1]) &&
                 gema_igual(tabuleiro[i][j], tabuleiro[i][j-2]))
                ||
                (i >= 2 &&
                 gema_igual(tabuleiro[i][j], tabuleiro[i-1][j]) &&
                 gema_igual(tabuleiro[i][j], tabuleiro[i-2][j]))
            );
        }
    }

    /*
     * Caso o tabuleiro fique sem nenhuma jogada possível,
     * ele é gerado novamente.
     */
    while(!tabuleiro_existe_jogada_possivel(tabuleiro)){
        for(int i=0; i<TAMANHO_TABULEIRO; i++){
            for(int j=0; j<TAMANHO_TABULEIRO;j++){

                do{
                    tabuleiro[i][j] = gema_criarAleatoria();
                }
                while(
                    (j >= 2 &&
                    gema_igual(tabuleiro[i][j], tabuleiro[i][j-1]) &&
                    gema_igual(tabuleiro[i][j], tabuleiro[i][j-2]))
                    ||
                    (i >= 2 &&
                    gema_igual(tabuleiro[i][j], tabuleiro[i-1][j]) &&
                    gema_igual(tabuleiro[i][j], tabuleiro[i-2][j]))
                );
            }
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
/*
 * Retorna true quando a posição (linha,coluna)
 * faz parte de uma combinação horizontal ou vertical.
 */
static bool possui_trio_local(
    Gema tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO],
    int linha,
    int coluna)
{
    TipoGema tipo = tabuleiro[linha][coluna].tipo;

    int cont = 1;

    for(int j = coluna - 1; j >= 0 &&
        tabuleiro[linha][j].tipo == tipo; j--) cont++;

    for(int j = coluna + 1; j < TAMANHO_TABULEIRO &&
        tabuleiro[linha][j].tipo == tipo; j++) cont++;

    if(cont >= 3) return true;

    cont = 1;

    for(int i = linha - 1; i >= 0 &&
        tabuleiro[i][coluna].tipo == tipo; i--) cont++;

    for(int i = linha + 1; i < TAMANHO_TABULEIRO &&
        tabuleiro[i][coluna].tipo == tipo; i++) cont++;

    return cont >= 3;
}

bool tabuleiro_existe_jogada_possivel(
    Gema tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO])
{
    for(int i = 0; i < TAMANHO_TABULEIRO; i++){
        for(int j = 0; j < TAMANHO_TABULEIRO; j++){

            if(j + 1 < TAMANHO_TABULEIRO){
                Gema temp = tabuleiro[i][j];
                tabuleiro[i][j] = tabuleiro[i][j + 1];
                tabuleiro[i][j + 1] = temp;

                bool geraTrio =
                    possui_trio_local(tabuleiro, i, j) ||
                    possui_trio_local(tabuleiro, i, j + 1);

                temp = tabuleiro[i][j];
                tabuleiro[i][j] = tabuleiro[i][j + 1];
                tabuleiro[i][j + 1] = temp;

                if(geraTrio) return true;
            }

            if(i + 1 < TAMANHO_TABULEIRO){
                Gema temp = tabuleiro[i][j];
                tabuleiro[i][j] = tabuleiro[i + 1][j];
                tabuleiro[i + 1][j] = temp;

                bool geraTrio =
                    possui_trio_local(tabuleiro, i, j) ||
                    possui_trio_local(tabuleiro, i + 1, j);

                temp = tabuleiro[i][j];
                tabuleiro[i][j] = tabuleiro[i + 1][j];
                tabuleiro[i + 1][j] = temp;

                if(geraTrio) return true;
            }
        }
    }

    return false;
}
