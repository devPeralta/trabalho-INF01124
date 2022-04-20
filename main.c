#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <time.h>
#include <string.h>
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

    lista_minirating = inicializaLista(); // inicializa a lista de dados do arquivo minirating.csv
    lista_minirating = saveFile(file_minirating, minirating, lista_minirating); // salva os dados de minirating.csv na lista

    printf("foi1\n");

    lista_rating = inicializaLista();
    lista_rating = saveFile(file_rating, rating, lista_rating); 

    printf("foi2");


    
    
    

    return 0;
}