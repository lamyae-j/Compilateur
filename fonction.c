/* sur ce fichier on va mettre en place les fonctions qui vont nous permettre de gérer les régles de l'exercice */
#include<stdio.h>
#include<ctype.h>
#include "header.h"

/* definition des contraintes de longueur des tokens */

#define MaxNum  11
#define MaxChar 20 

/* Prototype des fonctions de base */

char NextChar();
bool isNumber();
bool isAlphabetic();
bool ErrorLex();
bool isSpecialCharacter();
void ignoreWhiteSpaces();
void getToken();


/* declaration */

char currentChar;
Token currentToken;


/* implementation  */

char NextChar(){
    fscanf(fichier,"%c", &currentChar);// fgetc(currentChar)
    return currentChar;
}



// savoir si un caractère est un chiffre entiers : (\+|\-)?[0-9]+
bool  isNumber(){
    bool isInt = FALSE ;
     if(!isdigit(currentChar))
        return isInt;


	char* memory = (char *)malloc(MaxNum*sizeof(char));
    int i=0;
    memory[i]=currentChar;
    // on vérifie la longueur du nombre , et la non apparition de caractere autre que les digit
    while( ++i <= MaxNum && isdigit(memory[i] = currentChar = NextChar()));
     if(i > MaxNum){
       
        printf("Number has several digit");
        exit(1);
     }
    memory[i] = '\0';

    strcpy(currentToken.name, "NUM");
    strcpy(currentToken.value, memory);
    free(memory);
    isInt = TRUE;
    return isInt;
}


/*bool Alphabetic(char c){
	if((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') || c == '_'){
		return TRUE;
	}
	return FALSE;
}*/

// caractère ou l'on ne différencie pas entre maj et mini 
bool isAlphabetic(){
     if( !isalpha(currentChar) )
        return FALSE;
    
    char* memory =(char *)malloc(MaxChar*sizeof(char));
    int i = 0, j = 0, cmp=0;
    memory[i] = toupper(currentChar);// pour ne pas differencier upper or lower casev

    while( ++i <= MaxChar && (isalnum( memory[i] = currentChar = toupper(NextChar()) ) ||memory[i] == '_' ));

    if(i == MaxChar){
        printf("there is many characters in this word");
        exit(1);
    }
       
         
    memory[i] = '\0';

    // Verify this word match a keyword in the list of keywords
    while( (cmp=strcmp(memory , keywords_list[j++])) != 0 && j < NBRKEYWORDS);

    if(cmp == 0){ // is keyword
        strcpy(currentToken.name, keywords_list[j-1]);
        strcpy(currentToken.value, memory);
    }

    else{ // If not keyword, so it's an ID
        strcpy(currentToken.name, "ID"); 
        strcpy(currentToken.value, memory);
    }
    free(memory);
    return TRUE;
}

/*une erreur est affichée à chaque fois un token est different de ceux de notre langage 
cette fonction gère les messages d'erreur */



bool isSpecialCharacter(){

    int i=0,cmp=0;
    char op[3];
    memset(op,'\0',sizeof(op));

    op[0] = currentChar;
    if((op[1] = currentChar = NextChar()) != '=')
        op[1] =  '\0';
    else
        NextChar();
     
    while( (cmp = strcmp(op, specialTokens_symb[i++]) != 0) && i < NBRSPECIALTOKENS);// on parcours la liste des tokens et on compare 

    if(cmp != 0)
        return FALSE;

    strcpy(currentToken.name, specialTokens_list[i-1]); 
    strcpy(currentToken.value, op);

    return TRUE;
}

 void ignoreWhiteSpaces(){

    // Ignore blank space, tabulation, newline
    while( currentChar == ' ' || currentChar == '\t' || 
    currentChar == '\n' || currentChar == '{'){
        NextChar();
        // Ignore Comments
        if( currentChar == '{'){
            if((currentChar=NextChar()) == '*')
                while((currentChar=NextChar()) != '*' || currentChar != EOF);
            else {
                
            
                printf("Error in comment, open brace");
                exit(1);
            }

            if(currentChar != '}'){
               printf("Error in comment, close brace");
               exit(1);
            }
        }
    }
}


void getToken(){
    // Clear Token
    memset(currentToken.name, '\0', lenName);
    memset(currentToken.value, '\0', lenValue);

    // Ignore Whitespaces and Newlines and Comments
    ignoreWhiteSpaces();

    if(currentChar == EOF){ strcpy(currentToken.name, "EOF");}
    else if( isNumber() ){}
    else if( isAlphabetic() ){}
    else if( isSpecialCharacter() ){}
    else{ 
        printf("Invalid Token");
        exit(1);
    }
}
