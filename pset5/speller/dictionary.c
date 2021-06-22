// Implements a dictionary's functionality

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
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

int totalWords = 0;


// Returns true if word is in dictionary else false
bool check(const char *word)
{
    // i represents the current node of LinkedList
    node *i = table[hash(word)];

    while (i != NULL)
    {
        // Compare word from dictionary
        if (strcasecmp(i->word, word) == 0)
        {
            return true;
        }

        i = i->next;
    }

    return false;
}

// Hashes word to a number
unsigned int hash(const char *word)
{
    // a = 0, b = 1, c = 2 ..., z = 25
    return (int)tolower(word[0]) - 97;
}

// Loads dictionary into memory, returning true if successful else false
bool load(const char *dictionary)
{

    FILE *dictFile = fopen(dictionary, "r");
    char *dictWord = malloc(LENGTH + 1);

    // If File could not be read or
    // Point could not be created, return false
    if (dictFile == NULL || dictWord == NULL)
    {
        return false;
    }

    // Start to load the file and save wors in the hash table.
    while (fscanf(dictFile, "%s", dictWord) != EOF)
    {
        // Create a New Node
        node *new_node = malloc(sizeof(node));

        if (new_node == NULL)
        {
            return false;
        }

        // Copy a word from file
        strcpy(new_node->word, dictWord);
        new_node->next = NULL;

        // Get the index of Hash table
        int idx = hash(dictWord);

        if (table[idx] != NULL)
        {
            // 1. NewNode -> OldNode -> OldNOde (ab->a)
            // 2. Index -> NewNode -> OldNode   (ac->ab->a)

            new_node->next = table[idx];
            table[idx] = new_node;
        }
        else
        {
            // NewNode -> Index
            table[idx] = new_node;
        }

        // Count the word in dictionary
        totalWords++;
    }

    free(dictWord);
    fclose(dictFile);

    return true;
}


// Returns number of words in dictionary if loaded else 0 if not yet loaded
unsigned int size(void)
{
    return totalWords;
}

// Unloads dictionary from memory, returning true if successful else false
bool unload(void)
{
    node *head = NULL;
    node *tmp = NULL;
    node *cursor = NULL;

    for (int i = 0; i < N; i++)
    {
        // Head represents the Index
        head = table[i];

        // Both cursor and tmp start from Index
        cursor = head;
        tmp = head;

        while (cursor != NULL)
        {
            // Go cursor to next
            cursor = cursor->next;

            // Then value from tmp can be free
            free(tmp);
            tmp = cursor;
        }
    }

    return true;
}
