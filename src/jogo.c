// CONTROLA TUDO DO JOGO, FAZENDO AS CHAMADAS FUNCIONAIS DOS MÓDULOS INDIVIDUAIS
#include <jogo.h>
#include <raylib.h>
#include <render.h>
#include <interface.h>
#include <audio.h>

Gema tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO];
int linha1 = -1, coluna1 = -1; //um valor que não está entre os possiveis indices pra linha e coluna

int pontuacao = 0;
int recorde = 0;

/* ===== ESTADO DAS MECÂNICAS DE DICA E DESFAZER =====*/
// Dica: guarda as células sugeridas e se o destaque está ativo
int dicaLinha1 = -1, dicaColuna1 = -1, dicaLinha2 = -1, dicaColuna2 = -1;
bool dicaAtiva = false;

// Desfazer: guarda uma cópia do tabuleiro antes da última jogada válida
Gema backupTabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO];
int pontuacaoBackup = 0; // pontuação antes da jogada (para restaurar junto)
bool temBackup = false;  // indica se existe um estado salvo para desfazer

// custo fixo aplicado nas duas mecânicas
#define CUSTO_DICA 10
#define CUSTO_DESFAZER 10

EstadoJogo estadoAtual = ESTADO_TELA_INICIAL; //o jogo começa na tela inicial (menu)

static bool somAtivo = true;
bool pausar = false;

#define DURACAO_ANIMACAO_TROCA 0.25 // duração em segundos
int animLinha1 = -1, animColuna1 = -1, animLinha2 = -1, animColuna2 = -1;
double animInicio = 0;
bool animAtiva = false;

void jogo_inicializar(){
    tabuleiro_inicializar(tabuleiro);
}

/* FUNÇÃO DE DICA 
 A dica usa a função já tabuleiro_existe_jogada_possivel(), que
 percorre o tabuleiro testando trocas e devolve true se existe alguma jogada
 que forma trio. Como ela não devolve as coordenadas, uma busca auxiliar local
 (abaixo) encontra e guarda a primeira jogada válida para o renderizador
 destacar. A função existente NÃO é alterada. Custa CUSTO_DICA pontos.*/
static bool encontrar_jogada_para_dica(){
    // percorre o tabuleiro com a mesma lógica, usando troca_gera_trio(),
    // guardando as coordenadas da primeira troca que forma trio
    for(int i = 0; i < TAMANHO_TABULEIRO; i++){
        for(int j = 0; j < TAMANHO_TABULEIRO; j++){
            if(j + 1 < TAMANHO_TABULEIRO && troca_gera_trio(tabuleiro, i, j, i, j + 1)){
                dicaLinha1 = i; dicaColuna1 = j;
                dicaLinha2 = i; dicaColuna2 = j + 1;
                return true;
            }
            if(i + 1 < TAMANHO_TABULEIRO && troca_gera_trio(tabuleiro, i, j, i + 1, j)){
                dicaLinha1 = i; dicaColuna1 = j;
                dicaLinha2 = i + 1; dicaColuna2 = j;
                return true;
            }
        }
    }
    return false;
}

void usar_dica(){
    if(pontuacao < CUSTO_DICA) return; // não deixa usar se não tiver pontos suficientes

    dicaAtiva = false;
    dicaLinha1 = dicaColuna1 = dicaLinha2 = dicaColuna2 = -1;

    // usa a função já existente que percorre o tabuleiro procurando jogada possível
    if(!tabuleiro_existe_jogada_possivel(tabuleiro)){
        return; // não há jogada que forme trio; não gasta pontos
    }

    // encontra as coordenadas da jogada para destacar (sem alterar a função existente)
    if(encontrar_jogada_para_dica()){
        dicaAtiva = true;
        pontuacao -= CUSTO_DICA; // aplica o custo fixo
    }
}

/* FUNÇÃO DE DESFAZER
Restaura o tabuleiro e a pontuação para o estado salvo antes da última
jogada válida (backup), usando tabuleiro_copiar(). Custa CUSTO_DESFAZER pontos.*/ 
void desfazer_jogada(){
    if(!temBackup) return; // não há nada para desfazer
    if(pontuacao < CUSTO_DESFAZER) return; // sem pontos suficientes

    // restaura a matriz do backup (função já existente)
    tabuleiro_copiar(backupTabuleiro, tabuleiro);
    // restaura a pontuação do momento salvo
    pontuacao = pontuacaoBackup - CUSTO_DESFAZER;
    temBackup = false; // o backup foi consumido
    dicaAtiva = false; // limpa a dica, pois o tabuleiro mudou
}

//FUNÇÃO DE SALVAR ESTADO (antes de cada jogada válida)
// Guarda o tabuleiro e a pontuação atuais para permitir o desfazer depois.
void salvar_estado(){
    tabuleiro_copiar(tabuleiro, backupTabuleiro); // copia a matriz para o backup
    pontuacaoBackup = pontuacao;                   // guarda a pontuação atual
    temBackup = true;                              // marca que existe backup
}

