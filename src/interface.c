#include <interface.h>
#include <raylib.h>

// desenha um texto centralizado horizontalmente na tela
static void desenhar_texto_centralizado(const char *texto, int y, int tamanho, Color cor){
    int largura = MeasureText(texto, tamanho);
    DrawText(texto, (GetScreenWidth() - largura) / 2, y, tamanho, cor);
}

void interface_tela_inicial(){
    // título do jogo no topo
    desenhar_texto_centralizado("BEJEWELED", 60, 64, WHITE);

    // três botões retangulares e coloridos, um abaixo do outro
    DrawRectangle(MENU_BOTAO_X, MENU_BOTAO_JOGAR_Y, MENU_BOTAO_LARGURA, MENU_BOTAO_ALTURA, PINK);
    DrawRectangle(MENU_BOTAO_X, MENU_BOTAO_INSTRUCOES_Y, MENU_BOTAO_LARGURA, MENU_BOTAO_ALTURA, SKYBLUE);
    DrawRectangle(MENU_BOTAO_X, MENU_BOTAO_CONFIGURACOES_Y, MENU_BOTAO_LARGURA, MENU_BOTAO_ALTURA, PURPLE);

    // contorno branco nos botões
    DrawRectangleLines(MENU_BOTAO_X, MENU_BOTAO_JOGAR_Y, MENU_BOTAO_LARGURA, MENU_BOTAO_ALTURA, WHITE);
    DrawRectangleLines(MENU_BOTAO_X, MENU_BOTAO_INSTRUCOES_Y, MENU_BOTAO_LARGURA, MENU_BOTAO_ALTURA, WHITE);
    DrawRectangleLines(MENU_BOTAO_X, MENU_BOTAO_CONFIGURACOES_Y, MENU_BOTAO_LARGURA, MENU_BOTAO_ALTURA, WHITE);

    // textos centralizados dentro de cada botão
    DrawText("Jogar", MENU_BOTAO_X + (MENU_BOTAO_LARGURA - MeasureText("Jogar", 20)) / 2,
             MENU_BOTAO_JOGAR_Y + 12, 20, WHITE);

    DrawText("Instrucoes", MENU_BOTAO_X + (MENU_BOTAO_LARGURA - MeasureText("Instrucoes", 20)) / 2,
             MENU_BOTAO_INSTRUCOES_Y + 12, 20, WHITE);

    DrawText("Configuracoes", MENU_BOTAO_X + (MENU_BOTAO_LARGURA - MeasureText("Configuracoes", 20)) / 2,
             MENU_BOTAO_CONFIGURACOES_Y + 12, 20, WHITE);

    // rodapé no canto inferior da tela (nome dos alunos em vermelho)
    DrawText("Alunos: Emilly Karoline, Hiorrana Nicolly e Iago de França", 120, GetScreenHeight() - 20, 20, DARKGRAY);
}

void interface_tela_instrucoes(){
    // título da tela de instruções
    desenhar_texto_centralizado("COMO JOGAR?", 40, 40, MAGENTA);

    // instruções do jogo
    desenhar_texto_centralizado("Troque os doces para formar trios de doces do mesmo tipo", 120, 20,DARKPURPLE  );
    desenhar_texto_centralizado("Cada doce vale 5 pontos", 150, 20, DARKPURPLE  );
    desenhar_texto_centralizado("Dica: destaca uma combinacao possivel (custa 10 pontos)", 180, 20, DARKPURPLE  );
    desenhar_texto_centralizado("Desfazer: desfaz apenas a ultima jogada(custa 10 pontos)", 210, 20, DARKPURPLE  );
    desenhar_texto_centralizado("O jogo encerra automaticamente quando nao ha mais jogadas possiveis", 240, 20, DARKPURPLE  );
    desenhar_texto_centralizado("P pausa o jogo | ESPACO volta ao menu inicial", 270, 20, WHITE  );
}

void interface_tela_configuracoes(){
    // tela em branco (apenas aberta) - 
}

void interface_tela_final(int pontuacaoFinal){
    desenhar_texto_centralizado("FIM DE JOGO", 100, 56, WHITE);

    const char *textoPontuacao = TextFormat("Pontuacao final: %i", pontuacaoFinal);
    desenhar_texto_centralizado(textoPontuacao, 220, 32, WHITE);

    desenhar_texto_centralizado("Pressione ESPAÇO para voltar ao menu", 300, 20, WHITE);
}
