#ifndef GERADOR_DADOS_H
#define GERADOR_DADOS_H
#include <stdlib.h>
#include <stdio.h>
#include "operacoes_arquivo.h"
#include "utilitarios.h"
/** Define o numero total de registros no arquivo de dados */
#define N_REGS 100

/** Copia o ultimo n�mero lido no arquivo de orgigem (string) no arquivo destino, convertido pra int */
void copiarUltimoIntLido(FILE* arq_origem,FILE* arq_destino, int nDigitos);

/** Copia os "n" bytes anteriores � posi��o atual do ponteiro de arquivo de origem, no arquivo de destino */
void copiarUltimaStringLida(FILE* arq_origem,FILE* arq_destino, int n);

/** Avan�a o ponteiro do arquivo at� a posi��o que come�a o primeiro campo do filme n no arquivo de filmes */
void fSeekFilme(int n, FILE* arq_filme);

/** Escolhe 100 filmes aleat�rios dentro todos os filmes presentes no arquivo de filmes,
    atribui IDs aleat�rios a esses filmes e escreve no arquivo de dados.  */
FILE* gerarArqDados();

#endif // GERADOR_DADOS_H
