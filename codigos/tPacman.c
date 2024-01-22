#include "tPacman.h"

#define MAX_ACAO 50
#define TUNEL '@'
#define SPACE ' '

tPacman* CriaPacman(tPosicao* posicao)
{
    /*
    Aqui, além de alocar o Pacman e criá-lo com a posição que foi enviada como parâmetro, eu aloco um ponteiro para um ponteiro de movimento, pois nas outras funções referentes ao histórico de movimentos, eu já faço a realocação e, para realocar, eu preciso ter alocado.
    */

    tPacman *pacMan = (tPacman *)calloc(1, sizeof(tPacman));

    if (posicao == NULL || pacMan == NULL)
        return NULL;
    
    else
    {
        pacMan->posicaoAtual = posicao;
        pacMan->historicoDeMovimentosSignificativos = (tMovimento **)calloc(1, sizeof(tMovimento *));
        pacMan->trilha = NULL;
        pacMan->estaVivo = 1;

        return pacMan;
    }
}

tPacman* ClonaPacman(tPacman* pacman)
{
    tPosicao *posicaoNova = NULL;

    posicaoNova = ClonaPosicao(pacman->posicaoAtual);
    tPacman *PacmanClone = CriaPacman(posicaoNova);

    return PacmanClone;
}

tMovimento** ClonaHistoricoDeMovimentosSignificativosPacman(tPacman* pacman)
{
    tMovimento** clone = (tMovimento **)malloc((pacman->nMovimentosSignificativos+1) * sizeof(tMovimento *));

    if (clone != NULL)
    {
        for (int i = 0; i < pacman->nMovimentosSignificativos; i++)
            clone[i] = NULL;

        for (int i = 0; i < pacman->nMovimentosSignificativos; i++)
            clone[i] = pacman->historicoDeMovimentosSignificativos[i];

        return clone;
    }
    return NULL;
}

tPosicao* ObtemPosicaoPacman(tPacman* pacman)
{
    return pacman->posicaoAtual;
}

int EstaVivoPacman(tPacman* pacman)
{
    return pacman->estaVivo;
}

void MovePacman(tPacman* pacman, tMapa* mapa, COMANDO comando)
{
    char acaoComida[MAX_ACAO] = "pegou comida";
    char acaoParede[MAX_ACAO] = "colidiu com a parede";

    int linha = ObtemLinhaPosicao(pacman->posicaoAtual);
    int coluna = ObtemColunaPosicao(pacman->posicaoAtual);

    tPosicao *posicaoNova = NULL;

    if (comando == MOV_ESQUERDA)
    {
        pacman->nMovimentosEsquerda++;
        posicaoNova = CriaPosicao(linha, coluna-1);            
    }

    else if (comando == MOV_DIREITA)
    {
        pacman->nMovimentosDireita++;
        posicaoNova = CriaPosicao(linha, coluna+1);           
    }

    else if (comando == MOV_CIMA)
    {
        pacman->nMovimentosCima++;
        posicaoNova = CriaPosicao(linha-1, coluna);           
    }

    else if (comando == MOV_BAIXO)
    {
        pacman->nMovimentosBaixo++;
        posicaoNova = CriaPosicao(linha+1, coluna);           
    }

     if (!EncontrouParedeMapa(mapa, posicaoNova))
        {
            AtualizaPosicao(pacman->posicaoAtual, posicaoNova);  

            if(EncontrouComidaMapa(mapa, posicaoNova))
            {
                switch (comando)
                {
                    case MOV_ESQUERDA:
                        pacman->nFrutasComidasEsquerda++;
                        break;
                    
                    case MOV_DIREITA:
                        pacman->nFrutasComidasDireita++;
                        break;

                    case MOV_CIMA:
                        pacman->nFrutasComidasCima++;
                        break;

                    case MOV_BAIXO:
                        pacman->nFrutasComidasBaixo++;
                        break;
                    
                    default:
                        break;
                }

                InsereNovoMovimentoSignificativoPacman(pacman, comando, acaoComida);
                AtualizaItemMapa(mapa, posicaoNova, SPACE);
            }

            else if (ObtemItemMapa(mapa, posicaoNova) == TUNEL)
            {
                AtualizaTrilhaPacman(pacman);
                EntraTunelMapa(mapa, pacman->posicaoAtual);
            }
        }
        
        else
        {
            switch (comando)
            {
                case MOV_ESQUERDA:
                    pacman->nColisoesParedeEsquerda++;
                    break;
                
                case MOV_DIREITA:
                    pacman->nColisoesParedeDireita++;
                    break;

                case MOV_CIMA:
                    pacman->nColisoesParedeCima++;
                    break;

                case MOV_BAIXO:
                    pacman->nColisoesParedeBaixo++;
                    break;
                
                default:
                    break;
            }
            InsereNovoMovimentoSignificativoPacman(pacman, comando, acaoParede);
        }

    if (posicaoNova != NULL)
        DesalocaPosicao(posicaoNova);

    AtualizaTrilhaPacman(pacman);
}

