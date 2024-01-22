#include "tMovimento.h"

tMovimento* CriaMovimento(int numeroDoMovimento, COMANDO comando, const char* acao)
{
    tMovimento *movimento = (tMovimento *)calloc(1, sizeof(tMovimento));

    strcpy(movimento->acao, acao);
    movimento->numeroDoMovimento = numeroDoMovimento;
    movimento->comando = comando;

    return movimento;
}

int ObtemNumeroMovimento(tMovimento* movimento)
{
    return movimento->numeroDoMovimento;
}

COMANDO ObtemComandoMovimento(tMovimento* movimento)
{
    return movimento->comando;
}

char* ObtemAcaoMovimento(tMovimento* movimento)
{
    return movimento->acao;
}

void DesalocaMovimento(tMovimento* movimento)
{
    if (movimento != NULL)
        free(movimento);
}