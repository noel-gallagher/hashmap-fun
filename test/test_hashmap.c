#include "unity.h"
#include "hashmap.h"

void setUp(void) {}

void tearDown(void) {}

void test_createHashMap(void) {
    HashMap *map = createHashMap(HASHMAP_SIZE, NULL);
    TEST_ASSERT_NOT_NULL(map);
    freeHashMap(map);
}

void test_putAndGet(void) {
    HashMap *map = createHashMap(HASHMAP_SIZE, NULL);
    put(map, "testKey", 123);

    int value = get(map, "testKey");
    TEST_ASSERT_EQUAL_INT(123, value);

    freeHashMap(map);
}

void test_putAndGetWithCollision(void) {
    HashMap *map = createHashMap(HASHMAP_SIZE, NULL);
    put(map, "AB", 123);
    put(map, "BA", 456);

    int value = get(map, "AB");
    TEST_ASSERT_EQUAL_INT(123, value);
    value = get(map, "BA");
    TEST_ASSERT_EQUAL_INT(456, value);

    freeHashMap(map);
}

int dummy_hash_function(const char* input, size_t hashmap_size) {
    return 256;
}

void test_overflow(void) {
    HashMap *map = createHashMap(HASHMAP_SIZE, dummy_hash_function);
    put(map, "testKey", 123);

    int value = map->buckets[0]->value;
    TEST_ASSERT_EQUAL_INT(123, value);

    freeHashMap(map);
}


int main(void) {
    UNITY_BEGIN();
    RUN_TEST(test_createHashMap);
    RUN_TEST(test_putAndGet);
    RUN_TEST(test_putAndGetWithCollision);
    RUN_TEST(test_overflow);
    return UNITY_END();
}