//parte q emilly tinha colocado no loop principal, só passei pra cá pra ficar mais separado pq essa parte ainda vai aumentar
void jogo_atualizar(){
    //se apertar pra pausar
    if(IsKeyPressed(KEY_P)){
        estadoAtual = ESTADO_PAUSADO;
        return;
    }

    //CLIQUE NOS BOTÕES DA TELA (Dica e Desfazer)
    if(IsMouseButtonPressed(MOUSE_LEFT_BUTTON)){
        Vector2 mouse = GetMousePosition();
        // clique dentro do botão de dica
        if(mouse.x >= BOTAO_X && mouse.x <= BOTAO_X + BOTAO_LARGURA &&
           mouse.y >= BOTAO_DICA_Y && mouse.y <= BOTAO_DICA_Y + BOTAO_ALTURA){
            usar_dica();
            return;
        }
        // clique dentro do botão de desfazer
        if(mouse.x >= BOTAO_X && mouse.x <= BOTAO_X + BOTAO_LARGURA &&
           mouse.y >= BOTAO_DESFAZER_Y && mouse.y <= BOTAO_DESFAZER_Y + BOTAO_ALTURA){
            desfazer_jogada();
            return;
        }

        //clique no botão de encerrar
        if(mouse.x >= BOTAO_ENCERRAR_X && mouse.x <= BOTAO_ENCERRAR_X + BOTAO_LARGURA &&
           mouse.y >= BOTAO_ENCERRAR_Y && mouse.y <= BOTAO_ENCERRAR_Y + BOTAO_ALTURA){
            estadoAtual = ESTADO_GAME_OVER;
            return;
        }
    }

    int lin, col;
        
        if(obter_gema_clicada(&lin, &col)){
            if(linha1 == -1){
                linha1 = lin;
                coluna1 = col;
            } else{
                int linha2 = lin;
                int coluna2 = col;

                if(gemas_vizinhas(linha1,coluna1,linha2,coluna2) && troca_gera_trio(tabuleiro,linha1,coluna1,linha2,coluna2)){
                    salvar_estado(); // guarda o estado atual antes da jogada (para o desfazer)
                    trocar_gemas(tabuleiro,linha1, coluna1,linha2,coluna2);

                    dicaAtiva = false; // o tabuleiro mudou, então a dica anterior não vale mais

                    animLinha1 = linha1;
                    animColuna1 = coluna1;
                    animLinha2 = linha2; 
                    animColuna2 = coluna2;
                    animInicio = GetTime();
                    animAtiva = true;

                    bool marcado[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO];

                    do{
                        // detecta as combinações atuais e preenche o marcado
                        tabuleiro_detectar_combinacoes(tabuleiro, marcado);

                        tocar_som_gemas_quebrando(tabuleiro_tem_combinacao(marcado));

                        for(int i = 0; i < TAMANHO_TABULEIRO; i++){
                            for(int j = 0; j < TAMANHO_TABULEIRO; j++){
                                if(marcado[i][j]){
                                    pontuacao += 5;
                                }
                            }
                        }
                        
                        //atualizar o recorde do jogador
                        if(pontuacao>recorde){
                            recorde = pontuacao;
                        }

                        // remove as gemas combinadas e desce as de cima
                        tabuleiro_remover_combinacoes(tabuleiro);
                        efeito_cascata(tabuleiro);

                        // detecta novas combinações após a cascata
                        tabuleiro_detectar_combinacoes(tabuleiro, marcado);
                    }while(tabuleiro_tem_combinacao(marcado));
                }

                linha1 = -1; //reiniciar os valores 
                coluna1 = -1;
            }
            
        }

        if(jogo_encerrar()){
            estadoAtual = ESTADO_GAME_OVER; //se n tiver mais jogada possivel, atualiza pra poder desenhar a tela final
        }
}

// verifica se um clique ficou dentro de um botão  do menu
static bool clique_no_botao_(Vector2 mouse, int y){
    return (mouse.x >= MENU_BOTAO_X && mouse.x <= MENU_BOTAO_X + MENU_BOTAO_LARGURA &&
            mouse.y >= y && mouse.y <= y + MENU_BOTAO_ALTURA);
}

