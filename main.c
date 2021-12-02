#include<stdlib.h>
#include<stdio.h>
#include<string.h>

#include "fonction.c"

int main(){

    
    const char*  filename= "C:\\Users\\lolal\\Desktop\\compila\\Myfile.txt";
    fichier=fopen(filename,"r");
    if(fichier==NULL){
         printf(" ERREUR D'OUVERTURE DU FICHIER ");
         exit(EXIT_FAILURE);
    }
    NextChar();
    getToken();
    do{
        printf("%s_TOKEN\t", currentToken.name);
        getToken();
    }while(strcmp(currentToken.name,"EOF"));

    return 1;
    
}