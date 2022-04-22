#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <stdbool.h>
#define FILEMAXNOME 25
#define MAXDADOS 200
#define MAXRATINGS 24188078
#define MAXPLAYERS 18944
#define MAXTAGS 364950
#define MAXNOMEPLAYER 100
#define MAXNUMTAGS 10
#define MAXLENTAGS 5
#define TAMPLAYERS 2000
#define ALPHABET_SIZE 30

struct lista {
 char dados[150];
 struct lista* prox;
};
typedef struct lista Lista;

struct trie {
    struct trie *children[ALPHABET_SIZE];
    bool end_of_word;
};