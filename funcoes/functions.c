#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include "structs.h"
#define FILEMAXNOME 25
#define MAXDADOS 200
#define MAXRATINGS 24188078
#define MAXPLAYERS 18944
#define MAXTAGS 364950
#define MAXNOMEPLAYER 100
#define MAXNUMTAGS 10
#define MAXLENTAGS 5

char *minuscula(char *str){

    size_t len = strlen(str);
    char *lower = calloc(len+1, sizeof(char));

    for (size_t i = 0; i < len; ++i) {
        lower[i] = tolower((unsigned char)str[i]);
    }

    return lower;

}

Lista *inicializaLista()
{
    return NULL;
}

Lista *insereLista(Lista *l, char dado[MAXDADOS]){

    Lista *novo = (Lista *)malloc(sizeof(Lista));
    strcpy(novo->dados, dado);
    novo->prox = l;
    return novo;
}

Lista *saveFile(FILE *file, char nomeArquivo[FILEMAXNOME], Lista *l)
{
    char teste[MAXDADOS];
    double cont = 0.0;

    char diretorio[FILEMAXNOME] = "";
    strcat(diretorio, "csvFiles/");
    strcat(diretorio, nomeArquivo);
    
    file = fopen(diretorio, "r");
    if (file == NULL)
    {
        perror("Nao foi possivel abrir o arquivo.");
        exit(1);
    }

    char line[200];

    while (fgets(line, sizeof(line), file))
    {
        char *token;

        token = strtok(line, "");

        while (token != NULL)
        {
            strcpy(teste,token);
            l = insereLista(l, teste);
            cont = cont + 1;
            //if(cont>12459999){ // max=12461413
            //printf("%.lf: %s",cont, l->dados);
            //}
            token = strtok(NULL, "");
        }
        
        
    }
    return l;
}

void le_player(char dado[MAXDADOS], char *word){

    int cont=0;
    int id;
    char tags[25] = "";
    char nome[MAXNOMEPLAYER], tag[MAXNUMTAGS][MAXLENTAGS];

    char s[2] = ",\"";
    char *token;
    token = strtok(dado, s);

    while (token != NULL)
    {
        if (cont == 0)
        {
            id = atoi(token);
        }
        else if (cont == 1)
        {
            strcpy(nome, token);
        }
        else
        {
            strcat(tags, token);
        }

        token = strtok(NULL, s);

        cont++;
    }
    strcpy(word, nome);
   //printf("id = %d\nnome = ", id);
   //printf("tags = %s\n", tags);

}

int trie_new (struct trie **trie)
{
    *trie = calloc(1, sizeof(struct trie));
    if (NULL == *trie) {
        // erro ao alocar memoria
        return -1;
    }
    return 0;
}

int trie_insert (struct trie *trie, char *word, unsigned word_len)
{
    int ret = 0, index;

    if (0 == word_len) {
        trie->end_of_word = true;
        return 0;
    }
    if(((int)word[0]) == 32){ // space
        index = 26;
    }
    else if(((int)word[0]) == 39){ // '
        index = 27;
    }
    else if(((int)word[0]) == 46){ // .
        index = 28;
    }
    else if(((int)word[0]) == 45){ // -
        index = 29;
    }
    else{
        index = word[0] - 'a';
    }

    if (ALPHABET_SIZE <= index) {
        return -1;
    }

    if (NULL == trie->children[index]) {
        ret = trie_new(&trie->children[index]);
        if (-1 == ret) {
            return -1;
        }
    }
    
    return trie_insert(trie->children[index], word + 1, word_len - 1);
}

void trie_create(Lista *lista_players, struct trie *trie){
    
    int ret=0;
    char word[100] = {0};

    for(int i=0; i<MAXPLAYERS+1; i++) {
        le_player(lista_players->dados, word);
        strcpy(word, minuscula(word));
        ret = trie_insert(trie, word, strnlen(word, 100));
        if (-1 == ret){
            printf("Nao foi possivel inserir a palavra na trie\n");
            exit(1);
        }
        lista_players = lista_players->prox;
    }

}

int trie_search(struct trie *trie, char *word, unsigned word_len,struct trie **result)
{
    int index;
    if (0 == word_len) {
        *result = trie;
        return 0;
    }

    if(((int)word[0]) == 32){ // space
        index = 26;
    }
    else if(((int)word[0]) == 39){ // '
        index = 27;
    }
    else if(((int)word[0]) == 46){ // .
        index = 28;
    }
    else if(((int)word[0]) == 45){ // -
        index = 29;
    }
    else{
        index = word[0] - 'a';
    }

    if (ALPHABET_SIZE <= index) {
        return -1;
    }

    if (NULL == trie->children[index]) {
        return -1;
    }

    return trie_search(trie->children[index], word + 1,word_len - 1, result);
}

void trie_print (struct trie *trie, char prefix[], unsigned prefix_len)
{
    if (true == trie->end_of_word) {
        printf("%.*s\n", prefix_len, prefix);
    }

    for (int i = 0; i < ALPHABET_SIZE; i++) {

        if (NULL == trie->children[i]){
            continue;
        }

        if(i+'a' == '{'){
            prefix[prefix_len] = ' ';
        }
        else if(i+'a' == '|'){
            prefix[prefix_len] = '\'';
        }
        else if(i+'a' == '}'){
            prefix[prefix_len] = '.';
        }
        else if(i+'a' == '~'){
            prefix[prefix_len] = '-';
        }
        else{
            prefix[prefix_len] = i + 'a';
        }
        trie_print(trie->children[i], prefix, prefix_len + 1);
    }
}

