//Compiled with gcc version 9.3.0 
//@Author: Code Space
//The Tree and Linked List are not written with best practices 
//for these data-structures in mind.
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "tree.h"//tree.h includes linked list.

//because of the way we find anagrams, this 
//list most likely will have duplicates
//Remove duplicates with the tree data structure
struct Node *allLengthWords = NULL;

/**
 * A function that uses recursion to find anagrams
 **/
struct Node * findAnagrams(char *aWord) {
    struct Node *wordList = NULL;
    //if the word length is only 2, we simply swap each letter with each other and return
    //values. Thus if the input was "AB"... we return "AB" and "BA".
    if( strlen(aWord) == 2 ) {
        char *temp = (char *)malloc(MAX_LEN * sizeof(char));
        strncat(temp, &aWord[0], 1);
        strncat(temp, &aWord[1], 1);
        wordList = push(temp, wordList);

        free(temp);
        temp = (char *)malloc(MAX_LEN * sizeof(char));
        strncat(temp, &aWord[1], 1);
        strncat(temp, &aWord[0], 1);
        wordList = push(temp, wordList);

        return wordList;//Return immediately
    }

    //If the word length is more than 2, then we first take a character out of the 
    //word... then find the anagram (recursively) of the rest of the characters.
    //Then join the first character back to the anagram results.
    //Thus if the input word was "ABC", we take the first character "A" and find 
    //anagrams of the rest of the characters which will be "BC" and "CB". Join
    //These values back with the original letter "A" we kept aside. This will give
    //values "ABC" and "ACB". Then we start over again with the letter "B" and the 
    //rest of the characters "AC".... and so on and so forth.
    int strLen = strlen(aWord);
    for(int i=0; i<strLen; i++) {
        char firstLetter = aWord[i];
        char *restOfLetters = (char *)malloc(MAX_LEN * sizeof(char));
        for(int j=0; j<strLen; j++) {
            if( i != j ) {
                strncat(restOfLetters, &aWord[j], 1);
            }
        }
        struct Node *miniAnagrams = findAnagrams(restOfLetters);
        while ( miniAnagrams != NULL) {
            char *fullWord = (char *)malloc(MAX_LEN * sizeof(char));
            strncat(fullWord, &firstLetter, 1);
            strcat(fullWord, miniAnagrams->strData);
            allLengthWords = push(miniAnagrams->strData, allLengthWords);

            wordList = push(fullWord, wordList);

            miniAnagrams = miniAnagrams->next;
        }
    }

    return wordList;
}

/**
 * Remember that the program name itself is argv[0].
 * 
 * **/
int main(int argc, char *argv[]) {
    if( argc < 2 ) {
        printf("Require a parameter. Parameter can be any word\n");
        exit(0);
    }
    struct timespec nanoStartTime, nanoEndTime;
    double timeTaken;

    char *theWord = argv[1];

    clock_gettime(CLOCK_REALTIME, &nanoStartTime);
    struct Node *anagrams = findAnagrams(theWord);

    struct Node *current = anagrams;
    while ( current != NULL) {
        allLengthWords = push(current->strData, allLengthWords);
        current = current->next;
    }

    clock_gettime(CLOCK_REALTIME, &nanoEndTime);

    timeTaken = ((nanoEndTime.tv_sec - nanoStartTime.tv_sec) * 1000) + ((nanoEndTime.tv_nsec - nanoStartTime.tv_nsec) / 1000000);
    printf("**** It took %lf milliseconds to find all anagrams\n", timeTaken);

    printf("Results had %d words of the same length\n", linkedListLength(anagrams));
    printf("Results had %d words in total\n\n", linkedListLength(allLengthWords));

    //Remove duplicates
    //struct Node *uniqueAnagrams = toSet(allLengthWords);
    //removeDuplicates(allLengthWords);
    clock_gettime(CLOCK_REALTIME, &nanoStartTime);
    struct TNode *treeRoot = linkedListToTree(allLengthWords);
    clock_gettime(CLOCK_REALTIME, &nanoEndTime);

    timeTaken = ((nanoEndTime.tv_sec - nanoStartTime.tv_sec) * 1000) + ((nanoEndTime.tv_nsec - nanoStartTime.tv_nsec) / 1000000);
    printf("**** It took %lf milliseconds to remove duplicates\n", timeTaken);
    printf("After removing duplicates, results had %d words of all lengths\n\n", countTreeLeaves(treeRoot));

    //Find meanings
    FILE *fileIn = fopen("allwords.txt", "r");
    fseek(fileIn, 0L, SEEK_END);
    int fileSize = ftell(fileIn);
    fseek(fileIn, 0L, SEEK_SET);

    char *fileContents = (char*)malloc(fileSize + 1);
    size_t size = fread(fileContents, 1, fileSize, fileIn);
    fileContents[size] = 0;
    fclose(fileIn);

    clock_gettime(CLOCK_REALTIME, &nanoStartTime);
    char *splitted = strtok(fileContents, ",");
    struct Node *englishWords = NULL;
    while( splitted != NULL ) {
        struct TNode * srchResult = searchTree(splitted, treeRoot);
        if( srchResult != NULL ) {
            englishWords = push(splitted, englishWords);
        }
        splitted = strtok(NULL, ",");
    }
    clock_gettime(CLOCK_REALTIME, &nanoEndTime);
    timeTaken = ((nanoEndTime.tv_sec - nanoStartTime.tv_sec) * 1000) + ((nanoEndTime.tv_nsec - nanoStartTime.tv_nsec) / 1000000);
    printf("**** It took %lf milliseconds to filter words.\n", timeTaken);
    printf("There are %d real English words. They are :", linkedListLength(englishWords));
    logPrint(englishWords);
    printf("\n");
}
