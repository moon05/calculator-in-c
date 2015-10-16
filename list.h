/*
 * Abdullah Al Mamun
 * CSC 173 Fall 2015 -- Calculator project
 * Date: 11th October, 2015
 *
 */


#ifndef LIST_H
#define LIST_H


typedef struct Node{
    char val[30];
    struct Node * next;
} Node_t;


//struct list *head = NULL;
//struct list *curr = NULL;



Node_t* initList(char val[], Node_t *head);
Node_t* addNode(char val[], Node_t *head);
//int length();
void printList(Node_t *head);

#endif