#ifndef MENU_H
#define MENU_H
#include "raylib.h"
#include "constantes.h"
#include <stdio.h>
#include <stdbool.h>

static const float largura_botao = 80, altura_botao = 50;
Rectangle btnBounds = { 800/2.0f - largura_botao/2.0f, 450/2.0f - altura_botao/2.0f, largura_botao, altura_botao };
int estado_botao = 0;
bool ativar_botao = false;
static Vector2 posicao_mouse = { 0.0f, 0.0f };

void Logica_menu(void);
void Desenho_menu(void);

#endif // menu_h