void CriaTrilhaPacman(tPacman* pacman, int nLinhas, int nColunas)
{
    /*
    Crio a trilha atribuindo em todas as posições dela -1, pois depois (na hora de imprimir) eu vejo se é -1, caso seja, eu imprimo #(parede) ao invés do número, então por isso atrbuo um número negativo.
    */

    if (pacman->trilha == NULL)
    {
        pacman->nLinhasTrilha = nLinhas;
        pacman->nColunasTrilha = nColunas;
        
        pacman->trilha = (int **)calloc(nLinhas, sizeof(int *));

        for (int i = 0; i < nLinhas; i++)
            pacman->trilha[i] = (int *)calloc(nColunas, sizeof(int));

        for (int i = 0; i < nLinhas; i++)
        {
            for (int j = 0; j < nColunas; j++)
                pacman->trilha[i][j] = -1;
        }
    }
}

void AtualizaTrilhaPacman(tPacman* pacman)
{
    /*
    A atualização da trilha é feita após o Pacman se mover, pois sabendo para qual posição ele foi, eu atribuo para aquela posição o número do movimento.
    */

    int linha = ObtemLinhaPosicao(pacman->posicaoAtual);
    int coluna = ObtemColunaPosicao(pacman->posicaoAtual);
    int movimentoAtual = ObtemNumeroAtualMovimentosPacman(pacman);

    pacman->trilha[linha][coluna] = movimentoAtual;
}

void SalvaTrilhaPacman(tPacman* pacman)
{
    FILE* pTrilha = fopen("trilha.txt", "w");

    for (int i = 0; i < pacman->nLinhasTrilha; i++)
    {
        for (int j = 0; j < pacman->nColunasTrilha; j++)
        {
            if (j == (pacman->nColunasTrilha - 1))
            {
                if (pacman->trilha[i][j] != -1)
                    fprintf(pTrilha, "%d\n", pacman->trilha[i][j]);

                else
                    fprintf(pTrilha, "#\n");
            }
            
            else
            {
                if (pacman->trilha[i][j] != -1)
                    fprintf(pTrilha, "%d ", pacman->trilha[i][j]);

                else
                fprintf(pTrilha, "# ");                
            }
        }    
    }

    fclose(pTrilha);
}

void InsereNovoMovimentoSignificativoPacman(tPacman* pacman, COMANDO comando, const char* acao)
{
    pacman->nMovimentosSignificativos++;
    int movimentoAtual = ObtemNumeroAtualMovimentosPacman(pacman);
    int nMovimentosSignificativos = pacman->nMovimentosSignificativos;

    pacman->historicoDeMovimentosSignificativos = realloc(pacman->historicoDeMovimentosSignificativos,
                                                          nMovimentosSignificativos * sizeof(tMovimento *));

    pacman->historicoDeMovimentosSignificativos[nMovimentosSignificativos - 1] = CriaMovimento(movimentoAtual, comando, acao);
}

