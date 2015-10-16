#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <math.h>
#include "list.c"

#define BigArray 600


           ///////////////////////////////////////////////////////////////
           /////////////%%%%%% Prototyping Functions %%%%%%%%/////////////
           //////////////////////////////////////////////////////////////


//other functions
bool isDigit(char c);
bool isOperator(char c);
char *StringFormatter(char string[]);
Node_t *tokenizer(char string[]);
double convDouble(char string[]);
int isNumeric(char array[]);
int precChecker(char tokens[]);
double Parser(Node_t* LinkedList);

//grammar functions
static double statement_list();
static double statement();
static double E();
static double E_tail(double value);
static double T();
static double T_tail(double value);
static double F();

//global variables
double global_term_val = 0;
double global_e_val = 0;
Node_t *global_current;

//character storage
char allOPS[] = "+-*/%()";



        //////////////////////////////////////////////////////////////////////
        ////////%%%%%%%%%%%% Digit or Operator Checker %%%%%%%%%%%%%%/////////
        //////////////////////////////////////////////////////////////////////



bool isDigit(char c){
    int val = c - '0';
    if ((val >= 0 && val <= 9) || c == '.'){
        return true;
    }
    return false;
}

bool isOperator(char c){
    int charlen = strlen(allOPS);

    for(int i = 0 ; i< charlen; i++){
        if (allOPS[i] == c){
            return true;
        }
    }
    return false;

}



        //////////////////////////////////////////////////////////////////////
        ///////%%%%%%%%% String Formatter /w Single Spaces %%%%%%%%%%%////////
        //////////////////////////////////////////////////////////////////////




//for formatting any string into numbers then spaces then operators then numbers and so on //

char *StringFormatter(char string[]){

    char *newString = (char*)malloc(800 * sizeof(char));
    if (!newString) {
        return NULL;
    }
    int len = strlen(string);
    int i = 0;
    int desti = 0;
    char *space = " ";

    while (i<len) {
        if (isDigit(string[i])){
            newString[desti] = string[i];
            desti++;
        }
        
        
        else if ((i+1 < len) && ((string[i] == '+' && string[i+1] == '+') || (string[i] == '-' && string[i+1] == '-'))){
            newString[desti] = ' ';
            desti++;
            newString[desti] = string[i];
            desti++;
            newString[desti] = string[i];
            desti++;
            newString[desti] = ' ';
            desti++;
            i++;
        }
        else if (isOperator(string[i])){
            newString[desti] = ' ';
            desti++;
            newString[desti] = string[i];
            desti++;
            newString[desti] = ' ';
            desti++;
        }
        
        i++;
    }
    newString[desti] = '\0';
    return newString;

}



        //////////////////////////////////////////////////////////////////////
        ///////%%%%%%%%% String Tokenizer using LinkedList %%%%%%%%%%%////////
        //////////////////////////////////////////////////////////////////////




//to tokenize everything//
//takes in the formatted string and returns a list//


Node_t *tokenizer(char string[]){
    Node_t *token_list = NULL;
    const char space[2] = " ";
    char *id_token;
    id_token = strtok(string, space);
    token_list = initList(id_token,token_list);
    while(id_token != NULL){
        id_token = strtok(NULL, space);
        if (id_token == NULL)
            break;
        addNode(id_token,token_list);
    }
    return token_list;
}


        //////////////////////////////////////////////////////////////////////
        ///////////%%%%%%%%%%% Converting to a double %%%%%%%%%%%%////////////
        /////////////////////////////////////////////////////////////////////


double convDouble(char string[]){
double num;
sscanf(string, "%lf", &num);
return num;
}

        //////////////////////////////////////////////////////////////////////
        ///////%%%%%%% Checks if we can convert it to a double %%%%%%%%///////
        //////////////////////////////////////////////////////////////////////

//if numeric return NOT 0

