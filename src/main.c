//ESSE ARQUIVO DEVE APENAS CONTROLAR O FLUXO DO PROGRAMA
// NÃO DEVE CONTROLAR TABULEIRO, GEMAS, NADA, APENAS CHAMAR
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

    jogo_inicializar();

    //isso aq vai ficar rodando até q a janela seja fechada
    while(!WindowShouldClose() && !jogo_encerrar()){
        //lógica principal
        jogo_atualizar();
        
        BeginDrawing();
        //vai mudar dps pro papel de parede
        ClearBackground(PINK); //n precisa ligar pra essa cor é só q o branco tava agoniando

        jogo_renderizar();
        EndDrawing();
    }
    
    // e descarregar no final
    gema_descarregar_texturas();
    //fechar a janela
    CloseWindow();

    return 0;
}