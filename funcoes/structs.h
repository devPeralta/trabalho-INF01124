#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#define FILEMAXNOME 25
#define MAXDADOS 200
#define MAXRATINGS 24188078
#define MAXPLAYERS 18944
#define MAXTAGS 364950

struct lista {
 char dados[150];
 struct lista* prox;
};
typedef struct lista Lista;



