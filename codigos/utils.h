#ifndef _UTILS_H_
#define _UTILS_H_

#include <stdio.h>
#include <stdbool.h>

#include "tMapa.h"
#include "tPosicao.h"
#include "constantes.h"
#include "tPacman.h"
#include "tFantasma.h"

void ImprimeOMapa(tMapa *mapa);
void VerificaItemAnterior(tMapa *mapa, tMapa *mapaAuxiliar, int linha, int coluna);
bool EhPacman(tMapa *mapa, tPosicao *posicao);

#endif