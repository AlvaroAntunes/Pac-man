#ifndef _TJOGO_H_
#define _TJOGO_H_

#include "tMapa.h"
#include "tPosicao.h"
#include "tPacman.h"
#include "constantes.h"
#include "tFantasma.h"
#include "utils.h"

typedef struct
{
    tPacman* Pacman;
    tMapa* mapaJogo;
    tMapa* mapaAuxiliar;
    tMapa* mapaEspelho;
    tFantasma** fantasmas;
} tJogo;

typedef struct
{
    char movimento;
    int qtdFrutas;
    int qtdColisoes;
    int qtdMovimentos;
} tRanking;

tJogo AtualizaOEstadoDoJogo(tJogo jogo, tPacman *clonePacman, COMANDO comando);
void PreencheInicializacao(tJogo jogo);
void AtualizaMapaEspelho(tMapa* mapa, tMapa* mapaEspelho);
void PreencheRanking(tPacman* pacman);
void OrdenaRanking(tRanking* dadosRanking);
void DesalocaJogo(tJogo jogo, int nFantasmas);
void DesalocaJogador(tPacman* pacman);

#endif