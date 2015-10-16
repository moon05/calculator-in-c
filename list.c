/*
 * Abdullah Al Mamun
 * CSC 173 Fall 2015 -- Calculator project
 * Date: 11th October, 2015
 *
 */

#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <math.h>
#include "list.h"




Node_t* initList(char val[], Node_t *head){
    head = (Node_t*) malloc(sizeof(Node_t));
    //can also be written as null==ptr
    if(head == NULL){
        printf("\n Node creation failed \n");
        return NULL;
    }
    //ptr has two properties: .val and .next
    strcpy(head->val, val);
    head->next = NULL;   //this is same as ptr.next=null
    //making
    //head = ptr;
    return head;
}

Node_t* addNode(char val[], Node_t *head){
    if(head==NULL){
        head = initList(val, head);
        return head;
    }
    Node_t *curr = head;
    while(curr->next != NULL)
        curr = curr->next;
    
    Node_t *new_node = (Node_t*)malloc(sizeof(Node_t));
    
    if (new_node == NULL) {
        return NULL;
    }
    //ptr->val = val;
    strcpy(new_node->val, val);
    new_node->next = NULL;
    curr->next = new_node;
    
    return head;
}

//int length(){
//    return 0;
//}



void printList(Node_t *head){
    Node_t *ptr = head;
    printf("\nPrinting List Started \n");
    while(ptr!=NULL){
        printf("\n(%s)\n",ptr->val);
        ptr = ptr->next;
    }
    printf("\nPrinting List Ended \n");
    
    return;
}

//////////////////////////////
/////test for linked list/////
//////////////////////////////
////////
//int main(void){
//    Node_t *list = NULL;
//    char a[] = "s";
//    char b[] = "e";
//    char c[] = "x";
//    char d[] = "motherfucker";
//    list = initList(a, list);
//    
//    if (list == NULL)
//        printf("Still empty list");
//    
//    printList(list);
//    
//    addNode(b, list);
//    addNode(c, list);
//    addNode(d, list);
//    printList(list);
//}
//
//
//}
//
