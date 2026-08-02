#include <render.h>
#include <stdbool.h>
#include <math.h>

static Texture2D texturaFundo;
static Texture2D texturaFundoDesfoque;
static bool fundosCarregados = false;

void renderizar_fundo(bool desfocado){
    //carrega os fundos na primeira vez que for desenhar
    if (!fundosCarregados) {
        texturaFundo = LoadTexture("assets/images/PlanoDeFundo.png");
        texturaFundoDesfoque = LoadTexture("assets/images/PlanoDeFundoDesfoque.png");
        fundosCarregados = true;
    }

    /* um if/else Escolhe qual textura será usada, dependendo do valor de desfocado
    */
        Texture2D tex;
        if (desfocado) {
            tex = texturaFundoDesfoque;
        } else {
            tex = texturaFundo;
        }
            if (tex.id == 0) return;

    //estica a imagem (32x144) pra cobrir a janela inteira,função do raylib.
    DrawTexturePro(tex,
        (Rectangle){ 0, 0, (float)tex.width, (float)tex.height },
        (Rectangle){ 0, 0, (float)GetScreenWidth(), (float)GetScreenHeight() },
        (Vector2){ 0, 0 }, 0.0f, WHITE);
}

// libera as 2 texturas de fundo carregadas em renderizar_fundo 
void renderizar_fundo_descarregar(){
    if (!fundosCarregados) return;

    UnloadTexture(texturaFundo);
    UnloadTexture(texturaFundoDesfoque);
    fundosCarregados = false;
}

//eu acredito que a gente poderia manter essas variaveis em uma só já que é o msm tamanho, vcs podem perguntar pro professor pf
//largura é o TAMANHO_TABULEIRO que é 8 vezes o tamanho de cada quadradinho
    const int larguraTabuleiro = TAMANHO_TABULEIRO * TAMANHO_CELULA;
    //altura a msm coisa
    const int alturaTabuleiro  = TAMANHO_TABULEIRO * TAMANHO_CELULA;

void renderizar(Gema tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO]){
    //pra centralizar o tabuleiro
    //qd a gente usa  afunção Draw (pra desenhar o tabuleiro) tem q colocar as posições pra começar
    //qd a gente calcula o offset pegando a largura da tela e diminuindo a largura q o tabuleiro ocupa e dividindo por 2 a gente consegue
    // colocar nosso tabuleiro pra começar a ser desenhado no meio
    const int offsetX = (GetScreenWidth()  - larguraTabuleiro)/2;
    //o mesmo com a altura
    const int offsetY = (GetScreenHeight() - alturaTabuleiro)/2;

    for(int i=0;i<TAMANHO_TABULEIRO;i++){
        for(int j=0;j<TAMANHO_TABULEIRO;j++){
            //aq a gente vai atualizando a posição de desenho
            //o offset q a gente calculou ta no primeiro quadradinho aí passa pro proximo vezes o tamanho de cada quadradinho
            int x = offsetX + j * TAMANHO_CELULA;
            int y = offsetY + i * TAMANHO_CELULA;

            //parte de desenhar o tabuleiro mesmo
            DrawRectangleLines(x, y, TAMANHO_CELULA, TAMANHO_CELULA, GRAY);
            //desenha as gemas dentro do tabuleiro, função de emilly
            gema_desenhar(tabuleiro[i][j], x, y, TAMANHO_CELULA);
        }
    }
}

void renderizar_botoes_jogo(){
    // botão de dica: retângulo com texto e custo
    DrawRectangle(BOTAO_X, BOTAO_DICA_Y, BOTAO_LARGURA, BOTAO_ALTURA, (Color){ 50, 50, 100, 220 });
    DrawRectangleLines(BOTAO_X, BOTAO_DICA_Y, BOTAO_LARGURA, BOTAO_ALTURA, RAYWHITE);
    DrawText("Dica  (-10)", BOTAO_X + 15, BOTAO_DICA_Y + 12, 18, WHITE);

    // botão de desfazer: retângulo com texto e custo
    DrawRectangle(BOTAO_X, BOTAO_DESFAZER_Y, BOTAO_LARGURA, BOTAO_ALTURA, (Color){ 100, 50, 50, 220 });
    DrawRectangleLines(BOTAO_X, BOTAO_DESFAZER_Y, BOTAO_LARGURA, BOTAO_ALTURA, RAYWHITE);
    DrawText("Desfazer (-10)", BOTAO_X + 15, BOTAO_DESFAZER_Y + 12, 18, WHITE);

    //botão encerrar
    DrawRectangle(BOTAO_ENCERRAR_X, BOTAO_ENCERRAR_Y, BOTAO_LARGURA, BOTAO_ALTURA, (Color){ 140, 40, 130, 220 });
    DrawRectangleLines(BOTAO_ENCERRAR_X, BOTAO_ENCERRAR_Y, BOTAO_LARGURA, BOTAO_ALTURA, RAYWHITE);
    DrawText("Encerrar Jogo", BOTAO_ENCERRAR_X + 15, BOTAO_ENCERRAR_Y + 12, 18, WHITE);
}

