// Implements a dictionary's functionality

#include <ctype.h>
#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <strings.h>

#include "dictionary.h"

//size
int sizereturn = 0;

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
}
node;

// TODO: Choose number of buckets in hash table
const unsigned int N = 676;

// Hash table
node *table[N];

// Returns true if word is in dictionary, else false
bool check(const char *word)
{
    // TODO
    int index = hash(word);
    node *temp = table[index];
    while (temp != NULL)
    {
        if (strcasecmp(table[index]->word, word) == 0)
        {
            return true;
        }
        temp = temp->next;
    }
    return false;
}

// Hashes word to a number
unsigned int hash(const char *word)
{
    // TODO: Improve this hash function
    int index = 0;
    int length = strlen(word);

    if (length == 1)
    {

        if ((word[0] >= 65 && word[0] <= 90) || (word[0] >= 97 && word[0] <= 122))
        {

            index = (int)((toupper(word[0]) - 'A') * 26);

        }

    }
    else if (length >= 2)
    {

        if ((word[0] >= 65 && word[0] <= 90) || ((word[0] >= 97 && word[0] <= 122) && (word[1] >= 65 && word[1] <= 90)) || (word[1] >= 97
                 && word[1] <= 122))
        {

            index = (int)(((toupper(word[0]) - 'A') * 26) + (toupper(word[1]) - 'A'));

        }
    }

    return index;

}

// Loads dictionary into memory, returning true if successful, else false
bool load(const char *dictionary)
{
    // TODO

    //hash table: table[N]

    //open file
    FILE *dict = fopen(dictionary, "r");
    if (dict == NULL)
    {
        return false;
    }

    //word buffer
    char word[LENGTH + 1];

    //read strings from file one at a time
    while (fscanf(dict, "%s", word) != EOF)
    {

        //create new node
        node *temp = malloc(sizeof(node));
        if (temp == NULL)
        {
            return false;
        }

        strcpy(temp->word, word);

        //hash word for index
        int index = hash(word);

        //Insert Node into Hash table
        temp->next = table[index];
        table[index] = temp;

        //update size
        sizereturn++;

    }
    fclose(dict);
    return true;
}

// Returns number of words in dictionary if loaded, else 0 if not yet loaded
unsigned int size(void)
{
    // TODO
    return sizereturn;
}

// Unloads dictionary from memory, returning true if successful, else false
bool unload(void)
{
    // TODO
    for (int i = 0; i < N; i++)
    {
        node *cursor = table[i];
        while (cursor != NULL)
        {
            node *temp = cursor;
            cursor = cursor->next;
            free(temp);
        }
    }

    return true;
}
