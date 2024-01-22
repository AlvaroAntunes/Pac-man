# Pacman - Jogo em C para Terminal

![Pacman](https://veja.abril.com.br/wp-content/uploads/2016/05/pac-man-original.png)

## Descrição

Pacman é um jogo clássico e atemporal que desafia os jogadores a controlar um personagem amarelo (Pacman) enquanto ele percorre um labirinto, come pontos e evita fantasmas. Este jogo em C para o terminal oferece uma versão simplificada do clássico, mantendo a essência e a diversão do original.
- Esse jogo foi criado na disciplina de Programação 2 da Universidade Federal do Espírito Santo (UFES) para utilizar, principalmente, os conceitos de ponteiros, alocação dinâmica de memória e Tipo Abstrato de Dados (TAD).

## Características

- O Pacman nessa versão simplificada é representado pelo símbolo '>'.
- Os fantasmas são representados pelas letras B, P, I, C.
- Controle o Pacman com as teclas w (cima), s (baixo), a (esquerda) e d (direita).
- Evite fantasmas enquanto coleta pontos no labirinto.
- Ganhe pontos extras comendo frutas especiais.
- Desafie seus reflexos e estratégias para sobreviver o maior tempo possível (nessa versão, cada mapa tem um número máximo de jogadas).
- Para jogar em outros mapas, basta mudar o caso no arquivo de Makefile. Mais instruções em **Como jogar**.
- Ao final do jogo, o programa gera arquivos relacionados àquela partida. Por exemplo, o programa gerará um arquivo denominado 'ranking.txt', o qual mostrará quais foram as melhores jogadas (w, s, a e d) da partida.

## Requisitos

- Compilador C (ex: GCC)
- Terminal

## Como Jogar

- Caso já tenha o GCC (compilador C) instalado, basta seguir o passo-a-passo abaixo:

1. Clone o repositório:
   ```bash
   git clone https://github.com/AlvaroAntunes/pacman-c.git

2. Navegue até o diretório do jogo:
    ```bash
    cd pacman-c

3. Compile e execute o jogo:
    ```bash
    make
 - Para jogar em outro mapa, basta ir na macro 'executable' do arquivo **Makefile** e mudar casos/01 para casos/(caso desejado).
