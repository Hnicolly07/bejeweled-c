# Bejeweled C

Projeto do jogo Bejeweled desenvolvido em linguagem C utilizando a biblioteca Raylib.

---

## 1. Introdução

### Descrição geral
Desevolvimento, em grupo, de um programa semelhante ao jogo Bejeweled

### Objetivos do projeto
Promover a capacidade e o conhecimento prático para criar e desenvolver projetos na linguagem C.

### Funcionalidades
- Tela inicial, tela de configurações e tela de Game Over
- Opção para para ligar ou desligar a música na tela de configurações
- Input de botões das gemas para selecioná-las
- Selecionar duas gemas para trocarem suas posições
- Efeito cascata quando ocorre uma combinação de gemas feita pelo jogador
- Sistema de pontuação
### Tecnologias utilizadas
- O projeto foi feito na linguagem C
- Uso das bibliotecas padrões da linguagem C
- Uso da biblioteca Raylib.

---

## 2. Estrutura do projeto
```md
Bejeweled C/
├── assets/
│   ├── imagens
│   └── sounds
├── include/
|    ├── audio.h
|    ├── gema.h
|    ├── interface.h
|    ├── jogo.h
|    ├── render.h
|    └──tabuleiro.h
├── src/
|    ├── áudio.c
|    ├── gema.c
|    ├── interface.c
|    ├── jogo.c
|    ├── render.c
|    └── tabuleiro.c       
├── .gitignore
├── makefile
├── README.md
└── config.mk
```

---

## 3. Como compilar e executar

### Pré-requisitos
- Ter algum compilador C já instalado
- Ter instalado a biblioteca Raylib
    - [Link para o raylib](https://www.raylib.com/)
### Como instalar o compilador e executar no VS Code no Windows
1. Fazer a instalação do VS Code através do [Link](https://code.visualstudio.com/download?_exp_download=fb315fc982)
2. Ir nas extenções, procurar e baixar a extensão C/C++ Compile Run
![Texto alternativo](https://www.alura.com.br/artigos/assets/compilando-executando-programas-cc-windows/imagem18.png)
3. No terminal, no caminho do projeto, digitar os seguintes comando:
- para compilar todos os arquivos e linkar com a biblioteca do raylib:  
`make`
- para executar o programa compilado:  
`make run`
---

## 4. Como jogar
1. na tela inicial, selecionar com o botão esquerdo do mouse o botão de iniciar jogo
2. no tabuleiro, procurar um possível arranjo de 3 ou mais gemas idênticas ao trocar duas gemas vizinhas ortogonais diretas
3. Fazer a troca selecionando as duas gemas através do botão esquerdo do mouse
4. A condição de game over deve ocorrer quando após a quebra de um arranjo de gemas, não existir mais a possibilidade de outra formação de arranjo de três gemas ou mais.
---

## 5. Organização do código
1. assets: Pasta para guardar imagens e sons para posteriormente utilizá-las no jogo
2. Include: Pasta que possui todos os arquivos .h os quais contém as declarações de variáveis e funções que são usadas no programa.
3. src: Pasta que inclui os arquivos .c que abrange o código em si e a manipulação das variáveis declaradas. 
---

## 6. Equipe
Iago de França  
Emilly Karoline  
Hiorrana Nicolly de Santana
---

## 7. Licença
A Licença do MIT (MIT)  
Direitos autorais (c) 2026 Hiorrana Nicolly Emilly Karoline Iago de França

A permissão é concedida, gratuitamente, a qualquer pessoa que obtenha uma cópia desse software e arquivos de documentação associados (o "Bejeweled-c"), para lidar com o Software sem restrições, incluindo sem limitação os direitos usar, copiar, modificar, mesclar, publicar, distribuir, sublicenciar e/ou vender cópias do Software, e permitir que pessoas a quem o Software seja destinado Fornecido para isso, sujeito às seguintes condições: O aviso de direitos autorais acima e este aviso de permissão devem ser incluídos em todos cópias ou partes substanciais do Software.

O SOFTWARE É FORNECIDO "COMO ESTÁ", SEM QUALQUER TIPO DE GARANTIA, EXPRESSA OU IMPLÍCITO, INCLUINDO, MAS NÃO SE LIMITANDO A, AS GARANTIAS DE COMERCIALIZAÇÃO, APTIDÃO PARA UM PROPÓSITO ESPECÍFICO E NÃO INFRAÇÃO. EM NENHUM CASO O AUTORES OU DETENTORES DE DIREITOS AUTORAIS SERÃO RESPONSÁVEIS POR QUALQUER REIVINDICAÇÃO, DANOS OU OUTROS DIREITOS RESPONSABILIDADE, SEJA EM UMA AÇÃO CONTRATUAL, ILÍCITO OU OUTRO, DECORRENTE DE, FORA OU EM CONEXÃO COM O SOFTWARE OU O USO OU OUTRAS TRANSAÇÕES NA SOFTWARE.
