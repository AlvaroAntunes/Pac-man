#include "tTunel.h"

tTunel* CriaTunel(int linhaAcesso1, int colunaAcesso1, int linhaAcesso2, int colunaAcesso2)
{
    tTunel *tunel = (tTunel *)malloc(sizeof(tTunel));

    tunel->acesso1 = CriaPosicao(linhaAcesso1, colunaAcesso1);
    tunel->acesso2 = CriaPosicao(linhaAcesso2, colunaAcesso2);

    return tunel;
}

bool EntrouTunel(tTunel* tunel, tPosicao* posicao)
{
    int linha = ObtemLinhaPosicao(posicao);
    int coluna = ObtemColunaPosicao(posicao);

    if (linha == ObtemLinhaPosicao(tunel->acesso1) && coluna == ObtemColunaPosicao(tunel->acesso1))
        return true;

    else if (linha == ObtemLinhaPosicao(tunel->acesso2) && coluna == ObtemColunaPosicao(tunel->acesso2))
        return true;

    else
        return false;
}

void LevaFinalTunel(tTunel* tunel, tPosicao* posicao)
{
    int linha = ObtemLinhaPosicao(posicao);
    int coluna = ObtemColunaPosicao(posicao);

    if (linha == ObtemLinhaPosicao(tunel->acesso1) && coluna == ObtemColunaPosicao(tunel->acesso1))
    {
        tPosicao *posicaoNova = CriaPosicao(ObtemLinhaPosicao(tunel->acesso2), ObtemColunaPosicao(tunel->acesso2));
        AtualizaPosicao(posicao, posicaoNova);
        DesalocaPosicao(posicaoNova);
    }

    else if (linha == ObtemLinhaPosicao(tunel->acesso2) && coluna == ObtemColunaPosicao(tunel->acesso2))
    {
        tPosicao *posicaoNova = CriaPosicao(ObtemLinhaPosicao(tunel->acesso1), ObtemColunaPosicao(tunel->acesso1));
        AtualizaPosicao(posicao, posicaoNova);
        DesalocaPosicao(posicaoNova);
    }
}

void DesalocaTunel(tTunel* tunel)
{
    if (tunel != NULL)
    {
        DesalocaPosicao(tunel->acesso1);
        DesalocaPosicao(tunel->acesso2);
        free(tunel);
    }
}