void jogo_atualizar_telas(){
    switch(estadoAtual){
        case ESTADO_TELA_INICIAL:
            // cliques nos botões es do menu
            if(IsMouseButtonPressed(MOUSE_LEFT_BUTTON)){
                Vector2 mouse = GetMousePosition();
                if(clique_no_botao_(mouse, MENU_BOTAO_JOGAR_Y)){
                    jogo_reiniciar(); // começa a partida -> ESTADO_JOGANDO
                } else if(clique_no_botao_(mouse, MENU_BOTAO_INSTRUCOES_Y)){
                    estadoAtual = ESTADO_INSTRUCOES;
                } else if(clique_no_botao_(mouse, MENU_BOTAO_CONFIGURACOES_Y)){
                    estadoAtual = ESTADO_CONFIGURACOES;
                }
            }
            break;

        case ESTADO_INSTRUCOES:
            // ESPAÇO volta para a tela inicial
            if(IsKeyPressed(KEY_SPACE)){
                estadoAtual = ESTADO_TELA_INICIAL;
            }
            break;
        case ESTADO_CONFIGURACOES:
            // ESPAÇO volta para o menu principal
            if(IsMouseButtonPressed(MOUSE_LEFT_BUTTON)){
                Vector2 mouse = GetMousePosition();
                if(clique_no_botao_(mouse, CONFIG_BOTAO_SOM_Y)){
                    somAtivo = !somAtivo;
                    ativar_ou_desativar_musica(!somAtivo); // pausar = !somAtivo
                }
            }
            // ESPAÇO volta para o menu principal
            if(IsKeyPressed(KEY_SPACE)){
                estadoAtual = ESTADO_TELA_INICIAL;
            }
            break;
        case ESTADO_JOGANDO:
            jogo_atualizar();
            if(IsKeyPressed(KEY_SPACE)){
                estadoAtual = ESTADO_TELA_INICIAL;
            }

            if(IsKeyPressed(KEY_P)){
                estadoAtual = ESTADO_PAUSADO;
                ativar_ou_desativar_musica(true);
            }
            
            break;

        case ESTADO_PAUSADO:
            if(IsKeyPressed(KEY_P)){ //se tiver pausado e clicar dnv pra despausar
                estadoAtual = ESTADO_JOGANDO;
                ativar_ou_desativar_musica(false); 
            }
            break;

        case ESTADO_GAME_OVER:
            // ESPAÇO volta para a tela inicial
            if(IsKeyPressed(KEY_SPACE)){
                estadoAtual = ESTADO_TELA_INICIAL;
            }
            break;
    }
}

void jogo_renderizar(){
    switch(estadoAtual){
        case ESTADO_TELA_INICIAL:
            renderizar_fundo(false);
            interface_tela_inicial();
            break;

        case ESTADO_INSTRUCOES:
            renderizar_fundo(true);
            interface_tela_instrucoes();
            break;

        case ESTADO_CONFIGURACOES:
           renderizar_fundo(true);
           interface_tela_configuracoes(somAtivo);
            break;

        case ESTADO_JOGANDO:
            renderizar_fundo(true);
            renderizar(tabuleiro);
            // desenha o destaque da dica nas células sugeridas, se estiver ativa
            if(dicaAtiva){
                renderizar_dica(dicaLinha1, dicaColuna1, dicaLinha2, dicaColuna2);
            }

             if(linha1 != -1){
                renderizar_selecao(linha1, coluna1);
            }
            // desenha a animação de troca
            if(animAtiva){
                double progresso = (GetTime() - animInicio) / DURACAO_ANIMACAO_TROCA;
                if(progresso >= 1.0){
                    animAtiva = false;
                } else {
                    renderizar_animacao_troca(animLinha1, animColuna1, animLinha2, animColuna2, (float)progresso);
                }
            }

            // desenha os botões de Dica e Desfazer ao lado do tabuleiro
            renderizar_botoes_jogo();
            // mostra a pontuação atual no topo
            DrawText(TextFormat("Pontuacao: %i", pontuacao), 20, 20, 20, WHITE);
            break;

        case ESTADO_PAUSADO:
            renderizar_fundo(true);
            renderizar(tabuleiro);
            DrawText("PAUSADO - aperte P para continuar", 20, 20, 20, WHITE); //ainda atualizar
            break;

        case ESTADO_GAME_OVER:
            renderizar_fundo(true);
            interface_tela_final(pontuacao,recorde);
            break;
    }
    //renderizar(tabuleiro);
}
    

//aqui colocar a função de jogo encerrado
bool jogo_encerrar(){
    if (!tabuleiro_existe_jogada_possivel(tabuleiro)){
        return true; // não há mais jogadas possíveis, o jogo deve encerrar
    }
    
    return false;
}

EstadoJogo obter_estado(){
    return estadoAtual;
}

void jogo_definir_estado(EstadoJogo novoEstado){
    estadoAtual = novoEstado;
}

void jogo_reiniciar(){
    tabuleiro_inicializar(tabuleiro);
    pontuacao = 0;
    linha1 = -1;
    coluna1 = -1;

    // limpa o estado das mecânicas de dica e desfazer
    dicaAtiva = false;
    dicaLinha1 = dicaColuna1 = dicaLinha2 = dicaColuna2 = -1;
    temBackup = false;
    pontuacaoBackup = 0;

    estadoAtual = ESTADO_JOGANDO;
}

int jogo_obter_pontuacao(){
    return pontuacao;
}

