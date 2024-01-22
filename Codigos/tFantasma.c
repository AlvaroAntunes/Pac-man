#include "tFantasma.h"

void InicializaFantasmas(tFantasma* fantasma, char tipoFantasma)
{
    fantasma->flagInverteSentido = false;
    fantasma->tipoFantasma = tipoFantasma;
}

tFantasma **VerificaExistenciaDosFantasmas(tMapa *mapa)
{
    /*
    Como em todos os mapas tem um fantasma, eu faço a alocação de um fantasma no início da função, depois, se necessário, faço a realocação para criar novos fantasmas.
    */

    int numeroLinhasMapa = ObtemNumeroLinhasMapa(mapa);
    int numeroColunasMapa = ObtemNumeroColunasMapa(mapa);
    int qtdFantasmas = 0;

    tFantasma **fantasmas = (tFantasma **)calloc(1, sizeof(tFantasma *));
    fantasmas[qtdFantasmas] = (tFantasma *)calloc(1, sizeof(tFantasma));

    for (int i = 0; i < numeroLinhasMapa; i++)
    {
        for (int j = 0; j < numeroColunasMapa; j++)
        {
            tPosicao *posicao = CriaPosicao(i, j);

            if (ObtemItemMapa(mapa, posicao) == FANTASMA_B)
            {
                fantasmas[qtdFantasmas]->posicaoFantasma = CriaPosicao(i, j);

                InicializaFantasmas(fantasmas[qtdFantasmas], FANTASMA_B);
                qtdFantasmas++;
                fantasmas = realloc(fantasmas, (qtdFantasmas+1) * sizeof(tFantasma *));
                fantasmas[qtdFantasmas] = (tFantasma *)calloc(1, sizeof(tFantasma));
            }

            else if (ObtemItemMapa(mapa, posicao) == FANTASMA_P)
            {
                fantasmas[qtdFantasmas]->posicaoFantasma = CriaPosicao(i, j);

                InicializaFantasmas(fantasmas[qtdFantasmas], FANTASMA_P);
                qtdFantasmas++;
                fantasmas = realloc(fantasmas, (qtdFantasmas+1) * sizeof(tFantasma *));
                fantasmas[qtdFantasmas] = (tFantasma *)calloc(1, sizeof(tFantasma));
            }

            else if (ObtemItemMapa(mapa, posicao) == FANTASMA_I)
            {
                fantasmas[qtdFantasmas]->posicaoFantasma = CriaPosicao(i, j);

                InicializaFantasmas(fantasmas[qtdFantasmas], FANTASMA_I);
                qtdFantasmas++;
                fantasmas = realloc(fantasmas, (qtdFantasmas+1) * sizeof(tFantasma *));
                fantasmas[qtdFantasmas] = (tFantasma *)calloc(1, sizeof(tFantasma));
            }
            
            else if (ObtemItemMapa(mapa, posicao) == FANTASMA_C)
            {
                fantasmas[qtdFantasmas]->posicaoFantasma = CriaPosicao(i, j);

                InicializaFantasmas(fantasmas[qtdFantasmas], FANTASMA_C);
                qtdFantasmas++;
                fantasmas = realloc(fantasmas, (qtdFantasmas+1) * sizeof(tFantasma *));
                fantasmas[qtdFantasmas] = (tFantasma *)calloc(1, sizeof(tFantasma));
            }

            free(posicao);
        }
    }

    for (int i = 0, j = 0; i < qtdFantasmas; i++)
        fantasmas[i][j].quantidadeFantasmas = qtdFantasmas;

    return fantasmas;
}

