/**
 * dictionary.h
 *
 * Computer Science 50
 * Problem Set 5
 *
 * Declares a dictionary's functionality.
 */

#ifndef DICTIONARY_H
#define DICTIONARY_H

#include <stdbool.h>

// maximum length for a word
// (e.g., pneumonoultramicroscopicsilicovolcanoconiosis)
#define LENGTH 45

typedef struct Node
{
    bool is_word;
    struct Node *letter[27];
} Node;

bool check(const char* word, Node *head);

bool load(const char* dictionary, Node **head);

/*
 * Returns number of words in dictionary if loaded else 0 if not yet loaded.
 */
unsigned int size(void);

/*
 * Unloads dictionary from memory.  Returns true if successful else false.
 */
bool unload(Node *head);

#endif // DICTIONARY_H
