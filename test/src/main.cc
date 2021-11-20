#include <gtest/gtest.h>
#include <string.h>

extern "C" {
#include "hashtable.h"
}

TEST(HashTableTest, ShouldCreate) {
    struct hashtable *table = hashtable_new();

    ASSERT_NE((struct hashtable *)NULL, table);

    ASSERT_EQ(table->size, 0);
    ASSERT_EQ(table->capacity, HASHTABLE_BASE_SIZE);
}

TEST(HashTableTest, ShouldSet) {
    struct hashtable *table = hashtable_new();
    std::string key = "key";
    int value = 42;

    hashtable_set(table, (char *)key.c_str(), &value);

    size_t index = hashtable_get_index(table, (char *)key.c_str());
    ASSERT_EQ(value, *(int *)table->items[index]->value);
}

TEST(HashTableTest, ShouldSetAndReturnItem) {
    struct hashtable *table = hashtable_new();
    std::string key = "key";

    int value_1 = 3;
    int value_2 = 4;

    hashtable_set(table, (char *)key.c_str(), &value_1);

    int ret = *(int *)hashtable_set(table, (char *)key.c_str(), &value_2);
    ASSERT_EQ(value_1, ret);

    size_t index = hashtable_get_index(table, (char *)key.c_str());
    ret = *(int *)table->items[index]->value;

    ASSERT_EQ(value_2, ret);
    ASSERT_EQ(1, table->size);
}

TEST(HashTableTest, ShouldGet) {
    struct hashtable *table = hashtable_new();
    std::string key = "key";
    int value = 3;

    hashtable_set(table, (char *)key.c_str(), &value);

    int ret = *(int *)hashtable_get(table, (char *)key.c_str());

    ASSERT_EQ(value, ret);
}

TEST(HashTableTest, ShouldContain) {
    struct hashtable *table = hashtable_new();
    std::string key = "key";
    int value = 3;

    hashtable_set(table, (char *)key.c_str(), &value);

    bool ret = hashtable_contains(table, (char *)key.c_str());
    ASSERT_EQ(true, ret);

    ret = hashtable_contains(table, (char *)"some");
    ASSERT_EQ(false, ret);
}

TEST(HashTableTest, ShouldRemove) {
    struct hashtable *table = hashtable_new();

    std::string key = "key";
    int value = 3;

    hashtable_set(table, (char *)key.c_str(), &value);

    int ret = *(int *)hashtable_remove(table, (char *)key.c_str());
    ASSERT_EQ(value, ret);

    size_t index = hashtable_get_index(table, (char *)key.c_str());
    ASSERT_EQ(NULL, table->items[index]);
}

TEST(HashTableTest, ShouldResize) {
    struct hashtable *table = hashtable_new();
    int value = 1;

    for (size_t i = 0; i < HASHTABLE_BASE_SIZE * 4; i++) {
        hashtable_set(table, (char *)std::to_string(i).c_str(), &value);

        ASSERT_GT(0.7, hashtable_load_factor(table));
    }

    ASSERT_EQ(table->size, HASHTABLE_BASE_SIZE * 4);
    ASSERT_GT(table->capacity, HASHTABLE_BASE_SIZE * 4);
}
