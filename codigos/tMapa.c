#include "tMapa.h"

#define MAX_DIR 1001
#define ERROR 1

tMapa* CriaMapa(const char* caminhoConfig)
{
    /*
    Nessa função, além de criar o mapa, eu já verifico as frutas do mapa para saber a quantidade e já faço a verificação para saber se no mapa tem túnel.
    */
   
    tMapa *mapaJogo;
    char diretorio[MAX_DIR];

    sprintf(diretorio, "%s/mapa.txt", caminhoConfig);
    FILE *pMapa = fopen(diretorio, "r");

    if (pMapa == NULL)
    {
        printf("ERRO: nao foi possível ler o arquivo /%s\n", diretorio);
        exit(ERROR);
    }

    mapaJogo = (tMapa *)calloc(1, sizeof(tMapa));

    fscanf(pMapa, "%d%*c", &mapaJogo->nMaximoMovimentos);

    int linhas = 0, colunas = 0;

    mapaJogo->grid = (char **)calloc(1, sizeof(char *));
    mapaJogo->grid[linhas] = (char *)calloc(1, sizeof(char));

    char celula;
    int linhaTunel1 = 0, colunaTunel1 = 0, linhaTunel2 = 0, colunaTunel2 = 0;

    int primeiroTunel = true;

    while (true)
    {
        fscanf(pMapa, "%c", &celula);

        if(feof(pMapa))
            break;

        else if (celula == '\n')
        {
            mapaJogo->grid[linhas][colunas] = '\0';
            mapaJogo->nColunas = colunas;
            linhas++;
            mapaJogo->grid = realloc(mapaJogo->grid, (linhas + 1) * sizeof(char *));            
            mapaJogo->grid[linhas] = (char *)calloc(1, sizeof(char));
            
            colunas = 0;
            continue;
        }

        else if (celula == '*')
            mapaJogo->nFrutasAtual++;

        else if (celula == '@')
        {
            if (primeiroTunel)
            {
                linhaTunel1 = linhas;
                colunaTunel1 = colunas;
                primeiroTunel = false;
            }

            else
            {
                linhaTunel2 = linhas;
                colunaTunel2 = colunas;
            }
        }

        mapaJogo->grid[linhas][colunas] = celula;
        colunas++;
        mapaJogo->grid[linhas] = realloc(mapaJogo->grid[linhas], (colunas + 1) * sizeof(char));
    }
                            
    mapaJogo->nLinhas = linhas;

    if (!PossuiTunelMapa(mapaJogo))
        mapaJogo->tunel = NULL;

    else
        mapaJogo->tunel = CriaTunel(linhaTunel1, colunaTunel1, linhaTunel2, colunaTunel2);

    fclose(pMapa);

    return mapaJogo;
}

tPosicao* ObtemPosicaoItemMapa(tMapa* mapa, char item)
{
    for (int i = 0; i < mapa->nLinhas; i++)
    {
        for (int j = 0; j < mapa->nColunas; j++)
        {
            if (mapa->grid[i][j] == item)
            {
                tPosicao *posicao;
                posicao = CriaPosicao(i, j);
                return posicao;
            }
        }
    }

    return NULL;
}

tTunel* ObtemTunelMapa(tMapa* mapa)
{
    return mapa->tunel;
}

char ObtemItemMapa(tMapa* mapa, tPosicao* posicao)
{
    int linhaPosicao = ObtemLinhaPosicao(posicao);
    int colunaPosicao = ObtemColunaPosicao(posicao);

    if (mapa == NULL || mapa->grid == NULL)
        return '\0';

     else if ((linhaPosicao > mapa->nLinhas-1) || (linhaPosicao < 0) || (colunaPosicao < 0) || (colunaPosicao > mapa->nColunas-1))
        return '\0';

    else
        return mapa->grid[linhaPosicao][colunaPosicao];
}

int ObtemNumeroLinhasMapa(tMapa* mapa)
{
    return mapa->nLinhas;
}

int ObtemNumeroColunasMapa(tMapa* mapa)
{
    return mapa->nColunas;
}

int ObtemQuantidadeFrutasIniciaisMapa(tMapa* mapa)
{
    return mapa->nFrutasAtual;
}

int ObtemNumeroMaximoMovimentosMapa(tMapa* mapa)
{
    return mapa->nMaximoMovimentos;
}

bool EncontrouComidaMapa(tMapa* mapa, tPosicao* posicao)
{
    int linhaPosicao = ObtemLinhaPosicao(posicao);
    int colunaPosicao = ObtemColunaPosicao(posicao);

    if (mapa->grid == NULL)
        return false;
    
    else if ((linhaPosicao > mapa->nLinhas-1) || (linhaPosicao < 0) || (colunaPosicao < 0) || (colunaPosicao > mapa->nColunas-1))  
        return false;  
            

    else if (ObtemItemMapa(mapa, posicao) == '*')
        return true;

    else
        return false;
}

bool EncontrouParedeMapa(tMapa* mapa, tPosicao* posicao)
{
    int linhaPosicao = ObtemLinhaPosicao(posicao);
    int colunaPosicao = ObtemColunaPosicao(posicao);

    if (mapa->grid == NULL)
        return false;
    
    else if ((linhaPosicao > mapa->nLinhas-1) || (linhaPosicao < 0) || (colunaPosicao < 0) || (colunaPosicao > mapa->nColunas-1))  
        return false;  
            

    else if (ObtemItemMapa(mapa, posicao) == '#')
        return true;

    else
        return false;
}

bool AtualizaItemMapa(tMapa* mapa, tPosicao* posicao, char item)
{
    int linhaPosicao = ObtemLinhaPosicao(posicao);
    int colunaPosicao = ObtemColunaPosicao(posicao);

    if (mapa->grid == NULL)
        return false;
    
    else if ((linhaPosicao > mapa->nLinhas-1) || (linhaPosicao < 0) || (colunaPosicao < 0) || (colunaPosicao > mapa->nColunas-1))  
        return false;  
            
    else
    {
        mapa->grid[linhaPosicao][colunaPosicao] = item;
        return true;
    }
}

bool PossuiTunelMapa(tMapa* mapa)
{
    for (int i = 0; i < mapa->nLinhas; i++)
    {
        for (int j = 0; j < mapa->nColunas; j++)
        {
            if (mapa->grid[i][j] == '@')
                return true;
        }
    }

    return false;
}

bool AcessouTunelMapa(tMapa* mapa, tPosicao* posicao)
{
    if (mapa->tunel != NULL)
    {
        if (EntrouTunel(mapa->tunel, posicao))
            return true;
    }

    return false;
}

void EntraTunelMapa(tMapa* mapa, tPosicao* posicao)
{
    LevaFinalTunel(mapa->tunel, posicao);
}

void DesalocaMapa(tMapa* mapa)
{
    if (mapa != NULL)
    {
        if (mapa->grid != NULL)
        {
            for (int i = 0; i <= mapa->nLinhas; i++)
                free(mapa->grid[i]);

            free(mapa->grid);
        }

        if (mapa->tunel != NULL)
            DesalocaTunel(mapa->tunel);
        
        free(mapa);
    }
}