#ifndef _FANTASMAS_H
#define _FANTASMAS_H

#include <stdbool.h>

#include "tPosicao.h"
#include "constantes.h"
#include "tMapa.h"
#include "utils.h"

typedef struct
{
    tPosicao* posicaoFantasma;
    int flagInverteSentido;
    char tipoFantasma;
    int quantidadeFantasmas;
} tFantasma;

void InicializaFantasmas(tFantasma* fantasma, char tipoFantasma);

tFantasma** VerificaExistenciaDosFantasmas(tMapa *mapa);

void MoveFantasmas(tMapa *mapa, tMapa *mapaAuxiliar, tFantasma** fantasmas, int qtdFantasmas);

bool EhFantasma(tMapa *mapa, tPosicao *posicao);

int ObtemQuantidadeDeFantasmas(tFantasma** fantasma);

tPosicao* ObtemPosicaoFantasma(tFantasma* fantasma);

char ObtemTipoFantasma(tFantasma* fantasma);

void DesalocaFantasmas(tFantasma **fantasmas, int qtdFantasmas);

#endif