#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include "structs.h"
#define FILEMAXNOME 25
#define MAXDADOS 200
#define MAXRATINGS 24188078
#define MAXPLAYERS 18939
#define MAXTAGS 364950
#define MAXNOMEPLAYER 50
#define MAXNUMTAGS 10
#define MAXLENTAGS 5
#define TAMPLAYERS 2000

void verifica_consulta(char *consulta, int *codigo, int *topN, char *consultaelemento){             

    int cont=0;
    const char s[2] = " ";
    char busca[100] = {0};
    char top[4] = {0};
    char *token;
    token = strtok(consulta, s);
    
    while( token != NULL ) {

        if(cont>0){
            if(cont>1){
                strcat(busca, " ");
                strcat(busca, token);
            }
            else{
                strcat(busca, token);
            }
        }

        token = strtok(NULL, s);

        cont++;
   }

    if(consulta[0] == 'p' && consulta[1] == 'l' && consulta[2] == 'a' && consulta[3] == 'y' && consulta[4] == 'e' && consulta[5] == 'r'){
        *codigo = 1;
        strcpy(consultaelemento, busca);
    }
    else if(consulta[0] == 'u' && consulta[1] == 's' && consulta[2] == 'e' && consulta[3] == 'r'){
        *codigo = 2;
        strcpy(consultaelemento, busca);
    }
    else if(consulta[0] == 't' && consulta[1] == 'o' && consulta[2] == 'p'){
        *codigo = 3;
        if(consulta[3] >= 48 && consulta[3] <= 57){
            top[0] = consulta[3];
        }
        if(consulta[4] >= 48 && consulta[4] <= 57){
            top[1] = consulta[4];
        }
        if(consulta[5] >= 48 && consulta[5] <= 57){
            top[2] = consulta[5];
        }
        if(consulta[6] >= 48 && consulta[6] <= 57){
            top[3] = consulta[6];
        }
        *topN = atoi(top);
        strcpy(consultaelemento, busca);
    }
    else{
        *codigo = 0;
    }
}

char *minuscula(char *str){

    size_t len = strlen(str);
    char *lower = calloc(len+1, sizeof(char));

    for (size_t i = 0; i < len; ++i) {
        lower[i] = tolower((unsigned char)str[i]);
    }

    return lower;
}

char *remove_apostrofos(char *str){

    int len = strlen(str);

    if(str[0] == '\"'){

        for(int i=0; i<len;i++){

            str[i] = str[i+1];
            
        }
        str[len-3] = '\0';
    }
    else{

        str[len-1] = 32;

    }
    
    return str;
}

int indexPosition(char *position){
    if(position[0] == 'G'){
        return 0; // goleiro
    }
    else if(position[0] == 'S'){
        return 14; // centro avante
    }
    else if(position[0] == 'R'){
        if(position[1] == 'B'){
            return 1; // lateral direito
        }
        else if(position[1] == 'M'){
            return 9; // meia direita
        }
        else if(position[1] == 'W'){
            if(position[2] == 'B'){
                return 4; // ala direito
            }
            else{
                return 11; // ponta direito 
            }
        }
    }
    else if(position[0] == 'C'){
        if(position[1] == 'B'){
            return 2; // zagueiro
        }
        else if(position[1] == 'M'){
            return 7; // meia central
        }
        else if(position[1] == 'F'){
            return 13; // segundo atacante
        }
        else if(position[1] == 'D'){
            return 6; // volante
        }
        else if(position[1] == 'A'){
            return 8; // armadaor
        }
    }
    else if(position[0] == 'L'){
        if(position[1] == 'B'){
            return 3; // lateral direito
        }
        else if(position[1] == 'M'){
            return 10; // meia esquerda
        }
        else if(position[1] == 'W'){
            if(position[2] == 'B'){
                return 5; // ala esquerdo
            }
            else{
                return 12; // ponta esquerdo
            }
        }
    }
    else{
        return -2;
    }
}

int hashCode(int key, int tamanhotabela) {
    return (((int)sqrt(key)) + (key * 31)) % tamanhotabela;
}

