#ifndef HASHMAP_H
#define HASHMAP_H

#include <stddef.h>

#define HASHMAP_SIZE 256

typedef int (*HashFunction)(const char* key);

typedef struct KeyValuePair {
	char *key;
	int value;
	struct KeyValuePair *next;
} KeyValuePair;

typedef struct {
    HashFunction hashfunction; 
    KeyValuePair *buckets[HASHMAP_SIZE]; 
} HashMap;

HashMap* createHashMap();
void freeHashMap(HashMap *hmap);
int hash(const char *key);
void put(HashMap *map, const char *key, int value);
int get(const HashMap *map, const char *key);

#endif

