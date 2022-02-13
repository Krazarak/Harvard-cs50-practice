// Implements a dictionary's functionality

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <strings.h>
#include <ctype.h>
#include "dictionary.h"

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
}
node;

// Number of buckets in hash table
const unsigned int N = 26;

// Hash table
node *table[N];

// size of dictionary
int dict_size = 0;

// Returns true if word is in dictionary, else false
bool check(const char *word)
{
    // check hash number of word
    int hash_number = hash(word);
    // access linked list from hash_number location in hash table
    node *w = table[hash_number];
    // check each word in linked list for match until reached the end
    while (w != NULL)
    {
        if (strcasecmp(word, w->word) == 0)
        {
            return true;
        }
        w = w->next;
    }
    return false;
}
// Hashes word to a number
unsigned int hash(const char *word)
{
    unsigned int hash = 0;
    for (int i = 0 ; word[i] != '\0' ; i++)
    {
        hash = 31 * hash + tolower(word[i]);
    }
    return hash % N;
}
// Loads dictionary into memory, returning true if successful, else false
bool load(const char *dictionary)
{
    // open dictionary
    FILE *dictionary_pointer = fopen(dictionary, "r");
    // check if pointer is null
    if (dictionary_pointer == NULL)
    {
        printf("Failed to open %s\n", dictionary);
        return false;
    }
    // initialize char array to store next word
    char word[LENGTH + 1];
    // scan through each string in dictionary
    while (fscanf(dictionary_pointer, "%s", word) != EOF)
    {
        // malloc memory for node for each word
        node *w = malloc(sizeof(node));
        if (w == NULL)
        {
            return false;
        }
        // copy word into node
        strcpy(w->word, word);
        // retreive hash number of next word
        int hash_number = hash(word);
        // insert node into hash table
        w->next = table[hash_number];
        table[hash_number] = w;
        // increment count for size function
        dict_size++;
    }
    fclose(dictionary_pointer);
    return true;
}
// Returns number of words in dictionary if loaded, else 0 if not yet loaded
unsigned int size(void)
{
    return dict_size;
}
// Unloads dictionary from memory, returning true if successful, else false
bool unload(void)
{
    // loop through each linked list (N) of hash table
    for (int i = 0; i < N; i++)
    {
        // initialize head node for current linked list
        node *w = table[i];
        // loop through linked list
        while (w != NULL)
        {
            // initialize temp node to point at current node (as not to lose head node)
            node *tmp = w;
            // point head node towards next node
            w = w->next;
            // free temp node
            free(tmp);
        }
        if (w == NULL && i == N - 1)
        {
            return true;
        }
    }
    return false;
}