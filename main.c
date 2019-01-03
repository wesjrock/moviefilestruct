/*
Trabalho de Organizacao de Arquivos - Parte 1
Prof(a): Cristina Dutra de Aguiar Ciferri
Estagiário PAE: Rayner de Melo Pires

ICMC USP São Carlos

Alunos (Turma A):

Gabriel Pinheiro de Carvalho (7960727)
Jorge Luiz da Silva Vilaça (9066491)
Raul Procopio (9277200)
Wesley Tiozzo (8077925)

*/

#include <stdio.h>
#include <stdlib.h>
#include "operacoes_arquivo.h"
#include "gerador_dados.h"



/** struct Registro:
    Estrutura para armazenar um registro em memória
    Neste programa, um registro é carregado em memória
    utilizando essa estrutura, printado, e a memória é liberada
**/
typedef struct reg {
    int id;
    int ano;
    int duracao;
    char* titulo;
    char* descr;
    char* pais;
    char* genero;
} Registro;

/************************************* Protótipos de Funções *******************************************/

/** Libera a memória utilizada por um registro **/
void freeReg(Registro* reg);

/** Retorna o n-ésimo registro do arquivo, numa estrutura de memória do tipo Registro */
Registro* getReg(int id, FILE* arq_dados);

/** Lista todos os registros */
void listAllRegs(FILE* arq_dados);

/** Printa um registro com todos os seus campos */
void printReg(int regID, FILE* arq_dados);


/************************************* MAIN *******************************************/
int main()
{
     // Abre o arquivo de dados para leitura
    FILE* arq_dados = NULL;

    arq_dados = gerarArqDados();


    // Verifica se o arquivo foi aberto com sucesso
    if(arq_dados == NULL)
    {
        printf("Nao foi possivel localizar o arquivo de dados\n");
        printf("(Certifique-se que ele se encontra na pasta do executavel)\n");
        exit(1);
    }

    int command; //Variavel associada a escolha da funcao
    int index; //Variavel associada ao indice do filme buscado



    while (command != 3){
        printf("\nO que deseja fazer agora?\n");
        printf("1) Listar todos os filmes\n");
        printf("2) Buscar filme\n");
        printf("3) Sair\n\n");
        scanf("%d", &command);

        switch (command){
            case 1:
                listAllRegs(arq_dados);
                //Listar filmes
                break;

            case 2:
                printf("Digite o ID do filme a ser buscado (0 - 99):\nR:");
                scanf("%d", &index);
                printReg(index, arq_dados);
                //Buscar filme
                break;

            default:
                //Sair
                break;
        }
    }
    fclose(arq_dados);
    return 0;
}

/************************************* Implementação das Funções *******************************************/

/** Lista todos os registros do arquivo de dados */
void listAllRegs(FILE* arq_dados)
{
    int i = 0;
    // Para cada um dos 100 registros,
    for (i = 0; i < N_REGS; i++)
    {
        // Printa um registro na tela
        printReg(i,arq_dados);
    }
}

/** Printa um registro com todos os seus campos */
void printReg(int regID, FILE* arq_dados)
{
    // Resgata um registro e armazena num registro temporário
    Registro* reg = getReg(regID,arq_dados);

    // Printa o registro
    printf("\nRegistro[%d]:\n", reg->id);
    printf("ID: %d\n", reg->id);
    printf("Titulo: %s\n", reg->titulo);
    printf("Descricao: %s\n", reg->descr);
    printf("Producao: %s\n", reg->pais);
    printf("Ano Lancamento: %d\n", reg->ano);
    printf("Duracao: %d\n", reg->duracao);
    printf("Genero: %s\n", reg->genero);

    // Libera a memória do registro temporário utilizado para printar o registro atual
    freeReg(reg);
}

/** Retorna o n-ésimo registro do arquivo, numa estrutura de memória do tipo Registro */
Registro* getReg(int id, FILE* arquivo)
{
    if (arquivo == NULL)
    {
        printf("Arquivo nao aberto, abra o arquivo antes de usar a funcao getReg(int id, FILE* arquivo)\n");
        exit(1);
    }

    Registro* reg = (Registro*)malloc(sizeof(Registro)); // Registro temporario que será retornado preenchido no final da função
    char c;                 // Utilizado para ler cada byte do arquivo
    int encontrado = 0;     // Flag que indica que o registro pesquisado foi encontrado ou não
    int idLido = -1;        // Armazenará o ID lido no arquivo
    int bkpPtrArq = ftell(arquivo); // Faz um backup da posição atual do ponteiro do arquivo para poder voltar depois

    rewind(arquivo); // Rebubina o arquivo de dados para começar a pesquisa do começo

    // Verifica se o primeiro ID do arquivo não é o que estamos procurando

    if(fread(&idLido,sizeof(int),1,arquivo) == 0)
    {
        printf("falha ao ler arquivo de dados\n");
        exit(1);
    }

    if(idLido == id)
    {
        encontrado = 1;
    }

    // Equanto não chega no fim do arquivo
    while(fread(&c,1,1,arquivo) && encontrado == 0)
    {
        // Se o byte lido for o simbolo de termino de registro
        if(c == '#')
        {
            // Informa que passamos para o próximo registro
            idLido = nextInt(arquivo);

            if(idLido == id)
            {
                encontrado = 1;
                break;
            }
        }
    }

    if(idLido == -1)
    {
        printf("Nenhum ID encontrado no arquivo\n");
        exit(1);
    }

    if(encontrado == 0)
    {
        printf("Registro %d nao encontrado\n", id);
        exit(1);
    }

    reg->id = idLido;         // Temorariamente atribui o id aleatorio fornecido ao ID desse registro (será substrituido depois na função carregaRegistros)
    reg->ano = nextInt(arquivo);        // Lê os primeiros 4 bytes e atribui à variavel int ano
    reg->duracao = nextInt(arquivo);    // Faz o mesmo pra variavel duração
    reg->titulo = arqTok(arquivo,'|');  // Copia tudo que vem antes do marcador de fim de campo, na variável titulo
    reg->descr = arqTok(arquivo,'|');   // Faz o mesmo pros outros campos
    reg->pais = arqTok(arquivo,'|');
    reg->genero = arqTok(arquivo,'|');


    // Restaura a posição original do ponteiro do arquivo
    fseek(arquivo,bkpPtrArq,SEEK_SET);

    return reg;
}

/** Libera a memória utilizada por um registro **/
void freeReg(Registro* reg)
{
    free(reg->titulo);
    free(reg->descr);
    free(reg->pais);
    free(reg->genero);
    free(reg);
}


