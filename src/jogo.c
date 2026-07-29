#include <jogo.h>
#include <raylib.h>
#include <render.h>

//parte q emilly tinha colocado no loop principal, só passei pra cá pra ficar mais separado pq essa parte ainda vai aumentar
void jogo_atualizar(){
    int lin, col;
    if(obter_gema_clicada(&lin, &col)){
        // Exibe no console qual gema foi clicada.
        TraceLog(LOG_INFO, TextFormat("Gema clicada -> linha: %i coluna: %i", lin, col)); //só pra teste
    }
}

//aqui colocar a função de jogo encerrado

