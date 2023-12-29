#include "hashmap.h"
#include <stdlib.h>
#include <string.h>

KeyValuePair *createKeyValuePair() {
    KeyValuePair *kvp = malloc(sizeof(KeyValuePair));
    kvp->key = NULL;
    kvp->value = 0;
    kvp->next = NULL;
    return kvp;
}

KeyValuePair* createKeyValuePairWithValues(const char* key, int value) {
    KeyValuePair *kvp = malloc(sizeof(KeyValuePair));
    kvp->key = strdup(key);
    kvp->value = value;
    kvp->next = NULL;
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

HashMap* createHashMap() {
    HashMap *map = malloc(sizeof(HashMap));
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
    while(key[i]) {
        sum += key[i];
        i++;
    }
    return sum % HASHMAP_SIZE;
}

void put(HashMap *map, const char *key, int value) {
    int index = hash(key); 
    //collision
    KeyValuePair* kvp = createKeyValuePairWithValues(key, value);
    if(map->buckets[index] == NULL) {
        map->buckets[index] = kvp;
    }
    else {
        KeyValuePair* current = map->buckets[index];
        while(current->next){
           current = current->next; 
        }
        current->next = kvp;
    }
    
}

int get(const HashMap *map, const char *key) {
    int index = hash(key);
    KeyValuePair* current = map->buckets[index];
    KeyValuePair* next = current;
    while(next && strcmp(current->key, key) != 0) {
        current = next;
        next = next->next;
    }
    int value = current->value;
    return value;
}

