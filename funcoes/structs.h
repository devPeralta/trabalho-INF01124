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
#define HASHSIZE 20000

struct DataItem {
   int sofifaid;   
   int qtdRating;
   float somaRating;
   float avgRating;
};

struct DataItem* hashArray[HASHSIZE]; 
struct DataItem* dummyItem;
struct DataItem* item;

struct lista {
 char dados[150];
 int list_sofifaid;
 struct lista* prox;
};
typedef struct lista Lista;

struct trie {
    struct trie *children[ALPHABET_SIZE];
    int *trie_sofifaid;
    float *trie_avgrating;
    int *trie_qtdrating;
    bool end_of_word;
};