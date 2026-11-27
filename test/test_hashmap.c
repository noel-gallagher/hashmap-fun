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

void test_deleteFromFullWrapped(void) {
    HashMap *map = createHashMap(4, NULL);
    int value = 123;
    put(map, "A", &value, sizeof(value));
    put(map, "B", &value, sizeof(value));
    put(map, "E", &value, sizeof(value));
    put(map, "I", &value, sizeof(value));

    void *b = get(map, "B");
    void *e = get(map, "E");
    void *i = get(map, "I");
    TEST_ASSERT_NOT_NULL(b);
    TEST_ASSERT_NOT_NULL(e);
    TEST_ASSERT_NOT_NULL(i);

    TEST_ASSERT_TRUE(deleteKey(map, "A"));
    TEST_ASSERT_NULL(get(map, "A"));
    TEST_ASSERT_FALSE(deleteKey(map, "A"));
    TEST_ASSERT_EQUAL_PTR(b, get(map, "B"));
    TEST_ASSERT_EQUAL_PTR(e, get(map, "E"));
    TEST_ASSERT_EQUAL_PTR(i, get(map, "I"));

    put(map, "D", &value, sizeof(value));
    TEST_ASSERT_NOT_NULL(get(map, "D"));
    freeHashMap(map);
}

void test_deleteOnlyFirstMatchingEntry(void) {
    HashMap *map = createHashMap(2, NULL);
    int first = 12;
    int second = 34;
    put(map, "key", &first, sizeof(first));
    put(map, "key", &second, sizeof(second));
    TEST_ASSERT_TRUE(deleteKey(map, "key"));

    int *value = get(map, "key");
    TEST_ASSERT_NOT_NULL(value);
    TEST_ASSERT_EQUAL_INT(second, *value);
    TEST_ASSERT_TRUE(deleteKey(map, "key"));
    TEST_ASSERT_NULL(get(map, "key"));
    TEST_ASSERT_FALSE(deleteKey(map, "key"));

    freeHashMap(map);
}

int main(void) {
    UNITY_BEGIN();
    RUN_TEST(test_createHashMap);
    RUN_TEST(test_putAndGet);
    RUN_TEST(test_putAndGetWithCollision);
    RUN_TEST(test_overflow);
    RUN_TEST(test_support_string_type);
    RUN_TEST(test_deleteFromFullWrapped);
    RUN_TEST(test_deleteOnlyFirstMatchingEntry);
    return UNITY_END();
}
