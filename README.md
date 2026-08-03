# Bejeweled C

Projeto de jogo **Bejeweled** desenvolvido em linguagem C utilizando a biblioteca Raylib.

---

# 1. Introdução

## Descrição geral

Este projeto consiste no desenvolvimento de uma versão simplificada do jogo **Bejeweled**, implementada em linguagem C como atividade das disciplinas de Linguagem de Programação I e Laboratório de Programação I.

## Objetivos do projeto

- Aplicar os conceitos estudados na linguagem C.
- Desenvolver habilidades de programação modular.
- Trabalhar em equipe utilizando Git e GitHub.
- Praticar a organização e estruturação de projetos de software.

## Funcionalidades

- Tela inicial.
- Tela de configurações.
- Tela de fim de jogo.
- Sistema de pontuação e recorde.
- Ativação e desativação da música.
- Seleção de gemas através do mouse.
- Troca entre gemas vizinhas.
- Detecção de combinações de três ou mais gemas.
- Efeito cascata após a remoção das combinações.
- Geração de novas gemas após o efeito cascata.
- Encerramento automático da partida quando não existem mais jogadas possíveis.

## Tecnologias utilizadas

- C
- Raylib
- Git e GitHub

---

# 2. Estrutura do projeto

```text
Bejeweled C/
├── assets/
│   ├── imagens/
│   └── sounds/
├── include/
│   ├── audio.h
│   ├── gema.h
│   ├── interface.h
│   ├── jogo.h
│   ├── render.h
│   └── tabuleiro.h
├── src/
│   ├── audio.c
│   ├── gema.c
│   ├── interface.c
│   ├── jogo.c
│   ├── render.c
│   └── tabuleiro.c
├── .gitignore
├── config.mk
├── makefile
└── README.md
```

---

# 3. Como compilar e executar

## Pré-requisitos

- Compilador C instalado.
- Biblioteca Raylib instalada.

Site oficial da Raylib:

https://www.raylib.com/

## Compilação

No terminal, dentro da pasta do projeto, execute:

```bash
make
```

## Execução

Após a compilação:

```bash
make run
```

---

# 4. Como jogar

1. Na tela inicial, clique em **Iniciar Jogo**.
2. Selecione duas gemas vizinhas utilizando o botão esquerdo do mouse.
3. A troca só será realizada caso forme uma combinação válida de três ou mais gemas iguais.
4. As combinações são removidas automaticamente.
5. As gemas acima caem, formando o efeito cascata.
6. Novas gemas são geradas para preencher os espaços vazios.
7. O jogo termina quando não existem mais jogadas possíveis.

---

# 5. Organização do código

- **assets/**: imagens e efeitos sonoros utilizados pelo jogo.
- **include/**: arquivos .h, contendo declarações de funções, constantes e estruturas utilizadas nos códigos fonte.
- **src/**: arquivos .c, implementando as funcionalidades do jogo.

---
# 6. Equipe

- Hiorrana Nicolly de Santana
- Emilly Karoline
- Iago de França