void MoveFantasmas(tMapa *mapa, tMapa *mapaAuxiliar, tFantasma** fantasmas, int qtdFantasmas)
{
    int linha, coluna;
    tPosicao *posicaoNova = NULL;
    tPosicao *posicaoAuxiliar = NULL;

    for (int i = 0; i < qtdFantasmas; i++)
    {
        linha = ObtemLinhaPosicao(fantasmas[i]->posicaoFantasma);
        coluna = ObtemColunaPosicao(fantasmas[i]->posicaoFantasma);

      /*
      Como os fantasmas B e C se movem na mesma direção, eu faço duas condições para eles: caso o fantasma B esteja se movendo no seu sentido original e o C tenha invertido o sentido (por colidir em uma parede), eles estão indo para a esquerda, então o movimento vai ser o mesmo para os dois. Agora, se isso inverter (o fantasma C esteja em seu sentido original e o B tenha invertido), eles estão indo para a direita, ou seja, o movimento vai ser comum para os dois. A ideia vai ser a mesma para os fantasmas I e P, o que muda vai ser a direção de movimento (eles se movem na vertical).

      Agora, além dessa condição, preciso verificar se o fantasma encontrou uma parede ou não, caso tenha encontrado, eu tenho que inverter o sentido de movimento dele. Além disso, eu preciso sempre que o fantasma devolva o item anterior antes dele chegar em uma nova posição, pois ele não come comida e não entra no túnel, logo tenho que sempre devolver o item antes do fantasma chegar naquela posição. Por esse motivo eu uso o mapa auxiliar, pois no mapa auxiliar as comidas e túneis ficam fixos e só atualizo ele quando o Pacman come uma comida, logo eu sei que, se há comida ou túnel naquela posição, o fantasma devolve quando sai dela. 
      */

        if ((fantasmas[i]->tipoFantasma == FANTASMA_B && !fantasmas[i]->flagInverteSentido)  ||
            (fantasmas[i]->tipoFantasma == FANTASMA_C && fantasmas[i]->flagInverteSentido))
        {
            posicaoNova = CriaPosicao(linha, coluna-1);

            if (!EncontrouParedeMapa(mapa, posicaoNova))
            {
                AtualizaPosicao(fantasmas[i]->posicaoFantasma, posicaoNova);
                VerificaItemAnterior(mapa, mapaAuxiliar, linha, coluna);
            }

            else
            {
                posicaoAuxiliar = CriaPosicao(linha, coluna+1);
                AtualizaPosicao(fantasmas[i]->posicaoFantasma, posicaoAuxiliar);
                VerificaItemAnterior(mapa, mapaAuxiliar, linha, coluna);

                free(posicaoAuxiliar);

                /*
                Tenho que saber qual é o fantasma, pois o fantasma já pode estar com o sentido invertido, então tenho que inverter novamente, que na prática é deixar o sentido como o original da movimentação dele.
                */

                if (fantasmas[i]->tipoFantasma == FANTASMA_C)
                    fantasmas[i]->flagInverteSentido = false;
                
                else
                    fantasmas[i]->flagInverteSentido = true;
            }
            free(posicaoNova);
        }

        else if ((fantasmas[i]->tipoFantasma == FANTASMA_C && !fantasmas[i]->flagInverteSentido) ||
                (fantasmas[i]->tipoFantasma == FANTASMA_B && fantasmas[i]->flagInverteSentido))
        {
            posicaoNova = CriaPosicao(linha, coluna+1);

            if (!EncontrouParedeMapa(mapa, posicaoNova))
            {
                AtualizaPosicao(fantasmas[i]->posicaoFantasma, posicaoNova);
                VerificaItemAnterior(mapa, mapaAuxiliar, linha, coluna);
            }

            else
            {
                posicaoAuxiliar = CriaPosicao(linha, coluna-1);
                AtualizaPosicao(fantasmas[i]->posicaoFantasma, posicaoAuxiliar);
                VerificaItemAnterior(mapa, mapaAuxiliar, linha, coluna);
                
                free(posicaoAuxiliar);

                if (fantasmas[i]->tipoFantasma == FANTASMA_B)
                    fantasmas[i]->flagInverteSentido = false;
                
                else
                    fantasmas[i]->flagInverteSentido = true;
            }
            free(posicaoNova);
        }

        else if ((fantasmas[i]->tipoFantasma == FANTASMA_P && !fantasmas[i]->flagInverteSentido) ||
                (fantasmas[i]->tipoFantasma == FANTASMA_I && fantasmas[i]->flagInverteSentido))
        {
            posicaoNova = CriaPosicao(linha-1, coluna);

            if (!EncontrouParedeMapa(mapa, posicaoNova))
            {
                AtualizaPosicao(fantasmas[i]->posicaoFantasma, posicaoNova);
                VerificaItemAnterior(mapa, mapaAuxiliar, linha, coluna);
            }

            else
            {
                posicaoAuxiliar = CriaPosicao(linha+1, coluna);
                AtualizaPosicao(fantasmas[i]->posicaoFantasma, posicaoAuxiliar);
                VerificaItemAnterior(mapa, mapaAuxiliar, linha, coluna);
                
                free(posicaoAuxiliar);

                if (fantasmas[i]->tipoFantasma == FANTASMA_I)
                    fantasmas[i]->flagInverteSentido = false;
                
                else
                    fantasmas[i]->flagInverteSentido = true;
            }
            free(posicaoNova);
        }

        else if ((fantasmas[i]->tipoFantasma == FANTASMA_I && !fantasmas[i]->flagInverteSentido) ||
                (fantasmas[i]->tipoFantasma == FANTASMA_P && fantasmas[i]->flagInverteSentido))
        {
            posicaoNova = CriaPosicao(linha+1, coluna);

            if (!EncontrouParedeMapa(mapa, posicaoNova))
            {
                AtualizaPosicao(fantasmas[i]->posicaoFantasma, posicaoNova);
                VerificaItemAnterior(mapa, mapaAuxiliar, linha, coluna);
            }

            else
            {
                posicaoAuxiliar = CriaPosicao(linha-1, coluna);
                AtualizaPosicao(fantasmas[i]->posicaoFantasma, posicaoAuxiliar);
                VerificaItemAnterior(mapa, mapaAuxiliar, linha, coluna);
                
                free(posicaoAuxiliar);

                if (fantasmas[i]->tipoFantasma == FANTASMA_P)
                    fantasmas[i]->flagInverteSentido = false;
                
                else
                    fantasmas[i]->flagInverteSentido = true;

            }
            free(posicaoNova);
        }
    }
}

bool EhFantasma(tMapa *mapa, tPosicao *posicao)
{
    char celula = ObtemItemMapa(mapa, posicao);

    if (celula == FANTASMA_B || celula == FANTASMA_C || celula == FANTASMA_I || celula == FANTASMA_P)
        return true;
        
    return false;
}

int ObtemQuantidadeDeFantasmas(tFantasma** fantasma)
{
    int i = 0;
    return fantasma[i]->quantidadeFantasmas;
}

tPosicao* ObtemPosicaoFantasma(tFantasma* fantasma)
{
    return fantasma->posicaoFantasma;
}

char ObtemTipoFantasma(tFantasma* fantasma)
{
    return fantasma->tipoFantasma;
}

void DesalocaFantasmas(tFantasma** fantasmas, int qtdFantasmas)
{
    /*
    Aqui eu desaloco até ser igual a quantidade de fantasmas pois pela lógica de realocação, um fantasma a mais vai ser alocado, então preciso desalocá-lo.
    */

    if (fantasmas != NULL)
    {
        for (int i = 0; i <= qtdFantasmas; i++)
        {
            if (fantasmas[i]->posicaoFantasma != NULL)
                DesalocaPosicao(fantasmas[i]->posicaoFantasma);
                
            if (fantasmas[i] != NULL)
                free(fantasmas[i]);
        }
        free(fantasmas);
    }
}