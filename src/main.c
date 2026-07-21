#include <raylib.h>
#include <time.h>
#include <gema.h>
#include <tabuleiro.h>

int main(){
    // inicializar a janela
    const int largura = 800;
    const int altura = 400;

    //sempre primeiro a largura e depois a altura
    InitWindow(largura, altura,"Bejeweled-c");
    SetTargetFPS(60);

    // pra funcionamento da função gema_sortearTipo
    SetRandomSeed((unsigned int)time(NULL));

    Gema tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO];

    tabuleiro_inicializar(tabuleiro); 
    tabuleiro_imprimir(tabuleiro); 

    //parte gráfica do raylib
    while(!WindowShouldClose()){
        //lógica principal
        BeginDrawing();
        ClearBackground(WHITE);

        DrawText("Deu certo!",230, 210, 30, PURPLE);

        EndDrawing();
    }

    CloseWindow();

    return 0;
}