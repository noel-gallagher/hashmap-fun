#include "hashmap.h"
#include <stdlib.h>
#include <string.h>

KeyValuePair* createKeyValuePairWithValues(const char* key, const void* value, size_t size) {
    KeyValuePair *kvp = malloc(sizeof(KeyValuePair));
    kvp->key = strdup(key);
    kvp->value = malloc(size);
    memcpy(kvp->value, value, size);
    kvp->size = size;
    return kvp;
}

void freeKeyValuePair(KeyValuePair *kvp)
{
    if(kvp)
    {
        free(kvp->key);
        free(kvp->value);
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

static size_t homeBucket(const HashMap *map, const char *key) {
    size_t capacity = map->hashmap_size;
    return capacity == 0 ? 0 : (size_t)map->hashfunction(key, capacity) % capacity;
}

void put(HashMap *map, const char *key, void *value, size_t size) {
    size_t capacity = map->hashmap_size;
    size_t index = homeBucket(map, key);
    for (size_t scanned = 0; scanned < capacity; scanned++) {
        if (map->buckets[index] == NULL) {
            map->buckets[index] = createKeyValuePairWithValues(key, value, size);
            return;
        }
        index = (index + 1) % capacity;
    }
}

static size_t findBucket(const HashMap *map, const char *key) {
    size_t capacity = map->hashmap_size;
    size_t index = homeBucket(map, key);
    for (size_t scanned = 0; scanned < capacity; scanned++) {
        KeyValuePair *entry = map->buckets[index];
        if (entry == NULL) {
            break;
        }
        if (entry->key != NULL && strcmp(entry->key, key) == 0) {
            return index;
        }
        index = (index + 1) % capacity;
    }
    return capacity;
}

void* get(const HashMap *map, const char *key) {
    size_t index = findBucket(map, key);
    return index == map->hashmap_size ? NULL : map->buckets[index]->value;
}

static size_t probeDistance(size_t home, size_t index, size_t capacity) {
    return index >= home ? index - home : capacity - (home - index);
}

bool deleteKey(HashMap *map, const char *key) {
    size_t capacity = map->hashmap_size;
    size_t hole = findBucket(map, key);
    if (hole == capacity) {
        return false;
    }

    freeKeyValuePair(map->buckets[hole]);
    map->buckets[hole] = NULL;

    size_t index = (hole + 1) % capacity;
    for (size_t scanned = 1; scanned < capacity && map->buckets[index] != NULL; scanned++) {
        KeyValuePair *entry = map->buckets[index];
        size_t home = homeBucket(map, entry->key);

        if (probeDistance(home, hole, capacity) < probeDistance(home, index, capacity)) {
            map->buckets[hole] = entry;
            map->buckets[index] = NULL;
            hole = index;
        }
        index = (index + 1) % capacity;
    }

    return true;
}
