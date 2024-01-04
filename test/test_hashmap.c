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
    int test_value = 123;
    put(map, "testKey", &test_value, sizeof(int));

    int value = *(int*)get(map, "testKey");
    TEST_ASSERT_EQUAL_INT(123, value);

    freeHashMap(map);
}

void test_putAndGetWithCollision(void) {
    HashMap *map = createHashMap(HASHMAP_SIZE, NULL);
    int value1 = 123;
    int value2 = 456;
    put(map, "AB", &value1, sizeof(int));
    put(map, "BA", &value2, sizeof(int));

    int value = *(int*)get(map, "AB");
    TEST_ASSERT_EQUAL_INT(123, value);
    value = *(int*)get(map, "BA");
    TEST_ASSERT_EQUAL_INT(456, value);

    freeHashMap(map);
}

int dummy_hash_function(const char* input, size_t hashmap_size) {
    return 256;
}

void test_overflow(void) {
    HashMap *map = createHashMap(HASHMAP_SIZE, dummy_hash_function);
    int test_value = 123;
    put(map, "testKey", &test_value, sizeof(int));

    int value = *(int*)map->buckets[0]->value;
    TEST_ASSERT_EQUAL_INT(123, value);

    freeHashMap(map);
}

void test_support_string_type(void) {
    HashMap *map = createHashMap(HASHMAP_SIZE, dummy_hash_function);
    char* test_value = "hello";
    put(map, "testKey", &test_value, sizeof(test_value));

    char* value = *(char**)map->buckets[0]->value;
    TEST_ASSERT_EQUAL_STRING("hello", value);

    freeHashMap(map);

}

int main(void) {
    UNITY_BEGIN();
    RUN_TEST(test_createHashMap);
    RUN_TEST(test_putAndGet);
    RUN_TEST(test_putAndGetWithCollision);
    RUN_TEST(test_overflow);
    RUN_TEST(test_support_string_type);
    return UNITY_END();
}
