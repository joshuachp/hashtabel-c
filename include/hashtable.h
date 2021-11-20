#ifndef HASHTABLE_C
#define HASHTABLE_C

#include <stdbool.h>
#include <stdlib.h>

#define HASHTABLE_BASE_SIZE 256

struct hashtable {
    size_t size;
    size_t capacity;
    struct hashtable_item **items;
};

struct hashtable_item {
    char *key;
    void *value;
};

struct hashtable *hashtable_new();

size_t hashtable_key_hash(struct hashtable *self, char *key);

double hashtable_load_factor(struct hashtable *self);

size_t hashtable_probing_function(size_t index);

size_t hashtable_get_index(struct hashtable *self, char *key);

void *hashtable_set(struct hashtable *self, char *key, void *value);

void *hashtable_get(struct hashtable *self, char *key);

bool hashtable_contains(struct hashtable *self, char *key);

void *hashtable_remove(struct hashtable *self, char *key);

void hashtable_resize(struct hashtable *self);

void hashtable_free(struct hashtable *self);

void hashtable_free_item(struct hashtable_item *item);

#endif // HASHTABLE_C