struct DataPlayer *search(int key) {
   
   int hashIndex = hashCode(key, HASHSIZEPLAYER);  
    
   while(hashArray[hashIndex] != NULL) {
	
      if(hashArray[hashIndex]->sofifaid == key)
      {
        return hashArray[hashIndex]; 
      }
      else{ 
        ++hashIndex;
        hashIndex %= HASHSIZEPLAYER;
      }
   }        
   return NULL;        
}

void insertPlayer(int key, float data) {
    int flag=0;

   struct DataPlayer *player = (struct DataPlayer*) malloc(sizeof(struct DataPlayer));
   player->somaRating = data;  
   player->sofifaid = key;
   
   int hashIndex = hashCode(key, HASHSIZEPLAYER);

   while(hashArray[hashIndex] != NULL && flag==0) {

       if(hashArray[hashIndex]->sofifaid == key){
           player->somaRating = hashArray[hashIndex]->somaRating + data;
           player->qtdRating = hashArray[hashIndex]->qtdRating + 1;
           flag=1;
       }
       else{
            ++hashIndex;
            hashIndex %= HASHSIZEPLAYER;
       }
   }

   if(flag==0){
       player->qtdRating = 1;
   }

   hashArray[hashIndex] = player;
}

void insertUser(int user_id, int user_sofifaid, float user_rating) {
    int flag=0, pos_newrating=-1;

   struct DataUser *user = (struct DataUser*) malloc(sizeof(struct DataUser));

   int hashIndex = hashCode(user_id, HASHSIZEUSERS); 
   
   while(hashUser[hashIndex] != NULL && flag==0) { 

        if(hashUser[hashIndex]->userid == user_id){ 
            
            for(int i=0; i<20;i++){
                if(hashUser[hashIndex]->rating[i] >= user_rating){ 

                }
                else{ 
                    pos_newrating = i;
                    i=20;
                }
            }

            if (pos_newrating >= 0 && pos_newrating < 20)
            {
                for (int i = 19; i > pos_newrating; i--)
                {

                    hashUser[hashIndex]->rating[i] = hashUser[hashIndex]->rating[i - 1];
                    hashUser[hashIndex]->sofifaid[i] = hashUser[hashIndex]->sofifaid[i - 1];
                }

                hashUser[hashIndex]->rating[pos_newrating] = user_rating;
                hashUser[hashIndex]->sofifaid[pos_newrating] = user_sofifaid;
            }

            flag=1;
       }
       else{
            ++hashIndex;
            hashIndex = (hashIndex * hashIndex) %  HASHSIZEPLAYER;
       }
   }

   if(flag==0){
        user->userid = user_id;
        user->sofifaid[0] = user_sofifaid;
        user->rating[0] = user_rating;
        hashUser[hashIndex] = user;
   }
}

void saveRatings(FILE *file){

    char line[100];
    int cont, cont2=0;
    int num_userid, num_sofifaid;
    float num_rating;

    file = fopen("csvFiles/rating.csv", "r");
    if (file == NULL)
    {   
        printf("Arquivo rating.csv nao encontrado.\n\n");
        exit(1);
    }

    while (fgets(line, sizeof(line), file))
    {
        cont=0;
        char s[2] = ",";
        char *token;
        token = strtok(line, s);

        while (token)
        {   
            if(cont2>0){
            cont++;
                if(cont==1){
                    num_userid = atoi(token);
                }
                else if(cont==2){
                    num_sofifaid = atoi(token);
                }
                else if(cont==3){
                    num_rating = atof(token);
                }
            }
            token = strtok(NULL, ",");
        }
        if(cont2>0){ 
            insertPlayer(num_sofifaid, num_rating);
            if(cont2<7500000){
                insertUser(num_userid, num_sofifaid, num_rating);
            }
        }
        if(cont2%240000 == 0){
            system("cls");
            printf("%d%%\n", 2 * cont2/480000);
        }
        cont2++;
    }

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
            token = strtok(NULL, "");
        }
        
        
    }
    return l;
}

