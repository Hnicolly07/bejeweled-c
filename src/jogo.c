// CONTROLA TUDO DO JOGO, FAZENDO AS CHAMADAS FUNCIONAIS DOS MÓDULOS INDIVIDUAIS
#include <jogo.h>
#include <raylib.h>
#include <render.h>

int pontuacao = 0;

Gema tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO];
int linha1 = -1; //um valor que não está entre os possiveis indices pra linha e coluna
int coluna1 = -1;

void jogo_inicializar(){
    pontuacao = 0;
    tabuleiro_inicializar(tabuleiro);
}

//parte q emilly tinha colocado no loop principal, só passei pra cá pra ficar mais separado pq essa parte ainda vai aumentar
void jogo_atualizar(){
    int lin, col;
        
        if(obter_gema_clicada(&lin, &col)){
            // Exibe no console qual gema foi clicada.
            //TraceLog(LOG_INFO, TextFormat("Gema clicada -> linha: %i coluna: %i", lin, col)); //só pra teste
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
                        pontuacao += 10;
                        tabuleiro_remover_combinacoes(tabuleiro);
                        efeito_cascata(tabuleiro);
                        tabuleiro_detectar_combinacoes(tabuleiro, marcado);
                    }while(tabuleiro_tem_combinacao(marcado));
                }

                linha1 = -1; //reiniciar os valores 
                coluna1 = -1;
            }
            
        }
}

void jogo_renderizar(){
    renderizar(tabuleiro);
    DrawText(TextFormat("SCORE: %d", pontuacao),20,20,30,WHITE);
}

//aqui colocar a função de jogo encerrado
bool jogo_encerrar(){
     //ainda vai ser atualizada em jogo qd houver uma condição maior de parada do jogo, por enquanto ta aqui
    if(!tabuleiro_existe_jogada_possivel(tabuleiro)){ 
        return true;
    }

    return false;
}

