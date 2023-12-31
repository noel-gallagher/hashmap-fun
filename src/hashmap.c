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

HashMap* createHashMap(size_t hashmap_size, HashFunction hashfunction) {
    HashMap *map = malloc(sizeof(HashMap));
    map->hashmap_size = hashmap_size;
    map->buckets = malloc(hashmap_size * sizeof(KeyValuePair*));
    if(hashfunction == NULL)
    {
        map->hashfunction = hash;
    }
    else 
    {
        map->hashfunction = hashfunction;
    }
    for(size_t i = 0; i < map->hashmap_size; i++)
    {
        map->buckets[i] = NULL;
    }
    
    return map;
}

void freeHashMap(HashMap *hmap) {
    for(size_t i = 0; i < hmap->hashmap_size; i++)
    {
        KeyValuePair *cur_bucket = hmap->buckets[i];
        freeKeyValuePair(cur_bucket);
    }
    free(hmap->buckets); 
    free(hmap);
}

// hashing function
// quick and easy...compute sum of ascii vals and mod by array size 
int hash(const char *key, size_t hashmap_size) {
    int i = 0, sum = 0;
    while(key[i]) 
    {
        sum += key[i];
        i++;
    }
    
    return sum % hashmap_size;
}

void put(HashMap *map, const char *key, int value) {
    int index = map->hashfunction(key, map->hashmap_size); 
    KeyValuePair* kvp = createKeyValuePairWithValues(key, value);
    for(size_t i = 0; i < map->hashmap_size; i++) 
    {
        int startIndex = (index + i) % map->hashmap_size;
        if(map->buckets[startIndex] == NULL ) 
        {
            map->buckets[startIndex] = kvp;
            return;
        }
    }
}

int get(const HashMap *map, const char *key) {
    int index = map->hashfunction(key, map->hashmap_size);
    for(size_t i = 0; i < map->hashmap_size; i++) 
    {
        int currentIndex = (index + i) % map->hashmap_size;
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

