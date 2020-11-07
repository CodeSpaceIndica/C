#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "hash.h"

#define MAX_LEN 40

/**
 * A Doubly linked lit
 **/
struct Node {
    char strData[MAX_LEN];

    struct Node *next;
    struct Node *prev;
};

/**
 * Technically speaking this is a push... 
 * 
 * adds(pushes) a value to the linked and returns the head of the linked list.
 * 
*/
struct Node * push(char aData[], struct Node *head) {
    struct Node *newNode = (struct Node*)malloc( sizeof(struct Node) );

    //Copy data to new Node
    strcpy(newNode->strData, aData);
    //snprintf(newNode->strData, MAX_LEN, "%s", aData);
    newNode->next = head;
    newNode->prev = NULL;//Set previous to NULl initially.

    //If teh parameter *head already has some data then....
    //Make the previous pointer of head the new Node.
    if( head != NULL ) {
        head->prev = newNode;
    }

    head = newNode;

    return head;
}

/**
 * Delete a node with the first occurence of aData string
 **/
void delete(char aData[], struct Node *head) {
    struct Node *nodeToDelete = NULL;
    struct Node *current = head;
    //Search for the node with the data..
    while ( current != NULL) {
        if( strcmp(current->strData, aData) == 0 ) {
            nodeToDelete = current;
            break;
        }
        current = current->next;
    }
    //Nothing to delete. Return
    if( nodeToDelete == NULL ) {
        return;
    }
    //If the head is the nodeToDelete, then simply simply make it the head.
    if( nodeToDelete == head ) {
        head = nodeToDelete->next;
    }

    //Take the prev pointer of the next node and point it to the prev of the nodeToDelete.
    if( nodeToDelete->next != NULL ) {
        nodeToDelete->next->prev = nodeToDelete->prev;
    }

    //Take he next pointer of the prev node and point it to the next of the nodeToDelete.
    if( nodeToDelete->prev != NULL ) {
        nodeToDelete->prev->next = nodeToDelete->next;
    }

    //The node to delete simply hangs in there in memory....
    //Free it.
    free(nodeToDelete);
}

/**
 * Check if an item exists in a given linked list.
 */
int exists(char aData[], struct Node *head) {
    if( head == NULL ) {
        return 0;
    }

    struct Node *current = head;
    while ( current != NULL) {
        if( strcmp(current->strData, aData) == 0 ) {
            return 1;
        }
        current = current->next;
    }
    return 0;
}

/**
 * A function to remove duplicates from a list
 **/
void removeDuplicates(struct Node *head) {
    struct Node *ptr1;
    struct Node *ptr2;
    struct Node *duplicate;
    ptr1 = head;

    while (ptr1 != NULL && ptr1->next != NULL)
    {
        ptr2 = ptr1;

        /* Compare the current element with rest of the elements */
        while (ptr2->next != NULL) {
            if ( strcmp(ptr1->strData, ptr2->next->strData) == 0 ) {
                duplicate = ptr2->next;
                ptr2->next = ptr2->next->next;
                free(duplicate);
            }
            else {
                ptr2 = ptr2->next;
            }
        }
        ptr1 = ptr1->next;
    }
}

/**
 * Convert an existing linked list to a linked list having unique elements.
 * It returns a new Linked List having unique items.
 * Technicallly speaking this is not a Set... but you get the idea... yeah?
 **/
struct Node * toSet(struct Node *head) {
    struct Node *newList = NULL;

    struct Node *current = head;
    while ( current != NULL) {
        if( !exists(current->strData, newList) ) {
            newList = push(current->strData, newList);
        }
        current = current->next;
    }

    return newList;
}

/**
 * Append a linked list to another. Go to last item o the appendToList and point the next pointer to the head of the appendee.
 **/
struct Node * append(struct Node *appendToList, struct Node *appendee) {
    struct Node *current = appendToList;
    while ( current->next != NULL) {
        current = current->next;
    }
    current->next = appendee;

    return appendToList;
}

int linkedListLength(struct Node *head) {
    struct Node *current = head;
    int ctr = 0;
    while ( current != NULL) {
        ctr++;
        current = current->next;
    }
    return ctr;
}


void logPrint(struct Node *head) {
    struct Node *current = head;
    while ( current != NULL) {
        printf("'%s', ", current->strData);
        current = current->next;
    }
}
