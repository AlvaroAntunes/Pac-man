#include "tPosicao.h"

tPosicao* CriaPosicao(int linha, int coluna)
{
    tPosicao *posicao;
    posicao = (tPosicao *)calloc(1, sizeof(tPosicao));

    posicao->linha = linha;
    posicao->coluna = coluna;

    return posicao;
}

tPosicao* ClonaPosicao(tPosicao* posicao)
{
    tPosicao *posicaoClone = CriaPosicao(posicao->linha, posicao->coluna);

    return posicaoClone;
}

int ObtemLinhaPosicao(tPosicao* posicao)
{
    return posicao->linha;
}

int ObtemColunaPosicao(tPosicao* posicao)
{
    return posicao->coluna;
}

void AtualizaPosicao(tPosicao* posicaoAtual, tPosicao* posicaoNova)
{
    posicaoAtual->linha = posicaoNova->linha;
    posicaoAtual->coluna = posicaoNova->coluna;
}

bool SaoIguaisPosicao(tPosicao* posicao1, tPosicao* posicao2)
{
    if (posicao1->linha == posicao2->linha && posicao1->coluna == posicao2->coluna)
        return true;
    
    else
        return false;
}

void DesalocaPosicao(tPosicao* posicao)
{
    if (posicao != NULL)
        free(posicao);
}