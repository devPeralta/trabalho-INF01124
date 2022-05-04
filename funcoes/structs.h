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
#define HASHSIZEPLAYER 29383
//#define HASHSIZEUSERS 10000
#define HASHSIZEUSERS 24188078

struct DataPlayer { // player
   int sofifaid;   // id do player
   int qtdRating; // numero de avaliacoes do player
   float somaRating; // soma total das avaliacoes do player
   float avgRating; // somaRating dividido pelo qtdRating = media dos ratings do player
};

struct DataUser { // user
   int userid;  // id do usuario
   int sofifaid[20]; // array com o id dos 20 jogadores mais bem avaliados pelo user
   float rating[20]; // array com o rating dos 20 jogadores mais bem avaliados pelo user
};

struct DataPlayer* hashArray[HASHSIZEPLAYER]; // tabela hash dos players
struct DataPlayer* dummyItem; // nao usado ainda
struct DataPlayer* player; // variavel do tipo DataPlayer

struct DataUser* hashUser[HASHSIZEUSERS]; // tabela hash dos users
struct DataUser* dummyUser; // nao usado ainda
struct DataUser* user; // variavel do tipo DataUser

struct lista { // lista que armazena dados de players.csv
 char dados[150]; // string com dados do player
 struct lista* prox; // ponteiro para o proximo elemento da lista
};
typedef struct lista Lista;

struct trie { // arvore trie para armazenar todos nomes dos players
    struct trie *children[ALPHABET_SIZE]; // nodo filho com 30 espacos = A a Z + 4 caracteres especiais (space, virgula, hifen e apostrofo)
    int *trie_sofifaid; // armazena o id do player no nodo da ultima letra
    float *trie_avgrating; // armazena a media de avaliacoes no nodo da ultima letra
    int *trie_qtdrating; // armazena a quantidade de avaliacoes no nodo da ultima letra
    char trie_position[25];
    bool end_of_word; // booleano para sinalizar fim do nome do player
};