#include <adt/hashtable.h>
#include <utils.h>

#include <stdbool.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

#define INITIAL_CAPACITY 16

static inline uint64_t hash(const char *key) {
  const uint64_t FNV_OFFSET = 14695981039346656037UL;
  const uint64_t FNV_PRIME = 1099511628211UL;

  uint64_t ret = FNV_OFFSET;
  if (key != NULL) {
    for (size_t i = 0; key[i] != '\0'; ++i) {
      ret ^= key[i];
      ret *= FNV_PRIME;
    }
  }
  return ret;
}

static HTEntry *table_find(HTEntry *entries, size_t capacity, const char *key) {
  if (entries != NULL && key != NULL) {
    size_t index = hash(key) & (capacity - 1);
    HTEntry *entry;
    while ((entry = &entries[index])->key != NULL) {
      if (strcmp(key, entry->key) == 0) {
        break;
      }
      index = (index + 1) & (capacity - 1);
    }
    return entry;
  }
  return NULL;
}

static bool table_grow(HashTable *table) {
  HTEntry *new_entries = calloc(table->capacity * 2, sizeof(HTEntry));
  if (new_entries != NULL) {
    for (size_t i = 0; i < table->capacity; ++i) {
      HTEntry *old_entry = &table->entries[i];
      if (old_entry->key != NULL) {
        HTEntry *new_entry = table_find(new_entries, table->capacity * 2, old_entry->key);
        new_entry->key = old_entry->key;
        new_entry->value = old_entry->value;
      }
    }
    free(table->entries);
    table->entries = new_entries;
    table->capacity *= 2;
    return true;
  }
  return false;
}

HashTable new_table(void) {
  HashTable ret = {
    .length = 0,
    .capacity = INITIAL_CAPACITY
  };
  if ((ret.entries = calloc(ret.capacity, sizeof(HTEntry))) == NULL) {
    ret.capacity = 0;
  }
  return ret;
}

void **table_insert_or_get(HashTable *table, const char *key) {
  if (table != NULL && table->entries != NULL) {
    if (table->length >= (table->capacity / 2) && table_grow(table) == false) {
      return NULL;
    }
    
    HTEntry *entry = table_find(table->entries, table->capacity, key);

    if (entry->key == NULL) {
      entry->key = utils_strdup(key);

      ++table->length;
    }
    return &entry->value;
  }
  return NULL;
}

void *table_delete(HashTable *table, const char *key) {
  void *ret = NULL;
  if (table != NULL && key != NULL) {
    HTEntry *entry = table_find(table->entries, table->capacity, key);
    if (entry->key != NULL) {
      free(entry->key);
      ret = entry->value;
      entry->key = entry->value = NULL;
      --table->length;
    }
  }
  return ret;
}

void free_table(HashTable *table) {
  if (table != NULL) {
    if (table->entries != NULL) {
      for (size_t i = 0; i < table->capacity; ++i) {
        free(table->entries[i].key);
        free(table->entries[i].value);
      }
    }
    free(table);
  }
}
