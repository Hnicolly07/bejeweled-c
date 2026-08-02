//ESSE ARQUIVO DEVE APENAS CONTROLAR O FLUXO DO PROGRAMA
// NÃO DEVE CONTROLAR TABULEIRO, GEMAS, NADA, APENAS CHAMAR
#include <raylib.h>
#include <time.h>
#include <gema.h>
#include <tabuleiro.h>
#include <jogo.h>
#include <audio.h>
#include <render.h>

int main(){
    // inicializar a janela
    const int largura = 800;
    const int altura = 400;

    //sempre primeiro a largura e depois a altura
    InitWindow(largura, altura,"Bejeweled-c");
    SetTargetFPS(60);

    // pra funcionamento da função gema_sortear_tipo
    SetRandomSeed((unsigned int)time(NULL));
    //sempre tem que carregartd no inicio
    gema_carregar_texturas();

    //inicializar o audio
    InitAudioDevice();
    carregar_sons();
    tocar_musica_jogo();

    jogo_inicializar();

    //isso aq vai ficar rodando até q a janela seja fechada
    while(!WindowShouldClose()){
        //lógica principal (fluxo por estado/tela)
        jogo_atualizar_telas();

        //tem q ser cgamada aq pra manter a msc tocando
        atualizar_musica_no_jogo();
        
        BeginDrawing();
        //vai mudar dps pro papel de parede
        ClearBackground(PINK); //n precisa ligar pra essa cor é só q o branco tava agoniando

        jogo_renderizar();
        EndDrawing();
    }
    
    // e descarregar no final
    gema_descarregar_texturas();
    renderizar_fundo_descarregar();
    descarregar_sons();

    //fechar a janela
    CloseWindow();

    return 0;
}