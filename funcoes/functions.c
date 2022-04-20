#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include "structs.h"
#define FILEMAXNOME 25
#define MAXDADOS 200
#define MAXRATINGS 24188078
#define MAXPLAYERS 18944
#define MAXTAGS 364950

Lista *inicializaLista()
{
    return NULL;
}

Lista *insereLista(Lista *l, char dado[MAXDADOS]){

    Lista *novo = (Lista *)malloc(sizeof(Lista));
    strcpy(novo->dados, dado);
    novo->prox = l;
    return novo;
}

Lista *saveFile(FILE *file, char nomeArquivo[FILEMAXNOME], Lista *l)
{
    char teste[MAXDADOS];
    double cont = 0.0;

    char diretorio[FILEMAXNOME] = "";
    strcat(diretorio, "csvFiles/");
    strcat(diretorio, nomeArquivo);

    file = fopen(diretorio, "r");
    if (file == NULL)
    {
        perror("Nao foi possivel abrir o arquivo.");
        exit(1);
    }

    char line[200];

    while (fgets(line, sizeof(line), file))
    {
        char *token;

        token = strtok(line, "");

        while (token != NULL)
        {
            strcpy(teste,token);
            l = insereLista(l, teste);
            cont = cont + 1;
            if(cont>12459999){ // max=12461413
            printf("%.lf: %s",cont, l->dados);
            }
            token = strtok(NULL, "");
        }
        
        
    }
    return l;
}