#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <stdbool.h>
#include "functions.c"
#define FILEMAXNOME 25
#define MAXDADOS 200

Lista *inicializaLista();
Lista *insereLista(Lista *l, char dado[MAXDADOS]);
Lista *saveFile(FILE *file, char nomeArquivo[FILEMAXNOME], Lista *l);
void le_player(char dado[MAXDADOS], char *word);
int trie_new (struct trie **trie);
int trie_insert (struct trie *trie,char *word, unsigned word_len);
void trie_create(Lista *lista_players, struct trie *trie);
int trie_search(struct trie *trie, char *word, unsigned word_len,struct trie **result);
void trie_print (struct trie *trie, char prefix[], unsigned prefix_len);