int isNumeric(char array[]){
    if(array==NULL || array == '\0'){
        return 0;
    }
    char *num;
    strtod(array, &num);
    return *num == '\0';
}

        //////////////////////////////////////////////////////////////////////
        ////////////////%%%%%%%%%%%%% Grammar %%%%%%%%%%%%%%//////////////////
        //////////////////////////////////////////////////////////////////////

void next_token(){
    if ( global_current->next != NULL ){
        global_current = global_current->next;
    }
}

static double statement_list(){
    printf("Inside statement_list \n");

    if ( isNumeric(global_current->val) != 0 ){
        double temp = statement();
        return temp;

    }
    if (strcmp(global_current->val,"(") == 0){
        double temp = statement();
        return temp;

    }
}

static double statement(){
    printf("Inside statement\n");
    return E();
}

static double E(){
    printf("Inside E\n");
    return E_tail(T());
}

static double T(){
    printf("Inside T\n");
    return T_tail(F());
}

static double F(){
    printf("Inside F\n");
    if( strcmp(global_current->val,"(") == 0 ){
        next_token();
        double hold = E();
        if ( strcmp(global_current->val,")") == 0 ){
            next_token();
            return hold;
        }
        else{
            printf("Error\n");
        }
    }
    if ( isNumeric(global_current->val) != 0){
        double hold = convDouble(global_current->val);
        next_token();
        return hold;
    }
}

static double T_tail(double val){
    printf("Inside T_tail\n");
    
    if ( strcmp(global_current->val,"*") == 0 ){
        next_token();
        return val * T_tail(F());
    }
    else if ( strcmp(global_current->val,"/") == 0 ){
        next_token();
        return val / T_tail(F());
    }
    return val;
}

static double E_tail(double val){
    printf("Inside E_tail\n");

    if ( strcmp(global_current->val,"+") == 0 ){
        next_token();
        return E_tail(val + T());
    }
    else if ( strcmp(global_current->val,"-") == 0 ){
        next_token();
        return E_tail(val - T());
    }
    return val;
}



        //////////////////////////////////////////////////////////////////////
        ////////////////%%%%%%%%%%%%% Parser %%%%%%%%%%%%%%///////////////////
        //////////////////////////////////////////////////////////////////////


double Parser(Node_t* LinkedList){
   
    Node_t *current = LinkedList;
    global_current = current;

    double result = statement_list();
    return result;
   
}

       
       
        //////////////////////////////////////////////////////////////////////
       ///////%%%%%%%%% Main Method for Testing WhatsUp!! %%%%%%%%%%%////////
       //////////////////////////////////////////////////////////////////////
       
       
      
int main(int argc, char *argv[]){

    if (argc != 2){

        printf("usage: %s filename\n",argv[0]);

    }
    else{

        FILE *file = fopen(argv[1],"r");
        FILE *outfile = fopen("out.txt","w");
        if(file == 0){
            printf("Could not open file\n");

        }
        else{
            printf("Reading file");
            char x;
            while( (x = fgetc(file)) != EOF ){

                int i = 0;
                char Buffer[BigArray];
                while( x !=';'){
                    Buffer[i] = x;
                    printf("%c\n",Buffer[i]);
                    if (x == '\n'){
                        continue;
                    }
                    i++;
                    x = fgetc(file);
                }
                Buffer[i] = '\0';

                char *form = StringFormatter(Buffer);
                char formattedString[BigArray];
                for(int i =0; i<strlen(form);i++){
                   formattedString[i]=form[i];
                }
                printf("%s\n",formattedString);
                char printArr[BigArray];
                strcpy(printArr,formattedString);
                Node_t *tokenList = NULL;
                tokenList = tokenizer(formattedString);
                printList(tokenList);

                double mini_results = Parser(tokenList);
                printf("%s\n",printArr);


                fprintf(outfile, "%s %s %f\n", printArr, "=", mini_results);
                x = fgetc(file);

               
            }
            fclose(file);
            fclose(outfile);
        }
    }
}









