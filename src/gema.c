#include "gema.h"
#include <stdio.h>

/* Array estático com uma textura por tipo de gema. 
para que só funções dentro de gema.c enxergam
essa variável — o resto do programa só acessa via gema_obterTextura. */
static Texture2D texturasGemas[NUM_TIPOS_GEMA];
static bool texturasCarregadas = false;

/* dando textura as gemas A ORDEM AQUI TEM QUE BATER com a ordem
 do enum TipoGema em gema.h . Tem que ajustar as imagens pdf
 que a gente quer aki,  as gemas que a gente colocar em assets imagem os nomes
 dos arquivos é so substituir */
static const char *caminhosTexturas[NUM_TIPOS_GEMA] = {
    "assets/images/gema_vermelha.png",  /* GEMA_VERMELHA */
    "assets/images/gema_azul.png",      /* GEMA_AZUL     */
    "assets/images/gema_milticor.png",     /* GEMA_MULTICOR    */
    "assets/images/gema_amarela.png",   /* GEMA_AMARELA  */
    "assets/images/gema_roxa.png",      /* GEMA_ROXA     */
    "assets/images/gema_laranja.png"    /* GEMA_LARANJA  */
};

void gema_carregarTexturas(void)
{
    if (texturasCarregadas) return; /* evita carregar duas vezes */

    for (int i = 0; i < NUM_TIPOS_GEMA; i++) {
        texturasGemas[i] = LoadTexture(caminhosTexturas[i]);

        /* LoadTexture n retorna erro, se o arquivo não existir, texture.id fica 0. 
        Vale checar em modo debug. */
        if (texturasGemas[i].id == 0) {
            TraceLog(LOG_WARNING, "Falha ao carregar textura: %s",
                      caminhosTexturas[i]);
        }
    }
    texturasCarregadas = true;
}

void gema_descarregarTexturas(void)
{
    if (!texturasCarregadas) return;

    for (int i = 0; i < NUM_TIPOS_GEMA; i++) {
        UnloadTexture(texturasGemas[i]);
    }
    texturasCarregadas = false;
}

Texture2D gema_obterTextura(TipoGema tipo)
{
    /* tipo == GEMA_VAZIA (-1) nunca deveria chegar aqui */
    return texturasGemas[tipo];
}

Gema gema_criar(TipoGema tipo)
{
    Gema g;
    g.tipo = tipo;
    return g;
}

TipoGema gema_sortearTipo(void)
{
    /* GetRandomValue é da própria raylib pelo q eu vi, mas n consigo testar ainda, min e max INCLUSIVOS.
      No main.c: chamem SetRandomSeed((unsigned int)time(NULL)) uma
      única vez, logo após InitWindow, senão o jogo vai sortear
      a mesma sequência de gemas a cada execução. */
    return (TipoGema)GetRandomValue(0, NUM_TIPOS_GEMA - 1);
}

Gema gema_criarAleatoria(void)
{
    return gema_criar(gema_sortearTipo());
}

bool gema_igual(Gema a, Gema b)
{
    if (a.tipo == GEMA_VAZIA || b.tipo == GEMA_VAZIA) return false;
    return a.tipo == b.tipo;
}

void gema_desenhar(Gema g, int x, int y, int tamanho)
{
    if (g.tipo == GEMA_VAZIA) return; /* nada a desenhar */

    Texture2D tex = gema_obterTextura(g.tipo);

    /* Escala a textura original pra caber
     no quadrado "tamanho x tamanho" da célula da matriz. */
    Rectangle origem  = { 0, 0, (float)tex.width, (float)tex.height };
    Rectangle destino = { (float)x, (float)y, (float)tamanho, (float)tamanho };
    Vector2 origemRotacao = { 0, 0 };

    DrawTexturePro(tex, origem, destino, origemRotacao, 0.0f, WHITE);
}