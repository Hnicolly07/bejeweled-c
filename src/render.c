#include <render.h>

void renderizar(Gema tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO]){
    //tamanho de cada quadradinho
    const int tamanhoCelula = 40;

    //largura é o TAMANHO_TABULEIRO que é 8 vezes o tamanho de cada quadradinho
    const int larguraTabuleiro = TAMANHO_TABULEIRO * tamanhoCelula;
    //altura a msm coisa
    const int alturaTabuleiro  = TAMANHO_TABULEIRO * tamanhoCelula;

    const int offsetX = (GetScreenWidth()  - larguraTabuleiro) / 2;
    const int offsetY = (GetScreenHeight() - alturaTabuleiro) / 2;

    for(int i=0;i<TAMANHO_TABULEIRO;i++){
        for(int j=0;j<TAMANHO_TABULEIRO;j++){
            int x = offsetX + j * tamanhoCelula;
            int y = offsetY + i * tamanhoCelula;

            //parte de desenhar o tabuleiro mesmo
            DrawRectangleLines(x, y, tamanhoCelula, tamanhoCelula, GRAY);
            //desenha as gemas dentro do tabuleiro, função de emilly
            gema_desenhar(tabuleiro[i][j], x, y, tamanhoCelula);
        }
    }
}