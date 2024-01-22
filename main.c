/*
Implementação de um jogo Pacman com os conceitos de ponteiros, TAD e alocação dinâmica de memória vistos na disciplina de Programação 2.
Álvaro Antunes de Oliveira
05/11/2023
*/

#include <stdio.h>
#include <stdlib.h>

#include "constantes.h"
#include "tJogo.h"

tJogo InicializaJogo(char *argv);
int RealizaJogo(tJogo jogo);
void FinalizouPartida (int resultado, int pontuacao);
void PreencheResumo(tPacman* pacman);
void PreencheEstatisticas(tPacman* pacman);

int main (int argc, char* argv[])
{
    if (argc <= CAMINHO_DIR)
    {
        printf("ERRO: O diretório de arquivos de configuração nao foi informado\n");
        return ERROR;
    }

    tJogo jogo;
    jogo = InicializaJogo(argv[CAMINHO_DIR]);
    RealizaJogo(jogo);
    DesalocaJogo(jogo, ObtemQuantidadeDeFantasmas(jogo.fantasmas));

    return 0;
}

tJogo InicializaJogo(char *diretorio)
{
    /*
    Na inicialização do jogo, já faço toda a preparação para o jogo (crio três mapas que irão me ajudar na lógica do programa, sendo um desses mapas o mapa original do jogo. Já verifico também quais fantasmas existem e faço a alocação deles e, por fim, já vejo qual é a posição inicial do Pacman). Com essas informações do jogo, já preencho o arquivo de inicialização do jogo.
    */

    tJogo jogo;
    char caminhoMapa[MAX_DIR];
    strcpy(caminhoMapa, diretorio);

    jogo.mapaJogo = CriaMapa(caminhoMapa);
    jogo.mapaAuxiliar = CriaMapa(caminhoMapa);
    jogo.mapaEspelho = CriaMapa(caminhoMapa);

    jogo.fantasmas = VerificaExistenciaDosFantasmas(jogo.mapaJogo);
    
    tPosicao *posicaoInicialPacMan = ObtemPosicaoItemMapa(jogo.mapaJogo, PACMAN);
    jogo.Pacman = CriaPacman(posicaoInicialPacMan);

    PreencheInicializacao(jogo);

    return jogo;
}

int RealizaJogo(tJogo jogo)
{
    /*
    Nessa função, faço toda a realização do jogo. Desde ler todas as jogadas do usuário até finalizar o jogo e preencher todos os arquivos necessários. O jogo acaba em três situações: se o Pacman morrer, se o número de frutas que o Pacman comer for igual ao número de frutas iniciais do jogo ou se o número de jogadas acabar.
    */

    int numMovimentos = 1, pontuacao = 0;
    char jogadaAtual;

    tPacman* clonePacman = NULL;
    CriaTrilhaPacman(jogo.Pacman, ObtemNumeroLinhasMapa(jogo.mapaJogo), ObtemNumeroColunasMapa(jogo.mapaJogo));
    AtualizaTrilhaPacman(jogo.Pacman);

    int nTotalFantasmas = ObtemQuantidadeDeFantasmas(jogo.fantasmas);
    COMANDO comando;

    while (numMovimentos <= ObtemNumeroMaximoMovimentosMapa(jogo.mapaJogo))
    {
        scanf("%c%*c", &jogadaAtual);
        clonePacman = ClonaPacman(jogo.Pacman);

        switch (jogadaAtual)
        {
            case 'a':
                comando = MOV_ESQUERDA;
                break;
            
            case 'd':
                comando = MOV_DIREITA;
                break;

            case 'w':
                comando = MOV_CIMA;
                break;
            
            case 's':
                comando = MOV_BAIXO;
                break;
            
            default:
                break;
        }

        MoveFantasmas(jogo.mapaJogo, jogo.mapaAuxiliar, jogo.fantasmas, nTotalFantasmas);
        MovePacman(jogo.Pacman, jogo.mapaAuxiliar, comando);

        jogo = AtualizaOEstadoDoJogo(jogo, clonePacman, comando);

        printf("Estado do jogo apos o movimento '%c':\n", jogadaAtual);
        ImprimeOMapa(jogo.mapaJogo);
        AtualizaMapaEspelho(jogo.mapaJogo, jogo.mapaEspelho);

        pontuacao = ObtemPontuacaoAtualPacman(jogo.Pacman);
        printf("Pontuacao: %d\n\n", pontuacao);

        numMovimentos++;

        if(clonePacman != NULL)
            DesalocaPacman(clonePacman);

        if (!EstaVivoPacman(jogo.Pacman))
        {
            FinalizouPartida(GAME_OVER, pontuacao);
            break;
        }

        else if (ObtemPontuacaoAtualPacman(jogo.Pacman) == ObtemQuantidadeFrutasIniciaisMapa(jogo.mapaJogo))
        {
            FinalizouPartida(WIN, pontuacao);
            break;
        }

        else if (numMovimentos > ObtemNumeroMaximoMovimentosMapa(jogo.mapaJogo))
        {
            FinalizouPartida(GAME_OVER, pontuacao);
            break;
        }
    }

    PreencheRanking(jogo.Pacman);
    SalvaTrilhaPacman(jogo.Pacman);
    PreencheResumo(jogo.Pacman);
    PreencheEstatisticas(jogo.Pacman);

    return SUCESS;
}

