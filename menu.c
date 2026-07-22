#include "menu.h"

void Logica_menu(void) {
    /*Lógica da tela de menu*/
    posicao_mouse = GetMousePosition();
        ativar_botao = false;

        // Check button state
        if (CheckCollisionPointRec(posicao_mouse, btnBounds))
        {
            if (IsMouseButtonDown(MOUSE_BUTTON_LEFT)) estado_botao = 2;
            else estado_botao = 1;

            if (IsMouseButtonReleased(MOUSE_BUTTON_LEFT)) ativar_botao = true;
        }
        else estado_botao = 0;

        if (ativar_botao)
        {
            printf("esta funcionando");
            

            // TODO: Any desired action
        }
}
void Desenho_menu(void) {
    /*Desenho da tela de Menu*/
    DrawRectangle(btnBounds.x, btnBounds.y, largura_botao, altura_botao, BLUE);
        

}