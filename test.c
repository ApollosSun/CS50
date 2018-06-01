#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <ctype.h>
#include <string.h>

#define DICTIONARY "dictionaries/small"


typedef struct Node
{
    bool is_word;
    struct Node *letter[27];
} Node;

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
            printf("\n");
            p = root;
            if(p->letter[d] == NULL){
                p->letter[d] = tmp;
                p = p->letter[d];
            }
            else
                p = p->letter[d];

            index++;
            printf("%c ", (char)c);
        }
        else if((isalpha(c) && index > 0) || (c == '\'' && index > 0)){

            if(p->letter[d] == NULL){
                p->letter[d] = tmp;
                p = p->letter[d];
            }
            else
                p = p->letter[d];


            printf("%c ", (char)c);
        }
        else if (index > 0){
            p->is_word = true;
            index = 0;
            printf("- it's new word");
        }
    }

    *head = root;

    if(fgetc(fp) == EOF){
        printf("\n\nComplete!\n\n");
    }
    return false;
}
/////

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
            printf("found letter %d\n",d);
        }
        else{
            printf("no letter \n");
            return false;
        }
    }

    if (head->is_word == true){
        return true;
    }

    return false;
}

/////

bool unload(Node *head)
{
    Node *prev = NULL;
    bool check = true;
    //printf("enter to func \n");

    if(head == NULL)
        return false;

    for (int i = 0; i < 27; i++){

        if(check == false)
            return false;

        if(prev != NULL)
            head = prev;

        //printf("loop %d adress - %x\n", i, (int)head->letter[i]);

        if (head->letter[i] != NULL){
            prev = head;
            head = head->letter[i];
            check = unload(head);

            //printf("step %d\n",i);
        }

    }
    //printf("it seems like going to free\n");
    if(prev == NULL){
        free(head);
        return true;
    }
    else{
        free(prev);
        return true;
    }
    //printf("free\n");

    return false;
}

/////
int main(int argc, char* argv[]){
    Node *p;
    char* dictionary = (argc == 3) ? argv[1] : DICTIONARY;
    bool res = load(dictionary, &p);

    for (int i = 0; i < 27; i++){
        if(p->letter[i] != NULL){
            printf("Array 1 (main), letter %d - exist\n", i);
        }
        else
            printf("Array 1 (main), letter %d - doesn't exist\n", i);
    }

    char *word = "abc";

    res = check(word, p);

    if(res){
        printf("word exist! Well Done! \n\n");
    }
    else
        printf("looser!\n\n");

    word = "the";
    res = check(word, p);

    if(res){
        printf("word exist! Well Done! \n\n");
    }
    else
        printf("looser!\n\n");

    word = "apple";
    res = check(word, p);

    if(res){
        printf("word exist! Well Done! \n\n");
    }
    else
        printf("looser!\n\n");



    res = unload(p);

    if(res){
        printf("Memory is free! Well Done! \n");
    }
    else
        printf("Error. Memory isn't free!\n");


/*
    //Does word exist?

    if(p->is_word != false){
        printf("word\n");
    }
    else
        printf("nothing\n");

    p = p->letter[3];

    if(p->is_word != false){
        printf("word\n");
    }
    else
        printf("nothing\n");

    p = p->letter[1];

    if(p->is_word != false){
        printf("word\n");
    }
    else
        printf("nothing\n");

    p = p->letter[20];

    if(p->is_word != false){
        printf("word\n");
    }
    else
        printf("nothing\n");


    //Does letter exist?

    if(p->letter[2] != NULL){
        printf("Letter B exist\n");
        p = p->letter[2];
    }
    else
        printf("Letter B doesn't exist\n");

    if(p->letter[2] != NULL){
        printf("Letter B exist\n");
        p = p->letter[2];
    }
    else
        printf("Letter B doesn't exist\n");
*/
/*

    //Check existence words in arrays

    for (int i = 0; i < 27; i++){
        if(p->letter[i] != NULL){
            printf("Array 1 (main), letter %d - exist\n", i);
        }
        else
            printf("Array 1 (main), letter %d - doesn't exist\n", i);
    }
    p = p->letter[1];

    for (int i = 0; i < 27; i++){
        if(p->letter[i] != NULL){
            printf("Array 2 (A), letter %d - exist\n", i);
        }
        else
            printf("Array 2 (A), letter %d - doesn't exist\n", i);
    }
    p = p->letter[2];

    for (int i = 0; i < 27; i++){
        if(p->letter[i] != NULL){
            printf("Array 3 (B), letter %d - exist\n", i);
        }
        else
            printf("Array 3 (B), letter %d - doesn't exist\n", i);
    }
    p = p->letter[3];

    for (int i = 0; i < 27; i++){
        if(p->letter[i] != NULL){
            printf("Array 4 (C), letter %d - exist\n", i);
        }
        else
            printf("Array 4 (C), letter %d - doesn't exist\n", i);
    }
    p = p->letter[4];

    for (int i = 0; i < 27; i++){
        if(p->letter[i] != NULL){
            printf("Array 5 (D), letter %d - exist\n", i);
        }
        else
            printf("Array 5 (D), letter %d - doesn't exist\n", i);
    }
*/
    res = false;
    return 0;
}