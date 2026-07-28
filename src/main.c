#include <raylib.h>
#include <time.h>
#include <gema.h>
#include <tabuleiro.h>
#include <render.h>

int main(){
    // inicializar a janela
    const int largura = 800;
    const int altura = 400;

    //sempre primeiro a largura e depois a altura
    InitWindow(largura, altura,"Bejeweled-c");
    SetTargetFPS(60);

    // pra funcionamento da função gema_sortearTipo
    SetRandomSeed((unsigned int)time(NULL));

    //
    gema_carregarTexturas();

    Gema tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO];

    tabuleiro_inicializar(tabuleiro); 
    //tabuleiro_imprimir(tabuleiro); 

    bool jogoEncerrado = false;

    if(!tabuleiro_existe_jogada_possivel(tabuleiro)){
        jogoEncerrado = true;
    }

    //parte gráfica do raylib
    while(!WindowShouldClose() && !jogoEncerrado){
        //lógica principal
        BeginDrawing();
        ClearBackground(WHITE);

        renderizar(tabuleiro);
        //DrawText("Deu certo!",230, 210, 30, PURPLE);

        EndDrawing();
    }

    gema_descarregarTexturas();
    CloseWindow();

    return 0;
}