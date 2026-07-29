#include <raylib.h>
#include <time.h>
#include <gema.h>
#include <tabuleiro.h>
#include <render.h>
#include <jogo.h>

int main(){
    // inicializar a janela
    const int largura = 800;
    const int altura = 400;

    //sempre primeiro a largura e depois a altura
    InitWindow(largura, altura,"Bejeweled-c");
    SetTargetFPS(60);

    // pra funcionamento da função gema_sortear_tipo
    SetRandomSeed((unsigned int)time(NULL));

    //sempre tem que carregar as texturas
    gema_carregar_texturas();

    Gema tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO];

    tabuleiro_inicializar(tabuleiro);

    bool jogoEncerrado = false;
    //ainda vai ser atualizada em jogo qd houver uma condição maior de parada do jogo, por enquanto ta aqui
    if(!tabuleiro_existe_jogada_possivel(tabuleiro)){ 
        jogoEncerrado = true;
    }

    //isso aq vai ficar rodando até q a janela seja fechada
    while(!WindowShouldClose() && !jogoEncerrado){
        jogo_atualizar(); //coloquei o tracelog em jogo.c
        
        //lógica principal
        BeginDrawing();
        //vai mudar dps pro papel de parede
        ClearBackground(PINK); //n precisa ligar pra essa cor é só q o branco tava agoniando

        renderizar(tabuleiro);
        EndDrawing();
    }
    
    // e descarregar no final
    gema_descarregar_texturas();
    //fechar a janela
    CloseWindow();

    return 0;
}