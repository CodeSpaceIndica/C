#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "linkedlist.h"

/**
 *  A Tree structure. This structure will behave like a Set having unique items only.
 **/
struct TNode
{
  char strData[MAX_LEN];
  size_t hash;

  struct TNode *left;
  struct TNode *right;
};

/**
 * Insert to Tree structure. 
 **/
void insertToTree(char aData[], struct TNode **leaf) {
    //If this is the root node, create a new leaf and set left and right to NULL
    size_t dHash = djbHash(aData);
    if( *leaf == NULL ) {
        *leaf = (struct TNode *)malloc( sizeof( struct TNode ) );

        strcpy((*leaf)->strData, aData);
        (*leaf)->hash = dHash;

        //initialize the children to null
        (*leaf)->left = NULL;
        (*leaf)->right = NULL;
    }
    //Add to left since data is smaller than leaf data
    //else if( strcmp((*leaf)->strData, aData) < 0 ) {
    else if( (*leaf)->hash < dHash ) {
        insertToTree( aData, &(*leaf)->left );
    }
    //Add to right since data is bigger than leaf data
    //else if( strcmp((*leaf)->strData, aData) > 0 ) {
    else if( (*leaf)->hash > dHash ) {
        insertToTree( aData, &(*leaf)->right );
    }
}

/**
 * Search for string in the tree struccture
 **/
struct TNode * searchTree(char aData[], struct TNode *leaf) {
    size_t dHash = djbHash(aData);
    if( leaf != NULL ) {
        //if( strcmp(leaf->strData, aData) == 0 ) {
        if( leaf->hash == dHash ) {
            return leaf;
        }
        //else if( strcmp(leaf->strData, aData) < 0 ) {
        else if( leaf->hash < dHash ) {
            return searchTree(aData, leaf->left);
        }
        else {
            return searchTree(aData, leaf->right);
        }
    }
    else {
        return NULL;
    }
}

/**
 * Just a way to print everyhing in the tree
 **/
void logPrintTree(struct TNode *leaf, int indendCtr, char which) {
    if( leaf != NULL ) {
        for(int i=0; i<indendCtr; i++) {
            printf(" ");
        }
        printf("%c %s\n", which, leaf->strData);
        ++indendCtr;
        logPrintTree(leaf->left, indendCtr, 'l');
        logPrintTree(leaf->right, indendCtr, 'r');
    }
}

/**
 * Count tree leaves
 **/
int countTreeLeaves(struct TNode* leaf) { 
    if(leaf == NULL) {
        return 0;
    }

    if(leaf->left == NULL && leaf->right == NULL) {
        return 1;
    }
    else {
        return countTreeLeaves(leaf->left) + countTreeLeaves(leaf->right) + 1;//add a 1 here becaue you hve to count THIS node as well.
    }
}

/**
 * Convert a liinked list to a binary tree, eliminating duplicates 
 **/
struct TNode * linkedListToTree(struct Node *head) {
    struct TNode *root = NULL;
    struct Node *current = head;
    while ( current != NULL) {
        insertToTree(current->strData, &root);
        current = current->next;
    }

    return root;
}
