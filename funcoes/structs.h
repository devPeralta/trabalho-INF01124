#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <stdbool.h>
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