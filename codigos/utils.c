#include "utils.h"

void ImprimeOMapa(tMapa *mapa)
{
    int nLinhas = ObtemNumeroLinhasMapa(mapa);
    int nColunas = ObtemNumeroColunasMapa(mapa);

    for (int i = 0; i < nLinhas; i++)
    {
        for (int j = 0; j < nColunas; j++)
        {
            tPosicao *posicao = CriaPosicao(i, j);
            printf("%c", ObtemItemMapa(mapa, posicao));
            free(posicao);
        }
        printf("\n");
    }
}

void VerificaItemAnterior(tMapa *mapa, tMapa *mapaAuxiliar, int linha, int coluna)
{
    /*
    Em alguns casos especifícos (exemplo: na primeira movimentação do mapa) pode ocorrer de que na posição anterior do fantasma seja um fantasma ou na posição anterior do Pacman for um Pacman, o que não faz nenhum sentido devolver esse item para aquela posição, então quando isso ocorrer, eu atribuo um espaço naquela posição.
    */

    tPosicao *posicao = CriaPosicao(linha, coluna);
    char celula = ObtemItemMapa(mapaAuxiliar, posicao);

    if (EhFantasma(mapaAuxiliar, posicao) || EhPacman(mapaAuxiliar, posicao))
        celula = ' ';

    AtualizaItemMapa(mapa, posicao, celula);

    free(posicao);
}

bool EhPacman(tMapa *mapa, tPosicao *posicao)
{
    if (ObtemItemMapa(mapa, posicao) == PACMAN)
        return true;
        
    else
        return false;
}