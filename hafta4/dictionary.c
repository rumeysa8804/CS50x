// Implements a dictionary's functionality

#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include<strings.h>
#include<string.h>
#include<stdlib.h>
#include<cs50.h>

#include "dictionary.h"

// Represents number of buckets in a hash table
#define N 26

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
}
node;

// Represents a hash table
node *hashtable[N];
unsigned int hash_deger;
unsigned int bulunan_sozcuk;
// Hashes word to a number between 0 and 25, inclusive, based on its first letter
unsigned int hash(const char *word)
{
    return tolower(word[0]) - 'a';
}

// Loads dictionary into memory, returning true if successful else false
bool load(const char *dictionary)
{
    // Initialize hash table
    for (int i = 0; i < N; i++)
    {
        hashtable[i] = NULL;
    }

    // Open dictionary
    FILE *file = fopen(dictionary, "r");
    if (file == NULL)
    {
        unload();
        return false;
    }

    // Buffer for a word
    char word[LENGTH + 1];
    // Insert words into hash table
    while (fscanf(file, "%s", word) != EOF)
    {
        // TODO

       struct node *new_node=malloc(sizeof(node));
       if(new_node!=NULL)
       {

         strcpy(new_node->word,word);
         
         hash_deger=hash(word);
         
         new_node->next=hashtable[hash_value];
         
         hashtable[hash_deger]=new_node;
         
         bulunan_sozcuk++;

       }

       else
       {
           unload();
           return false;
       }

    }

    // Close dictionary
    fclose(file);

    // Indicate success
    return true;
}

// Returns number of words in dictionary if loaded else 0 if not yet loaded
unsigned int size(void)
{
    // TODO
    if(bulunan_sozcuk>0)
    {
        return bulunan_sozcuk;
    }
    else
    {
    return 0;
    }
}

// Returns true if word is in dictionary else false
bool check(const char *word)
{
    // TODO
    hash_deger=hash(word);
    struct node *cursor=hashtable[hash_deger];
    
    while(cursor!=NULL)
    {
        if(strcasecmp(word,cursor->word)==0)
        {
            return true;
        }
        cursor=cursor->next;
    }
    return false;
}

// Unloads dictionary from memory, returning true if successful else false
bool unload(void)
{
    // TODO
    for(int i=0;i<N;i++)
    {
        struct node *cursor=hashtable[i];
        
        while(cursor)
        {
            struct node *temp=cursor;
            cursor=cursor->next;
            free(temp);
        }
        
        if(i==N-1&&cursor==NULL)
        {
            return true;
        }
    }
    return false;
}
