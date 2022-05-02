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
    int *list_sofifaid, *trieqtdrating;
    float *trieavgrating;
    
    lista_players = inicializaLista(); // inicializa uma lista encadeada para armazenar os dados dos jogadores
    lista_players = saveFile(file_players, players, lista_players); // salva os dados dos jogadores na lista
    
    saveRatings(file_minirating);
    
    ret = trie_new(&root); // cria trie
    for(int i=0; i<MAXPLAYERS; i++) { // insere "MAXPLAYERS" jogadores na trie
        le_player(lista_players->dados, word, &list_sofifaid); // salva dados do jogador em uma string auxiliar
        strcpy(word, minuscula(word)); // passa todos caracteres da string para minuscula
        
        item = search(list_sofifaid);
        if (item != NULL){
            item->avgRating = item->somaRating / item->qtdRating;
            trieqtdrating = &item->qtdRating;
            trieavgrating = &item->avgRating;
            ret = trie_insert(root, word, strnlen(word, 100), list_sofifaid, trieqtdrating, trieavgrating); // insere a string na trie
            if (-1 == ret){ // testa se conseguiu inserir na trie
            fprintf(stderr, "Could not insert word into trie\n");
            exit(1);
            }
        }
        lista_players = lista_players->prox; // passa pro proximo jogador na lista encadeada
    }
    
    while (1) {
        printf("\n\nPlayer prefix: ");
        gets(word);
        system("cls");

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
