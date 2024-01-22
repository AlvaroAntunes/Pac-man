# Pacman - Jogo em C para Terminal

![Pacman](https://www.google.com/url?sa=i&url=https%3A%2F%2Fpixabay.com%2Fpt%2Fillustrations%2Fpacman-pac-man-aventura-engra%25C3%25A7ado-4285160%2F&psig=AOvVaw343T9dVvzUtsOlo1GR_9qz&ust=1706013716683000&source=images&cd=vfe&opi=89978449&ved=0CBIQjRxqFwoTCICrx8WC8YMDFQAAAAAdAAAAABAD)

## Descrição

Pacman é um jogo clássico e atemporal que desafia os jogadores a controlar um personagem amarelo (Pacman) enquanto ele percorre um labirinto, come pontos e evita fantasmas. Este jogo em C para o terminal oferece uma versão simplificada do clássico, mantendo a essência e a diversão do original.

## Características

- O Pacman nessa versão simplificada é representado pelo símbolo '>'.
- Os fantasmas são representados pelas letras B, P, I, C.
- Controle o Pacman com as teclas w(cima), s(baixo), a(esquerda) e d(direita).
- Evite fantasmas enquanto coleta pontos no labirinto.
- Ganhe pontos extras comendo frutas especiais.
- Desafie seus reflexos e estratégias para sobreviver o maior tempo possível (nessa versão, cada mapa tem um número máximo de jogadas).
- Para jogar em outros mapas, basta mudar o caso no arquivo de Makefile. Na macro 'executable', mude 01 para o caso desejado.
- Ao final do jogo, o programa gera arquivos relacionados àquela partida. Por exemplo, o programa gerará um arquivo denominado 'ranking.txt', o qual mostrará quais foram as melhores jogadas (w, s, a e d) da partida.

## Requisitos

- Compilador C (ex: GCC)
- Terminal

## Como Jogar

- Caso já tenha o GCC (compilador C) instalado, basta seguir o passo-a-passo abaixo:

1. Clone o repositório:
   ```bash
   git clone https://github.com/AlvaroAntunes/pacman-c.git