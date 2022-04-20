#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include "functions.c"
#define FILEMAXNOME 25
#define MAXDADOS 200
#define MAXRATINGS 24188078
#define MAXPLAYERS 18944
#define MAXTAGS 364950

Lista *inicializaLista();
Lista *insereLista(Lista *l, char dado[MAXDADOS]);
Lista *saveFile(FILE *file, char nomeArquivo[FILEMAXNOME], Lista *l);