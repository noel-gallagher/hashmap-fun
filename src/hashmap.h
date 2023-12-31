#ifndef HASHMAP_H
#define HASHMAP_H

#include <stddef.h>

#define HASHMAP_SIZE 256

typedef int (*HashFunction)(const char* key, size_t hmap_size);

typedef struct KeyValuePair {
	char *key;
	int value;
	struct KeyValuePair *next;
} KeyValuePair;

typedef struct {
    size_t hashmap_size;
    HashFunction hashfunction; 
    KeyValuePair **buckets; 
} HashMap;

HashMap* createHashMap();
void freeHashMap(HashMap *hmap);
int hash(const char *key, size_t hashmap_size);
void put(HashMap *map, const char *key, int value);
int get(const HashMap *map, const char *key);

#endif

