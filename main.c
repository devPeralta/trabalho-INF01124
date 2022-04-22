#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <time.h>
#include <string.h>
#include <ctype.h>
#include "funcoes/functions.c"
#define ALPHABET_SIZE 30
#define FILEMAXNOME 25
#define MAXRATINGS 24188078
#define MAXPLAYERS 18945
#define MAXTAGS 364950

int main()
{
    FILE *file_minirating, *file_players21, *file_players, *file_rating, *file_tags;
    char minirating[FILEMAXNOME] = "minirating.csv", players21[FILEMAXNOME] = "players_21.csv", players[FILEMAXNOME] = "players.csv", rating[FILEMAXNOME] = "rating.csv", tags[FILEMAXNOME] = "tags.csv";
    Lista *lista_minirating, *lista_players21, *lista_players, *lista_tags, *lista_rating;
    int ret = 0;
    struct trie * root = NULL;
    struct trie * trie = NULL;
    char word[100] = {0};
    
    lista_players = inicializaLista(); // inicializa uma lista para armazenar os dados dos jogadores
    lista_players = saveFile(file_players, players, lista_players); // salva os dados dos jogadores em lista_players
   
    ret = trie_new(&root);

    for(int i=0; i<MAXPLAYERS; i++) {
        le_player(lista_players->dados, word);
        strcpy(word, minuscula(word));
        ret = trie_insert(root, word, strnlen(word, 100));
        if (-1 == ret) {
            fprintf(stderr, "Could not insert word into trie\n");
            exit(1);
        }
        lista_players = lista_players->prox;
    }

    while (1) {
        printf("Player prefix: ");
        gets(word);

        printf("\n==========================================================\n");
        printf("\n********************* Players List ********************\n");

        ret = trie_search(root, word, strnlen(word, 100), &trie);
        if (-1 == ret) {
            printf("No results\n");
            continue;
        }

        trie_print(trie, word, strnlen(word, 100));

        printf("\n==========================================================\n");
    }


    return 0;
}