void MataPacman(tPacman* pacman)
{
    pacman->estaVivo = 0;
}

void DesalocaPacman(tPacman* pacman)
{
    if (pacman != NULL)
    {
        DesalocaPosicao(pacman->posicaoAtual);

        if(pacman->historicoDeMovimentosSignificativos != NULL)
            free(pacman->historicoDeMovimentosSignificativos);

        if (pacman->trilha != NULL)
        {
            for (int i = 0; i < pacman->nLinhasTrilha; i++)
                free(pacman->trilha[i]);

            free(pacman->trilha);
        }

        free(pacman);
    }       
}

int ObtemNumeroAtualMovimentosPacman(tPacman* pacman)
{
    int nAtualMovimentos = pacman->nMovimentosBaixo + pacman->nMovimentosCima + pacman->nMovimentosDireita + pacman->nMovimentosEsquerda;

    return nAtualMovimentos;
}

int ObtemNumeroMovimentosSemPontuarPacman(tPacman* pacman)
{
    int nTotalFrutas = ObtemPontuacaoAtualPacman(pacman);

    int nMovimentosSemPontuar = ObtemNumeroAtualMovimentosPacman(pacman) - nTotalFrutas;

    return nMovimentosSemPontuar;
}

int ObtemNumeroColisoesParedePacman(tPacman* pacman)
{
    int nColisoes = pacman->nColisoesParedeBaixo + pacman->nColisoesParedeCima + pacman->nColisoesParedeDireita + pacman->nColisoesParedeEsquerda;

    return nColisoes;
}

int ObtemNumeroMovimentosBaixoPacman(tPacman* pacman)
{
    return pacman->nMovimentosBaixo;
}

int ObtemNumeroFrutasComidasBaixoPacman(tPacman* pacman)
{
    return pacman->nFrutasComidasBaixo;
}

int ObtemNumeroColisoesParedeBaixoPacman(tPacman* pacman)
{
    return pacman->nColisoesParedeBaixo;
}

int ObtemNumeroMovimentosCimaPacman(tPacman* pacman)
{
    return pacman->nMovimentosCima;
}

int ObtemNumeroFrutasComidasCimaPacman(tPacman* pacman)
{
    return pacman->nFrutasComidasCima;
}

int ObtemNumeroColisoesParedeCimaPacman(tPacman* pacman)
{
    return pacman->nColisoesParedeCima;
}

int ObtemNumeroMovimentosEsquerdaPacman(tPacman* pacman)
{
    return pacman->nMovimentosEsquerda;
}

int ObtemNumeroFrutasComidasEsquerdaPacman(tPacman* pacman)
{
    return pacman->nFrutasComidasEsquerda;
}

int ObtemNumeroColisoesParedeEsquerdaPacman(tPacman* pacman)
{
    return pacman->nColisoesParedeEsquerda;
}

int ObtemNumeroMovimentosDireitaPacman(tPacman* pacman)
{
    return pacman->nMovimentosDireita;
}

int ObtemNumeroFrutasComidasDireitaPacman(tPacman* pacman)
{
    return pacman->nFrutasComidasDireita;
}

int ObtemNumeroColisoesParedeDireitaPacman(tPacman* pacman)
{
    return pacman->nColisoesParedeDireita;
}

int ObtemNumeroMovimentosSignificativosPacman(tPacman* pacman)
{
    return pacman->nMovimentosSignificativos;
}

int ObtemPontuacaoAtualPacman(tPacman* pacman)
{
    int pontuacaoAtual = ObtemNumeroFrutasComidasBaixoPacman(pacman) + ObtemNumeroFrutasComidasCimaPacman(pacman) + ObtemNumeroFrutasComidasDireitaPacman(pacman) + ObtemNumeroFrutasComidasEsquerdaPacman(pacman);

    return pontuacaoAtual;
}