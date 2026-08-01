#include <stdio.h>
#include <tabuleiro.h>
#include <stdlib.h>


void tabuleiro_inicializar(Gema tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO]){
    //faça todo esse processo
    do{
        for(int i=0; i<TAMANHO_TABULEIRO; i++){
            for(int j=0; j<TAMANHO_TABULEIRO;j++){
                //gere pra posição [i][j] uma gema aleatória
                do{
                    tabuleiro[i][j] = gema_criar_aleatoria();
                } //enquanto as gemas nos quadradinhos vizinhos formarem uma combinação
                while((j >= 2 && gema_igual(tabuleiro[i][j], tabuleiro[i][j-1]) && gema_igual(tabuleiro[i][j], tabuleiro[i][j-2]))
                    || (i >= 2 && gema_igual(tabuleiro[i][j], tabuleiro[i-1][j]) && gema_igual(tabuleiro[i][j], tabuleiro[i-2][j])));
            }
        }
    }while(!tabuleiro_existe_jogada_possivel(tabuleiro)); //enquanto não houverem jogadas possiveis
}

void tabuleiro_detectar_combinacoes(Gema tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO],bool marcado[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO]){

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

void tabuleiro_remover_combinacoes(Gema tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO]){
    bool marcado[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO] = {false};

    tabuleiro_detectar_combinacoes(tabuleiro, marcado);

    if(!tabuleiro_tem_combinacao(marcado)){
        return;
    }

    for(int i = 0; i < TAMANHO_TABULEIRO; i++){
        for(int j = 0; j < TAMANHO_TABULEIRO; j++){
            if(marcado[i][j]){
                tabuleiro[i][j].tipo = GEMA_VAZIA;
            }
        }
    }
}

//Retorna true se o array de marcação contém pelo menos uma gema combinada
bool tabuleiro_tem_combinacao(bool marcado[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO]){
    for(int i=0; i<TAMANHO_TABULEIRO; i++){
        for(int j=0; j<TAMANHO_TABULEIRO; j++){
            if(marcado[i][j]) return true;
        }
    }
    return false;
}
 
// Retorna true quando a posição (linha,coluna) faz parte de uma combinação horizontal ou vertical
bool possui_trio_local(Gema tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO], int linha, int coluna){
    int cont = 1;
    //pra esquerda
    for(int j = coluna - 1; j >= 0 && gema_igual(tabuleiro[linha][j], tabuleiro[linha][coluna]); j--){
        cont++;
    } 
    //pra direita
    for(int j = coluna + 1; j < TAMANHO_TABULEIRO && gema_igual(tabuleiro[linha][j], tabuleiro[linha][coluna]); j++){
        cont++;
    }

    if(cont >= 3){
        return true;
    }

    cont = 1;
    
    //pra cima
    for(int i = linha - 1; i >= 0 && gema_igual(tabuleiro[i][coluna], tabuleiro[linha][coluna]); i--){
        cont++;
    } 
    //pra baixo
    for(int i = linha + 1; i < TAMANHO_TABULEIRO && gema_igual(tabuleiro[i][coluna], tabuleiro[linha][coluna]); i++){
        cont++;
    } 

    return cont >= 3;
}

void trocar_gemas(Gema tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO], int linha1, int coluna1, int linha2, int coluna2){
    Gema temp = tabuleiro[linha1][coluna1];  //gema auxiliar pra trocar as gemas vai receber a primeira
    tabuleiro[linha1][coluna1] = tabuleiro[linha2][coluna2]; // primeira recebe a segunda
    tabuleiro[linha2][coluna2] = temp; // segunda recebe a auxiliar q ta guardando a primeira antes da troca

}

bool troca_gera_trio(Gema tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO],int linha1,int coluna1,int linha2,int coluna2){
    trocar_gemas(tabuleiro,linha1,coluna1,linha2,coluna2); //troca as gemas

    bool geraTrio;
    // testa pra ver se tem trio
    if(possui_trio_local(tabuleiro, linha1, coluna1) || possui_trio_local(tabuleiro, linha2, coluna2)){
        geraTrio = true;
    } else{
        geraTrio = false;
    }

    trocar_gemas(tabuleiro,linha1,coluna1,linha2,coluna2); //destroca 

    return geraTrio;
}
 
bool tabuleiro_existe_jogada_possivel(Gema tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO]){
    for(int i = 0; i < TAMANHO_TABULEIRO; i++){
        for(int j = 0; j < TAMANHO_TABULEIRO; j++){

            // testa troca com a gema da direita
            if(j + 1 < TAMANHO_TABULEIRO && troca_gera_trio(tabuleiro, i, j, i, j + 1)){
                return true;
            }

            // testa troca com a gema de baixo
            if(i + 1 < TAMANHO_TABULEIRO && troca_gera_trio(tabuleiro, i, j, i + 1, j)){
                return true;
            }
        }
    }
    return false;
}

bool gemas_vizinhas(int linha1, int coluna1, int linha2, int coluna2){
    if(abs(linha1 - linha2) + abs(coluna1 - coluna2) == 1){
        return true;
    }

    return false;
}

void efeito_cascata(Gema tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO]){
    for(int i = TAMANHO_TABULEIRO-1; i>=0; i--){
        for(int j = 0; j<TAMANHO_TABULEIRO; j++){
                if(tabuleiro[i][j].tipo == GEMA_VAZIA){
                    int atual = i-1; // utilizando essa variavel pra n ficar alterando diretamente o valor de i
                    while(atual >= 0 && tabuleiro[atual][j].tipo == GEMA_VAZIA){ // se não for a primeira linha pq n dá pra olhar acima
                        atual--;
                    } 
                
                    if(atual >= 0){
                        tabuleiro[i][j] = tabuleiro[atual][j];
                        tabuleiro[atual][j].tipo = GEMA_VAZIA;
                    } else{
                        tabuleiro[i][j] = gema_criar_aleatoria(); //caso tiver percorrido tudo e n encontrou gema pra descer, cria uma nova
                    }
                } 
        }
    }
}