void insertPlayernames(char *nome, int idsofifa, char playernames[HASHSIZEPLAYER][MAXNOMEPLAYER]){

    int hashIndex = hashCode(idsofifa, HASHSIZEPLAYER);

    if(strcmp(nome,"Joe Fryer") != 0 && strcmp(nome,"Ellis Simms") != 0 && strcmp(nome,"Y. Takahashi") != 0){
        if(hashArray[hashIndex]->sofifaid == idsofifa){

            strcpy(playernames[hashIndex], nome); 

        }
        else{
            ++hashIndex;
            hashIndex %= HASHSIZEPLAYER;
        }
    }
}

void saveTops(int tops[15][MAXTOPN], int sofifaid, char *position, char *nome){

    int cont=0, codigohash=0, codigohashtops=0;
    int position1=-1, position2=-1, position3=-1;
    const char s[2] = ",";
    char *token;

    if(sofifaid != 229685 && sofifaid != 231196 && sofifaid != 242048 && sofifaid != 251198 && sofifaid != 201353  && sofifaid != 211434 && sofifaid != 257359 && sofifaid != 211791 && sofifaid != 232462 && sofifaid != 0){

        token = strtok(position, s);

        while( token != NULL ) {
            
            if(cont==0){
                
                position1 = indexPosition(token);

            }
            else if(cont==1){

                position2 = indexPosition(token);
                
            } 
            else if(cont==2){

                position3 = indexPosition(token);
                
            }

            token = strtok(NULL, s);

            cont++;
        }

        codigohash = hashCode(sofifaid, HASHSIZEPLAYER);

        while(hashArray[codigohash]->sofifaid != sofifaid){

            ++codigohash;
            codigohash %= HASHSIZEPLAYER;
            
        }

        if (sofifaid != 229685 && sofifaid != 251198 && sofifaid != 211434){

            if(hashArray[codigohash]->qtdRating >= 1000){

                if (position1 != -1){

                    for (int i = 0; i < MAXTOPN; i++){

                        if (tops[position1][i] == 0){
                            tops[position1][i] = sofifaid;
                            i = MAXTOPN + 10;
                        }
                        else{

                            codigohashtops = hashCode(tops[position1][i], HASHSIZEPLAYER);

                            while(hashArray[codigohashtops]->sofifaid != tops[position1][i]){
                                ++codigohashtops;
                                codigohashtops %= HASHSIZEPLAYER;
                            }

                            
                            if(hashArray[codigohash]->somaRating / hashArray[codigohash]->qtdRating >  hashArray[codigohashtops]->somaRating / hashArray[codigohashtops]->qtdRating){

                                if(i==MAXTOPN-1){
                                    tops[position1][i] = sofifaid;
                                }
                                else{
                                    for (int j = MAXTOPN - 1; j > i; j--){
                                        tops[position1][j] = tops[position1][j - 1];
                                    }
                                    tops[position1][i] = sofifaid;
                                }
                                i=MAXTOPN+10;
                            }
                        }
                    }
                }
                if (position2 != -1){

                    for (int i = 0; i < MAXTOPN; i++){

                        if (tops[position2][i] == 0){
                            tops[position2][i] = sofifaid;
                            i = MAXTOPN + 10;
                        }
                        else{

                            codigohashtops = hashCode(tops[position2][i], HASHSIZEPLAYER);

                            while(hashArray[codigohashtops]->sofifaid != tops[position2][i]){
                                ++codigohashtops;
                                codigohashtops %= HASHSIZEPLAYER;
                            }
                            
                            if(hashArray[codigohash]->somaRating / hashArray[codigohash]->qtdRating >  hashArray[codigohashtops]->somaRating / hashArray[codigohashtops]->qtdRating){

                                if(i==MAXTOPN-1){
                                    tops[position2][i] = sofifaid;
                                }
                                else{
                                    for (int j = MAXTOPN - 1; j > i; j--){
                                        tops[position2][j] = tops[position2][j - 1];
                                    }
                                    tops[position2][i] = sofifaid;
                                }

                                i=MAXTOPN+10;
                            }
                        }
                    }
                }
                if (position3 != -1){

                    for (int i = 0; i < MAXTOPN; i++){

                        if (tops[position3][i] == 0){
                            tops[position3][i] = sofifaid;
                            i = MAXTOPN + 10;
                        }
                        else{

                            codigohashtops = hashCode(tops[position3][i], HASHSIZEPLAYER);

                            while(hashArray[codigohashtops]->sofifaid != tops[position3][i]){
                                ++codigohashtops;
                                codigohashtops %= HASHSIZEPLAYER;
                            }


                            if(hashArray[codigohash]->somaRating / hashArray[codigohash]->qtdRating >  hashArray[codigohashtops]->somaRating / hashArray[codigohashtops]->qtdRating){
                            
                                if(i==MAXTOPN-1){
                                    tops[position3][i] = sofifaid;
                                }
                                else{
                                    for (int j = MAXTOPN - 1; j > i; j--){
                                        tops[position3][j] = tops[position3][j - 1];
                                    }
                                    tops[position3][i] = sofifaid;
                                }

                                i=MAXTOPN+10;
                            }
                        }
                    }
                }
            }
        }
    }
}