void renderizar_dica(int linha1, int coluna1, int linha2, int coluna2){
    // desenha um contorno vermelho nas duas células sugeridas pela dica
    const int offsetX = (GetScreenWidth()  - larguraTabuleiro)/2;
    const int offsetY = (GetScreenHeight() - alturaTabuleiro)/2;

    int x1 = offsetX + coluna1 * TAMANHO_CELULA;
    int y1 = offsetY + linha1 * TAMANHO_CELULA;
    DrawRectangleLinesEx((Rectangle){ x1, y1, TAMANHO_CELULA, TAMANHO_CELULA }, 3, RED);

    int x2 = offsetX + coluna2 * TAMANHO_CELULA;
    int y2 = offsetY + linha2 * TAMANHO_CELULA;
    DrawRectangleLinesEx((Rectangle){ x2, y2, TAMANHO_CELULA, TAMANHO_CELULA }, 3, RED);
}

bool obter_gema_clicada(int *linha,int *coluna){
    //movi pra cá pq se n houver clique ele já retorna false direto sem criar as variaveis de posição e os offsets
    // Verifica se houve clique esquerdo.
    if(!IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) return false;
    
    // Obtém a posição atual do mouse em pixels.
    Vector2 mouse = GetMousePosition();
    const int offsetX = (GetScreenWidth()  - larguraTabuleiro)/2;
    const int offsetY = (GetScreenHeight() - alturaTabuleiro)/2;
    
   
    // Verifica se o clique ocorreu dentro do tabuleiro.
    if(mouse.x<offsetX||mouse.y<offsetY||mouse.x>=offsetX+larguraTabuleiro||mouse.y>=offsetY+alturaTabuleiro) return false;
    // Converte x em coluna e y em linha.
    int c=(mouse.x-offsetX)/TAMANHO_CELULA; //componente x do mouse menos o local onde o tabuleiro começa a ser desenhado/tamanho de cada celula
    int l=(mouse.y-offsetY)/TAMANHO_CELULA; //mesma coisa
    // Valida posição calculada.
    if(l<0||l>=TAMANHO_TABULEIRO||c<0||c>=TAMANHO_TABULEIRO) return false;
    // Armazena linha e coluna selecionadas.
    *linha=l; *coluna=c;
    return true;
}

void renderizar_selecao(int linha, int coluna){
    const int offsetX = (GetScreenWidth()  - larguraTabuleiro)/2;
    const int offsetY = (GetScreenHeight() - alturaTabuleiro)/2;

    int x = offsetX + coluna * TAMANHO_CELULA;
    int y = offsetY + linha * TAMANHO_CELULA;

    // sinf(GetTime()) oscila entre -1 e 1; aqui normalizamos pra ficar entre 0 e 1
    float pulso = (sinf((float)GetTime() * 6.0f) + 1.0f) / 2.0f;
    float margem = 2.0f + pulso * 4.0f; // contorno varia de 2 a 6 pixels pra fora da célula

    Rectangle retangulo = {
        x - margem, y - margem,
        TAMANHO_CELULA + margem * 2, TAMANHO_CELULA + margem * 2
    };
    DrawRectangleLinesEx(retangulo, 3, YELLOW);
}

void renderizar_animacao_troca(int linha1, int coluna1, int linha2, int coluna2, float progresso){
    const int offsetX = (GetScreenWidth()  - larguraTabuleiro)/2;
    const int offsetY = (GetScreenHeight() - alturaTabuleiro)/2;

    if(progresso < 0.0f) progresso = 0.0f;
    if(progresso > 1.0f) progresso = 1.0f;

    unsigned char alfa = (unsigned char)(255 * (1.0f - progresso));
    Color cor = (Color){ 255, 255, 255, alfa };

    int x1 = offsetX + coluna1 * TAMANHO_CELULA;
    int y1 = offsetY + linha1 * TAMANHO_CELULA;
    DrawRectangleLinesEx((Rectangle){ x1, y1, TAMANHO_CELULA, TAMANHO_CELULA }, 4, cor);

    int x2 = offsetX + coluna2 * TAMANHO_CELULA;
    int y2 = offsetY + linha2 * TAMANHO_CELULA;
    DrawRectangleLinesEx((Rectangle){ x2, y2, TAMANHO_CELULA, TAMANHO_CELULA }, 4, cor);
}
