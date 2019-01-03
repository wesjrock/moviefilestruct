#ifndef OPERACOES_ARQUIVO_H
#define OPERACOES_ARQUIVO_H

#include <stdio.h>
#include <stdlib.h>

/** L� todas as letras encontradas,a partir da posi��o atual do arquivo at� um marcador qualquer, e retorna-as como uma string.*/
char* arqTok(FILE* arquivo, char marcador);

/** Retorna a quantidade total de registros no arquivo **/
int contaMarcador(FILE* arquivo, char marcador);

/** Retorna os proximos 4 bytes lidos do arquivo, como int **/
int nextInt(FILE* arquivo);


#endif // OPERACOES_ARQUIVO_H
