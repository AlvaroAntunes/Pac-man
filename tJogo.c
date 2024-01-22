#include <stdio.h>

#include "tJogo.h"

tJogo AtualizaOEstadoDoJogo(tJogo jogo, tPacman *clonePacman, COMANDO comando)
{
    /*
    Como eu movimento somente a posição do Pacman e do fantasma, eu tenho que ter essa função para de fato fazer a movimentação mudando a posição deles no mapa do jogo. Como no código eles não podem se mover ao mesmo tempo, escolho primeiro movimentar os fantasmas (no loop logo abaixo) e a partir disso eu uso a lógica para movimentar o Pacman com todas as verificações que precisam ser feitas.
    */

    char acaoFantasma[MAX_ACAO] = "fim de jogo por encostar em um fantasma";

    for (int i = 0; i < ObtemQuantidadeDeFantasmas(jogo.fantasmas); i++)
        AtualizaItemMapa(jogo.mapaJogo, ObtemPosicaoFantasma(jogo.fantasmas[i]), ObtemTipoFantasma(jogo.fantasmas[i]));

    if (EhFantasma(jogo.mapaJogo, ObtemPosicaoPacman(jogo.Pacman)))
    {
        if (!EhFantasma(jogo.mapaJogo, ObtemPosicaoPacman(clonePacman)))
            VerificaItemAnterior(jogo.mapaJogo, jogo.mapaAuxiliar, ObtemLinhaPosicao(ObtemPosicaoPacman(clonePacman)),
                                 ObtemColunaPosicao(ObtemPosicaoPacman(clonePacman)));

        InsereNovoMovimentoSignificativoPacman(jogo.Pacman, comando, acaoFantasma);
        MataPacman(jogo.Pacman);
    }

    else if (EhFantasma(jogo.mapaJogo, ObtemPosicaoPacman(clonePacman)))
    {
        char tipo = ObtemItemMapa(jogo.mapaJogo, ObtemPosicaoPacman(clonePacman));

        if (EncontrouParedeMapa(jogo.mapaJogo, ObtemPosicaoPacman(jogo.Pacman)))
        {
            InsereNovoMovimentoSignificativoPacman(jogo.Pacman, comando, acaoFantasma);
            MataPacman(jogo.Pacman);
        }
        
        else if (ObtemItemMapa(jogo.mapaEspelho, ObtemPosicaoPacman(jogo.Pacman)) == tipo)
        {
            InsereNovoMovimentoSignificativoPacman(jogo.Pacman, comando, acaoFantasma);
            MataPacman(jogo.Pacman);
        }

        else
            AtualizaItemMapa(jogo.mapaJogo, ObtemPosicaoPacman(jogo.Pacman), PACMAN);
    }

    else
    {
        VerificaItemAnterior(jogo.mapaJogo, jogo.mapaAuxiliar, ObtemLinhaPosicao(ObtemPosicaoPacman(clonePacman)),
                            ObtemColunaPosicao(ObtemPosicaoPacman(clonePacman)));

        if (EncontrouComidaMapa(jogo.mapaAuxiliar, ObtemPosicaoPacman(jogo.Pacman)))
            AtualizaItemMapa(jogo.mapaAuxiliar, ObtemPosicaoPacman(jogo.Pacman), SPACE);

        AtualizaItemMapa(jogo.mapaJogo, ObtemPosicaoPacman(jogo.Pacman), PACMAN);
    }

    return jogo;
}

void PreencheInicializacao(tJogo jogo)
{
    FILE* pInicializacao = fopen("inicializacao.txt", "w");

    for (int i = 0; i < ObtemNumeroLinhasMapa(jogo.mapaJogo); i++)
    {
        for (int j = 0; j < ObtemNumeroColunasMapa(jogo.mapaJogo); j++)
        {
            tPosicao *posicao = CriaPosicao(i, j);
            fprintf(pInicializacao, "%c", ObtemItemMapa(jogo.mapaJogo, posicao));
            DesalocaPosicao(posicao);
        }
        fprintf(pInicializacao, "\n");
    }

    int linhaPacman = ObtemLinhaPosicao(ObtemPosicaoPacman(jogo.Pacman));
    int colunaPacman = ObtemColunaPosicao(ObtemPosicaoPacman(jogo.Pacman));

    fprintf(pInicializacao, "Pac-Man comecara o jogo na linha %d e coluna %d", linhaPacman+1, colunaPacman+1);

    fclose(pInicializacao);
}

void AtualizaMapaEspelho(tMapa* mapa, tMapa* mapaEspelho)
{
    /*
    O mapa espelho sempre está na "versão" anterior do mapa original do jogo. Isso acontece pois pode ter o caso do fantasma e Pacman se atravessarem, então o fantasma não vai necessariamente para a posição do Pacman, então tenho que fazer uma outra verificação, por esse motivo uso o mapa espelho.
    */

    for (int i = 0; i < ObtemNumeroLinhasMapa(mapa); i++)
    {
        for (int j = 0; j < ObtemNumeroColunasMapa(mapa); j++)
        {
            tPosicao *posicao = CriaPosicao(i, j);
            AtualizaItemMapa(mapaEspelho, posicao, ObtemItemMapa(mapa, posicao));
            DesalocaPosicao(posicao);
        }
    }
}

