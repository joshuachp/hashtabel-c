#include "hashtable.h"
#include <stdbool.h>
#include <stdio.h>
#include <string.h>

struct hashtable *hashtable_new() {
    struct hashtable *table = malloc(sizeof(struct hashtable));

    table->items = calloc(HASHTABLE_BASE_SIZE, sizeof(struct hashtable_item *));

    table->capacity = HASHTABLE_BASE_SIZE;
    table->size = 0;

    return table;
}

size_t hashtable_key_hash(struct hashtable *self, char *key) {
    size_t length = strlen(key);

    if (length == 0) {
        fprintf(stderr, "ERROR: hashmap received an empty key");
        exit(1);
    }

    size_t hash = 0;

    for (size_t i = 0; i < length; i++) {
        hash = 31 * hash + key[i];
    }

    return hash % self->capacity;
}

double hashtable_load_factor(struct hashtable *self) { return (double)self->size / (double)self->capacity; }

size_t hashtable_probing_function(size_t index) { return (index * index + index) / 2; }

size_t hashtable_get_index(struct hashtable *self, char *key) {
    size_t x = 1;
    size_t key_hash = hashtable_key_hash(self, key);
    size_t index = key_hash;

    while ((self->items[index] != NULL) && (strcmp(self->items[index]->key, key) != 0)) {
        index = (key_hash + hashtable_probing_function(x)) % self->capacity;
        x += 1;
    }

    return index;
}

void *hashtable_set(struct hashtable *self, char *key, void *value) {
    size_t index = hashtable_get_index(self, key);

    struct hashtable_item *item = malloc(sizeof(struct hashtable_item));
    item->key = strdup(key);
    item->value = value;

    void *prev_value = NULL;

    if (self->items[index] != NULL) {
        prev_value = self->items[index]->value;

        self->items[index]->value = NULL;

        hashtable_free_item(self->items[index]);
        self->items[index] = NULL;
    } else {
        self->size += 1;
    }

    self->items[index] = item;

    if (hashtable_load_factor(self) >= 0.7) {
        hashtable_resize(self);
    }

    return prev_value;
}

void *hashtable_get(struct hashtable *self, char *key) {
    size_t index = hashtable_get_index(self, key);

    if (self->items[index] == NULL) {
        return NULL;
    }

    return self->items[index]->value;
}

bool hashtable_contains(struct hashtable *self, char *key) {
    size_t index = hashtable_get_index(self, key);

    return self->items[index] != NULL;
}

void *hashtable_remove(struct hashtable *self, char *key) {
    size_t index = hashtable_get_index(self, key);

    if (self->items[index] == NULL) {
        return NULL;
    }

    void *value = NULL;

    value = self->items[index]->value;

    self->items[index]->value = NULL;

    hashtable_free_item(self->items[index]);
    self->items[index] = NULL;

    return value;
}

void hashtable_resize(struct hashtable *self) {
    size_t prev_capacity = self->capacity;
    struct hashtable_item **prev_items = self->items;

    self->capacity *= 2;

    self->items = calloc(self->capacity, sizeof(struct hashtable_item *));

    for (size_t i = 0; i < prev_capacity; i++) {
        if (prev_items[i] == NULL) {
            continue;
        }

        size_t new_index = hashtable_get_index(self, prev_items[i]->key);

        self->items[new_index] = prev_items[i];
        prev_items[i] = NULL;
    }

    free(prev_items);
    prev_items = NULL;
}

void hashtable_free(struct hashtable *self) {
    for (size_t i = 0; i < self->capacity; i++) {
        if (self->items[i] == NULL) {
            continue;
        }

        hashtable_free_item(self->items[i]);
        self->items[i] = NULL;
    }

    free(self->items);
    self->items = NULL;

    free(self);
    self = NULL;
}

void hashtable_free_item(struct hashtable_item *item) {
    if (item == NULL) {
        return;
    }

    free(item->key);
    item->key = NULL;

    free(item->value);
    item->value = NULL;

    free(item);
    item = NULL;
}
