#include "unity.h"
#include "hashmap.h"

void setUp(void) {}

void tearDown(void) {}

void test_createHashMap(void) {
    HashMap *map = createHashMap();
    TEST_ASSERT_NOT_NULL(map);
    freeHashMap(map);
}

void test_putAndGet(void) {
    HashMap *map = createHashMap();
    put(map, "testKey", 123);

    int value = get(map, "testKey");
    TEST_ASSERT_EQUAL_INT(123, value);

    freeHashMap(map);
}

int main(void) {
    UNITY_BEGIN();
    RUN_TEST(test_createHashMap);
    RUN_TEST(test_putAndGet);
    return UNITY_END();
}
