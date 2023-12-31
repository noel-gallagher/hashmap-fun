#include <stdio.h>
#include "hashmap.h"

int dummy_hash_function(const char* input)
{
    return 256;
}

int main() {
    HashMap *myMap = createHashMap(NULL);

    put(myMap, "key1", 100);
    put(myMap, "key2", 200);
    put(myMap, "key3", 300);

    int value;
    value = get(myMap, "key1");
    if (value) printf("key1: %d\n", value);
    value = get(myMap, "key2");
    if (value) printf("key2: %d\n", value);
    value = get(myMap, "key3");
    if (value) printf("key3: %d\n", value);

    freeHashMap(myMap);

    return 0;
}

