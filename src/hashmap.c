#include "hashmap.h"
#include <stdlib.h>
#include <string.h>

KeyValuePair *createKeyValuePair() {
    KeyValuePair *kvp = malloc(sizeof(KeyValuePair));
    kvp->key = NULL;
    kvp->value = 0;
    return kvp;
}

KeyValuePair* createKeyValuePairWithValues(const char* key, int value) {
    KeyValuePair *kvp = malloc(sizeof(KeyValuePair));
    kvp->key = strdup(key);
    kvp->value = value;
    return kvp;
}

void freeKeyValuePair(KeyValuePair *kvp)
{
    if(kvp)
    {
        if(kvp->key)
        {
             free(kvp->key);
        }
        free(kvp);
    }
}

HashMap* createHashMap(HashFunction hashfunction) {
    HashMap *map = malloc(sizeof(HashMap));
    if(hashfunction == NULL)
    {
        map->hashfunction = hash;
    }
    else 
    {
        map->hashfunction = hashfunction;
    }
    for(int i = 0; i < HASHMAP_SIZE; i++)
    {
        map->buckets[i] = NULL;
    }
    
    return map;
}

void freeHashMap(HashMap *hmap) {
    for(int i = 0; i < HASHMAP_SIZE; i++)
    {
        KeyValuePair *cur_bucket = hmap->buckets[i];
        freeKeyValuePair(cur_bucket);
    }
    
    free(hmap);
}

// hashing function
// quick and easy...compute sum of ascii vals and mod by array size 
int hash(const char *key) {
    int i = 0, sum = 0;
    while(key[i]) 
    {
        sum += key[i];
        i++;
    }
    
    return sum % HASHMAP_SIZE;
}

void put(HashMap *map, const char *key, int value) {
    int index = map->hashfunction(key); 
    KeyValuePair* kvp = createKeyValuePairWithValues(key, value);
    for(int i = 0; i < HASHMAP_SIZE; i++) 
    {
        int startIndex = (index + i) % HASHMAP_SIZE;
        if(map->buckets[startIndex] == NULL ) 
        {
            map->buckets[startIndex] = kvp;
            return;
        }
    }
}

int get(const HashMap *map, const char *key) {
    int index = map->hashfunction(key);
    for(int i = 0; i < HASHMAP_SIZE; i++) 
    {
        int currentIndex = (index + i) % HASHMAP_SIZE;
        KeyValuePair* current = map->buckets[currentIndex];
        if(current == NULL)
        {
            return -1;
        }
        if(current->key != NULL && strcmp(current->key, key) == 0)
        {
            return current->value;   
        }
    }

    return -1;
}

