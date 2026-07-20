#ifndef GEMA_H
#define GEMA_H

#include "raylib.h"
#include <stdbool.h>

/* 
 1) ENUM DOS TIPOS DE GEMA
  Cada valor representa um tipo distinto de gema. Manter GEMA_VAZIA
   como -1 é para uma célula "sem gema" na matriz (logo após uma remoção).
 NUM_TIPOS_GEMA fica sempre igual à quantidade de tipos "de verdade", vou mandar as gemas
 que pensei, mas se achar que são mts seis basta remover as que vem antes de NUM_TIPOS_GEMA 
 que tudo teoricamente se ajusta sozinho.
 */
typedef enum {
    GEMA_VERMELHA = 0,
    GEMA_AZUL=1,
    GEMA_MULTICOR=2,
    GEMA_AMARELA=3,
    GEMA_ROXA=4,
    GEMA_LARANJA=5,
    NUM_TIPOS_GEMA,      /* = 6, quantidade de tipos válidos */
    GEMA_VAZIA = -1
} TipoGema;

/* 
 2) STRUCT DA GEMA
  
  Por enquanto só guarda o tipo, mas deixei como struct para adicionar outras coisas 
  dentro dps e não muda a assinatura de nenhuma função.
 */
typedef struct {
    TipoGema tipo;
} Gema;

/* 
 3) GERENCIAMENTO DE TEXTURAS (as imagens ficam em assets/images)
  Carrega todas as texturas de gema uma única vez (chamar no início do programa, depois de InitWindow). */
void gema_carregarTexturas(void);

/* Libera todas as texturas (chamar antes de CloseWindow). */
void gema_descarregarTexturas(void);

/* Retorna a textura associada a um tipo de gema. */
Texture2D gema_obterTextura(TipoGema tipo);

/* 4) CRIAÇÃO / SORTEIO DE GEMAS  */

/* Cria uma gema de um tipo específico. */
Gema gema_criar(TipoGema tipo);

/* Sorteia um tipo válido  */
TipoGema gema_sortearTipo(void);

/* Cria uma gema com tipo sorteado aleatoriamente. */
Gema gema_criarAleatoria(void);


/* Compara duas gemas (considera vazia como diferente de qualquer coisa). */
bool gema_igual(Gema a, Gema b);

/* Desenha a gema em um retângulo de "tamanho" x "tamanho" pixels,
 * com o canto superior esquerdo em (x, y). */
void gema_desenhar(Gema g, int x, int y, int tamanho);

#endif /* GEMA_H */