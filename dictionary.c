/**
 * dictionary.c
 *
 * Computer Science 50
 * Problem Set 5
 *
 * Implements a dictionary's functionality.
 */

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <ctype.h>
#include <string.h>

#include "dictionary.h"


//Returns true if word is in dictionary else false.

bool check(const char* word, Node *head)
{
    int n = strlen(word);
    int d = 0;

    for (int i = 0; i < n; i++){

        d = (int) word[i];

        if(d == 39)
            d = 0;
        else {
            if (d < 97){
                d+=32;
            }
            d-=96;
        }


        if (head->letter[d] != NULL){
            head = head->letter[d];
        }
        else{
            return false;
        }
    }

    if (head->is_word == true){
        return true;
    }

    return false;
}

/*/
 * Loads dictionary into memory.  Returns true if successful else false.
**/


bool load(const char* dictionary, Node **head)
{
    Node *root, *p;
    root = (Node*) malloc (sizeof (Node));
    p = root;

    int index = 0;
    FILE* fp = fopen(dictionary, "r");

    if (fp == NULL){
        printf("Couldn't openc%s.\n", dictionary);
        return false;
    }

    for (int c = fgetc(fp); c != EOF; c = fgetc(fp)){

        Node *tmp = (Node*) malloc (sizeof(Node));
        int d = c;

        if(d == 39)
            d = 0;
        else {
            if (d < 97){
                d+=32;
            }
            d-=96;
        }

        if ((isalpha(c) && index == 0) || (c == '\'' && index == 0)){

            p = root;
            if(p->letter[d] == NULL){
                p->letter[d] = tmp;
                p = p->letter[d];
            }
            else
                p = p->letter[d];

            index++;
        }
        else if((isalpha(c) && index > 0) || (c == '\'' && index > 0)){

            if(p->letter[d] == NULL){
                p->letter[d] = tmp;
                p = p->letter[d];
            }
            else
                p = p->letter[d];

        }
        else if (index > 0){
            p->is_word = true;
            index = 0;
        }
    }

    *head = root;

    if(fgetc(fp) == EOF){
        return true;
    }
    return false;
}

/*
 * Returns number of words in dictionary if loaded else 0 if not yet loaded.
 */


unsigned int size(void)
{
    // TODO
    return 0;
}

/*
 * Unloads dictionary from memory.  Returns true if successful else false.
 */


bool unload(Node *head)
{
    Node *prev = NULL;
    bool check = true;

    if(head == NULL)
        return false;

    for (int i = 0; i < 27; i++){

        if(check == false)
            return false;

        if(prev != NULL)
            head = prev;

        if (head->letter[i] != NULL){
            prev = head;
            head = head->letter[i];
            check = unload(head);
        }
    }

    if(prev == NULL){
        free(head);
        return true;
    }
    else{
        free(prev);
        return true;
    }
}