void FinalizouPartida (int resultado, int pontuacao) {

    //Se a partida acabou com o jogador vencendo, mando WIN(1) como parâmetro para resultado, senão mando GAME_OVER(0)

    if (resultado) {
        printf ("Voce venceu!\n");
        printf ("Pontuacao final: %d\n", pontuacao);
    }
    else {
        printf ("Game over!\n");
        printf ("Pontuacao final: %d\n", pontuacao);
    }
}

void PreencheResumo(tPacman* pacman)
{
    /*
    Como na struct tPacman eu tenho um campo que guarda todos os movimentos significativos, basta fazer um loop para passar por todos esses movimentos e imprimir as informações de cada movimento.
    */

    char caractere;
    FILE* pResumo = fopen("resumo.txt", "w");

    for (int i = 0; i < ObtemNumeroMovimentosSignificativosPacman(pacman); i++)
    {
        switch (ObtemComandoMovimento(pacman->historicoDeMovimentosSignificativos[i]))
        {
            case MOV_CIMA:
                caractere = MOVIMENTO_CIMA;
                break;
            
            case MOV_BAIXO:
                caractere = MOVIMENTO_BAIXO;
                break;

            case MOV_ESQUERDA:
                caractere = MOVIMENTO_ESQUERDA;
                break;

            case MOV_DIREITA:   
                caractere = MOVIMENTO_DIREITA;
                break;   
        }

        fprintf (pResumo, "Movimento %d (%c) %s\n", ObtemNumeroMovimento(pacman->historicoDeMovimentosSignificativos[i]),
                                                    caractere, ObtemAcaoMovimento(pacman->historicoDeMovimentosSignificativos[i]));
    }

    fclose(pResumo);
}

void PreencheEstatisticas(tPacman* pacman)
{
    /*
    Assim como no resumo, o meu Pacman vai armazenar todas as informações que irei precisar para gerar as estatísticas, então é basicamente obter cada informação do Pacman.
    */

    FILE* pEstatisticas = fopen("estatisticas.txt", "w");

    fprintf (pEstatisticas, "Numero de movimentos: %d\n", ObtemNumeroAtualMovimentosPacman(pacman));
    fprintf (pEstatisticas, "Numero de movimentos sem pontuar: %d\n", ObtemNumeroMovimentosSemPontuarPacman(pacman));
    fprintf (pEstatisticas, "Numero de colisoes com parede: %d\n", ObtemNumeroColisoesParedePacman(pacman));
    fprintf (pEstatisticas, "Numero de movimentos para baixo: %d\n", ObtemNumeroMovimentosBaixoPacman(pacman));
    fprintf (pEstatisticas, "Numero de movimentos para cima: %d\n", ObtemNumeroMovimentosCimaPacman(pacman));
    fprintf (pEstatisticas, "Numero de movimentos para esquerda: %d\n", ObtemNumeroMovimentosEsquerdaPacman(pacman));
    fprintf (pEstatisticas, "Numero de movimentos para direita: %d\n", ObtemNumeroMovimentosDireitaPacman(pacman));

    fclose(pEstatisticas);
}