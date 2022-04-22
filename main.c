#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <time.h>
#include <string.h>
#include <ctype.h>
#include "funcoes/functions.h"
#define FILEMAXNOME 25
#define MAXRATINGS 24188078
#define MAXPLAYERS 18944
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
    if (-1 == ret) {
        printf("Nao foi possivel criar a trie\n");
        exit(1);
    }
    trie_create(lista_players, root);

    while (1) {
        printf("Player prefix: ");
        gets(word);

        printf("\n********************* Players List ********************\n");

        ret = trie_search(root, word, strnlen(word, 100), &trie);
        if (-1 == ret) {
            printf("Nao encontrado\n");
        }
        else{
            trie_print(trie, word, strnlen(word, 100));
        }
    }


    return 0;
}