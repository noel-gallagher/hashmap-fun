#include <stdio.h>
#include "hashmap.h"

int main() {
    HashMap *myMap = createHashMap(HASHMAP_SIZE, NULL);

    int value1 = 100;
    int value2 = 200;
    int value3 = 300;
    put(myMap, "key1", &value1, sizeof(int));
    put(myMap, "key2", &value2, sizeof(int));
    put(myMap, "key3", &value3, sizeof(int));

    int value;
    value = *(int*)get(myMap, "key1");
    if (value) printf("key1: %d\n", value);
    value = *(int*)get(myMap, "key2");
    if (value) printf("key2: %d\n", value);
    value = *(int*)get(myMap, "key3");
    if (value) printf("key3: %d\n", value);

    freeHashMap(myMap);

    return 0;
}

