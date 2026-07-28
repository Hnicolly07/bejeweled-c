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

bool obterGemaClicada(int *linha,int *coluna){
    // Obtém a posição atual do mouse em pixels.
    Vector2 mouse = GetMousePosition();
    const int tamanhoCelula=40;
    const int largura=TAMANHO_TABULEIRO*tamanhoCelula;
    const int altura=TAMANHO_TABULEIRO*tamanhoCelula;
    const int offsetX=(GetScreenWidth()-largura)/2;
    const int offsetY=(GetScreenHeight()-altura)/2;
    // Verifica se houve clique esquerdo.
    if(!IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) return false;
    // Verifica se o clique ocorreu dentro do tabuleiro.
    if(mouse.x<offsetX||mouse.y<offsetY||mouse.x>=offsetX+largura||mouse.y>=offsetY+altura) return false;
    // Converte x em coluna e y em linha.
    int c=(mouse.x-offsetX)/tamanhoCelula;
    int l=(mouse.y-offsetY)/tamanhoCelula;
    // Valida posição calculada.
    if(l<0||l>=TAMANHO_TABULEIRO||c<0||c>=TAMANHO_TABULEIRO) return false;
    // Armazena linha e coluna selecionadas.
    *linha=l; *coluna=c;
    return true;
}