void PreencheRanking(tPacman* pacman)
{
    /*
    Aqui eu defino um número para cada movimento e preencho tudo referente ao que irá ser preciso para fazer o ranking, após isso, eu faço a ordenação do ranking e depois faço a impressão do ranking ordenado no arquivo.
    */

    tRanking dadosRanking[NUM_MOVIMENTOS];

    dadosRanking[MOV_A].movimento = 'a';
    dadosRanking[MOV_A].qtdColisoes = ObtemNumeroColisoesParedeEsquerdaPacman(pacman);
    dadosRanking[MOV_A].qtdFrutas = ObtemNumeroFrutasComidasEsquerdaPacman(pacman);
    dadosRanking[MOV_A].qtdMovimentos = ObtemNumeroMovimentosEsquerdaPacman(pacman);

    dadosRanking[MOV_D].movimento = 'd';
    dadosRanking[MOV_D].qtdColisoes = ObtemNumeroColisoesParedeDireitaPacman(pacman);
    dadosRanking[MOV_D].qtdFrutas = ObtemNumeroFrutasComidasDireitaPacman(pacman);
    dadosRanking[MOV_D].qtdMovimentos = ObtemNumeroMovimentosDireitaPacman(pacman);

    dadosRanking[MOV_S].movimento = 's';
    dadosRanking[MOV_S].qtdColisoes = ObtemNumeroColisoesParedeBaixoPacman(pacman);
    dadosRanking[MOV_S].qtdFrutas = ObtemNumeroFrutasComidasBaixoPacman(pacman);
    dadosRanking[MOV_S].qtdMovimentos = ObtemNumeroMovimentosBaixoPacman(pacman);

    dadosRanking[MOV_W].movimento = 'w';
    dadosRanking[MOV_W].qtdColisoes = ObtemNumeroColisoesParedeCimaPacman(pacman);
    dadosRanking[MOV_W].qtdFrutas = ObtemNumeroFrutasComidasCimaPacman(pacman);
    dadosRanking[MOV_W].qtdMovimentos = ObtemNumeroMovimentosCimaPacman(pacman);

    OrdenaRanking(dadosRanking);
    FILE* pRanking = fopen("ranking.txt", "w");

    for (int i = 0; i < NUM_MOVIMENTOS; i++)
        fprintf (pRanking, "%c,%d,%d,%d\n", dadosRanking[i].movimento, dadosRanking[i].qtdFrutas, dadosRanking[i].qtdColisoes,  
                                            dadosRanking[i].qtdMovimentos);

    fclose(pRanking);
}

void OrdenaRanking(tRanking* dadosRanking)
{
    
    //Na ordenação eu uso cada ordem de precedência para fazer a verificação e ordenar de forma correta.
    
    tRanking aux;

    for (int i = 0; i < NUM_MOVIMENTOS; i++) {
        for (int j = i + 1; j < NUM_MOVIMENTOS; j++) {

            if (dadosRanking[j].qtdFrutas > dadosRanking[i].qtdFrutas) {
                aux = dadosRanking[i];
                dadosRanking[i] = dadosRanking[j];
                dadosRanking[j] = aux;
            }

            else if (dadosRanking[j].qtdFrutas == dadosRanking[i].qtdFrutas) {

                if (dadosRanking[j].qtdColisoes < dadosRanking[i].qtdColisoes) {
                    aux = dadosRanking[i];
                    dadosRanking[i] = dadosRanking[j];
                    dadosRanking[j] = aux;
                }

                else if (dadosRanking[j].qtdColisoes == dadosRanking[i].qtdColisoes) {
                    if (dadosRanking[j].qtdMovimentos > dadosRanking[i].qtdMovimentos) {
                        aux = dadosRanking[i];
                        dadosRanking[i] = dadosRanking[j];
                        dadosRanking[j] = aux;
                    }

                    else if (dadosRanking[j].qtdMovimentos == dadosRanking[i].qtdMovimentos) {
                        if (dadosRanking[j].movimento < dadosRanking[i].movimento) {
                            aux = dadosRanking[i];
                            dadosRanking[i] = dadosRanking[j];
                            dadosRanking[j] = aux;
                        }
                    }
                }
            }
        }
    }
}

void DesalocaJogo(tJogo jogo, int nFantasmas)
{
    DesalocaMapa(jogo.mapaJogo);
    DesalocaMapa(jogo.mapaAuxiliar);
    DesalocaMapa(jogo.mapaEspelho);
    DesalocaJogador(jogo.Pacman);
    DesalocaFantasmas(jogo.fantasmas, nFantasmas);
}

void DesalocaJogador(tPacman* pacman)
{
    if (pacman != NULL)
    {
        DesalocaPosicao(pacman->posicaoAtual);

        if (pacman->historicoDeMovimentosSignificativos != NULL)
        {
            for (int i = 0; i < ObtemNumeroMovimentosSignificativosPacman(pacman); i++)
                DesalocaMovimento(pacman->historicoDeMovimentosSignificativos[i]);

            free(pacman->historicoDeMovimentosSignificativos);
        }

        if (pacman->trilha != NULL)
        {
            for (int i = 0; i < pacman->nLinhasTrilha; i++)
                free(pacman->trilha[i]);

            free(pacman->trilha);
        }

        free(pacman);
    }       
}