void le_player(char dado[MAXDADOS], char *word, int *id, char *pos, char playernames[HASHSIZEPLAYER][MAXNOMEPLAYER], int tops[15][MAXTOPN]){

    int cont=0;
    int idsofifa;
    char position[25] = "";
    char nome[MAXNOMEPLAYER];

    char s[2] = ",\"";
    char u[2] = " ";
    char *token;
    token = strtok(dado, s);

    while (token != NULL)
    {
        if (cont == 0)
        {   
            idsofifa = atoi(token);
        }
        else if (cont == 1)
        {
            strcpy(nome, token);
        }
        else
        {  
            if(strlen(token) <= 5){
                strcat(position, token);
            }
        }

        if(cont>0){
            token = strtok(NULL, u);
        }
        else{
            token = strtok(NULL, s);
        }
    
        cont++;
    }

    if(nome && idsofifa){
        insertPlayernames(nome, idsofifa, playernames);
    }
    
    strcpy(position, remove_apostrofos(position));
    strcpy(pos, position);
    strcpy(word, nome);
    *id = idsofifa;


    saveTops(tops, idsofifa, position, nome);
    

}

void print_userrating(int consulta_user, char playernames[HASHSIZEPLAYER][MAXNOMEPLAYER]){

    for(int i=0;i<20;i++){
        printf("%d\t", hashUser[hashCode(consulta_user, HASHSIZEUSERS)]->sofifaid[i]);
        fputs(playernames[(((int)sqrt(hashUser[hashCode(consulta_user, HASHSIZEUSERS)]->sofifaid[i])) + (hashUser[hashCode(consulta_user, HASHSIZEUSERS)]->sofifaid[i] * 31)) % HASHSIZEPLAYER], stdout);
        
        if(strlen(playernames[(((int)sqrt(hashUser[hashCode(consulta_user, HASHSIZEUSERS)]->sofifaid[i])) + (hashUser[hashCode(consulta_user, HASHSIZEUSERS)]->sofifaid[i] * 31)) % HASHSIZEPLAYER]) < 8){
            printf("\t\t\t\t\t%.6f\t", hashArray[hashCode(hashUser[hashCode(consulta_user, HASHSIZEUSERS)]->sofifaid[i], HASHSIZEPLAYER)]->avgRating);
        }
        else if(strlen(playernames[(((int)sqrt(hashUser[hashCode(consulta_user, HASHSIZEUSERS)]->sofifaid[i])) + (hashUser[hashCode(consulta_user, HASHSIZEUSERS)]->sofifaid[i] * 31)) % HASHSIZEPLAYER]) < 16){
            printf("\t\t\t\t%.6f\t", hashArray[hashCode(hashUser[hashCode(consulta_user, HASHSIZEUSERS)]->sofifaid[i], HASHSIZEPLAYER)]->avgRating);
        }
        else if(strlen(playernames[(((int)sqrt(hashUser[hashCode(consulta_user, HASHSIZEUSERS)]->sofifaid[i])) + (hashUser[hashCode(consulta_user, HASHSIZEUSERS)]->sofifaid[i] * 31)) % HASHSIZEPLAYER]) < 24 ){
            printf("\t\t\t%.6f\t", hashArray[hashCode(hashUser[hashCode(consulta_user, HASHSIZEUSERS)]->sofifaid[i], HASHSIZEPLAYER)]->avgRating);
        }
        else if(strlen(playernames[(((int)sqrt(hashUser[hashCode(consulta_user, HASHSIZEUSERS)]->sofifaid[i])) + (hashUser[hashCode(consulta_user, HASHSIZEUSERS)]->sofifaid[i] * 31)) % HASHSIZEPLAYER]) < 32 ){
            printf("\t\t%.6f\t", hashArray[hashCode(hashUser[hashCode(consulta_user, HASHSIZEUSERS)]->sofifaid[i], HASHSIZEPLAYER)]->avgRating);
        }
        else if(strlen(playernames[(((int)sqrt(hashUser[hashCode(consulta_user, HASHSIZEUSERS)]->sofifaid[i])) + (hashUser[hashCode(consulta_user, HASHSIZEUSERS)]->sofifaid[i] * 31)) % HASHSIZEPLAYER]) >= 32 ){
            printf("\t%.6f\t", hashArray[hashCode(hashUser[hashCode(consulta_user, HASHSIZEUSERS)]->sofifaid[i], HASHSIZEPLAYER)]->avgRating);
        }

        printf("%d\t", hashArray[hashCode(hashUser[hashCode(consulta_user, HASHSIZEUSERS)]->sofifaid[i], HASHSIZEPLAYER)]->qtdRating);
        printf("%.2f\n", hashUser[hashCode(consulta_user, HASHSIZEUSERS)]->rating[i]);
    }

}

