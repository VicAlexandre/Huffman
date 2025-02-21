#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//O unsigned char servirá para representar o byte
typedef unsigned char byte;

/*  ÁRVORE DE HUFFMAN
    freq = int
    ch = byte
    left, right = tree*
*/
typedef struct _nodearvore{
    void    *freq,
            *ch,
            *left,
            *right;
} tree;

// FILA DE PRIORIDADE
// node = tree / next = node_pq
typedef struct _priority_queue_node{
    void    *node,
            *next;
} node_pq;

//Função que scaneia o arquivo e armazena no array "bytes" as frequências de cada byte scaneado
void buscando_frequencias(FILE *entrada, unsigned int *bytes)
{
    byte b;
    while(fread(&b, 1, 1, entrada))
        bytes[(byte)b]++;
    rewind(entrada); //void rewind(FILE *stream) = volta a stream FILE *entrada para o começo do arquivo
}

//Função que exibe uma mensagem de erro caso o programa não consiga localizar um arquivo e em seguida o encerra
void error_file()
{
    printf("--------------------\nErro ao encontrar o arquivo, por favor verifique se o arquivo esta no diretorio correto\n--------------------");
    exit(EXIT_SUCCESS);
}

//TO DO: FAZER ESSA FUNÇÃO
void comprimir(const char *entrada, const char *saida)
{
    unsigned int bytes[256] = {0};
    tree *hufftree;

    FILE *arquivo_e = fopen(entrada, "rb");
    if(!arquivo_e)
        error_file();

    FILE *arquivo_s = fopen(saida, "wb");
    if(!arquivo_s)
        error_file();
    
    buscando_frequencias(arquivo_e, bytes);
    for(int i=0; i < 256; i++)
        printf("%d\n", bytes[i]);
    
}

//TO DO: FAZER ESSA FUNÇÃO
void descomprimir(const char *entrada, const char *saida)
{
    printf("%s\n%s\n", entrada, saida);
}

//Função que printa no terminal o uso correto do programa caso tenha sido chamado de forma incorreta
void error_param()
{
    printf("--------------------\nUso invalido!\nModelo de uso: ./huffman [-c OU -d] [ARQ. DE ENTRADA] [ARQ. DE SAIDA]\n\n-c: Comprime um arquivo; ARQ. DE SAIDA deve ser .huffman\n");   
    printf("-d: Descomprime um arquivo; ARQ. DE ENTRADA deve ser .huffman\n--------------------");
}


// MAIN
// argc = inteiro que contém a quantidade de parâmetros passados para o programa
// argv[] = array de strings que contém os parâmetros passados para o programa
int main(int argc, char *argv[])
{
    if(argc < 4){
        error_param();
        return 0;
    }

    if(!strcmp("-c", argv[1])){
        if(strstr(argv[3], ".huffman"))
            comprimir(argv[2], argv[3]);
        else
            error_param();
    }

    else if (!strcmp("-d", argv[1])){
        if(strstr(argv[2], ".huffman"))
            descomprimir(argv[2], argv[3]);
        else
            error_param();
    }

    else
        error_param();
    return 0;
}