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
    int *topN, *codigo=0, code=0;
    char consulta[150] = {0};
    char consulta_elemento[100] = {0};
    int consulta_user=0;
    char player_pos[50] = {0};
    int *list_sofifaid, *trieqtdrating;
    float *trieavgrating;
    
    lista_players = inicializaLista(); // inicializa uma lista encadeada para armazenar os dados dos jogadores
    lista_players = saveFile(file_players, players, lista_players); // salva os dados dos jogadores na lista
    
    saveRatings(file_minirating);

    ret = trie_new(&root); // cria trie
    for(int i=0; i<MAXPLAYERS; i++) { // insere "MAXPLAYERS" jogadores na trie
        le_player(lista_players->dados, word, &list_sofifaid, player_pos); // salva dados do jogador em uma string auxiliar
        strcpy(word, minuscula(word)); // passa todos caracteres da string para minuscula
        player = search(list_sofifaid);
        if (player != NULL){
            player->avgRating = player->somaRating / player->qtdRating;
            trieqtdrating = &player->qtdRating;
            trieavgrating = &player->avgRating;
            ret = trie_insert(root, word, strnlen(word, 100), list_sofifaid, trieqtdrating, trieavgrating, player_pos); // insere a string na trie
            if (-1 == ret){ // testa se conseguiu inserir na trie
            fprintf(stderr, "Nao foi possivel inserir a palavra na arvore trie\n");
            exit(1);
            }
        }
        lista_players = lista_players->prox; // passa pro proximo jogador na lista encadeada
    }
    
    while(1){
        system("cls");
        printf("$ ");
        gets(consulta);
        fflush(stdin);

        verifica_consulta(consulta, &codigo, &topN, consulta_elemento);

        code = codigo;

        switch(code){

            case 1:{
                strcpy(consulta_elemento, minuscula(consulta_elemento));
                system("cls");

                printf("\n********************* Players List ********************\n\n");

                ret = trie_search(root, consulta_elemento, strnlen(consulta_elemento, 100), &trie);
                if (-1 == ret) {
                    printf("No results\n");
                    continue;
                }

                trie_print(trie, consulta_elemento, strnlen(consulta_elemento, 100));

                printf("\n==========================================================\n");
                system("pause");
            }
            break;
            case 2:{    

                consulta_user = atoi(consulta_elemento);
                
                for(int i=0;i<20;i++){
                    
                    printf("userid=%d\tsofifaid=%d\t\tmaiorrating=%.2f\t\t", hashUser[hashCode(consulta_user, HASHSIZEUSERS)]->userid, hashUser[hashCode(consulta_user, HASHSIZEUSERS)]->sofifaid[i], hashUser[hashCode(consulta_user, HASHSIZEUSERS)]->rating[i]);
                    printf("%.6f\t", hashArray[hashCode(hashUser[hashCode(consulta_user, HASHSIZEUSERS)]->sofifaid[i], HASHSIZEPLAYER)]->avgRating);
                    printf("%d\n", hashArray[hashCode(hashUser[hashCode(consulta_user, HASHSIZEUSERS)]->sofifaid[i], HASHSIZEPLAYER)]->qtdRating);
                }
                
                system("pause");
            }
            break;
            case 3:{
                puts(consulta_elemento);
                printf("\ntop%d", topN);
                system("pause");
            }
            break;
            case 4:{

            }
            break;
            default:{

            }
        }
        



    }

    return 0;
}