int trie_new (struct trie **trie)
{
    *trie = calloc(1, sizeof(struct trie));
    if (NULL == *trie) {
        // erro ao alocar memoria
        printf("erro ao alocar memoria para a trie\n");
        return -1;
    }
    return 0;
}

int trie_insert (struct trie *trie, char *word, unsigned word_len, int id, int *qtd, float *avg, char *playerpos)
{
    int ret = 0, index;

    if (0 == word_len) {
        trie->end_of_word = true;
        trie->trie_sofifaid = id;
        trie->trie_qtdrating = qtd;
        trie->trie_avgrating = avg;
        strcpy(trie->trie_position, playerpos);

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
    
    return trie_insert(trie->children[index], word + 1, word_len - 1, id, qtd, avg, playerpos);
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
    char aux[50];
    int len_aux;

    if (true == trie->end_of_word) {
        printf("%d ", trie->trie_sofifaid);
        
        itoa(trie->trie_sofifaid, aux, 10);
        len_aux = strlen(aux) + 2;

        if(prefix_len+len_aux == 49){
            printf("%.*s", prefix_len, prefix);
        }
        else if(prefix_len+len_aux > 45){
            printf("%.*s\t", prefix_len, prefix);
        }
        else if(prefix_len+len_aux > 40){
            printf("%.*s\t", prefix_len, prefix);
        }
        else if(prefix_len+len_aux > 32){
            printf("%.*s\t\t", prefix_len, prefix);
        }
        else if(prefix_len+len_aux >= 25){
            printf("%.*s\t\t\t", prefix_len, prefix);
        }
        else if(prefix_len+len_aux > 16){
            printf("%.*s\t\t\t\t", prefix_len, prefix);
        }
        else{
            printf("%.*s\t\t\t\t\t", prefix_len, prefix);
        }
        
        fputs(trie->trie_position, stdout);
        if(strlen(trie->trie_position) > 7){
            printf("\t%.6f\t", *trie->trie_avgrating);
        }
        else{
            printf("\t\t%.6f\t", *trie->trie_avgrating);
        }
        
        printf("%d", *trie->trie_qtdrating);
        printf("\n");
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

