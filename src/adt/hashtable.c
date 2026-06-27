#include <adt/hashtable.h>

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

static inline bool table_grow(HashTable *table) {
  HTEntry *entries = calloc(table->capacity * 2, sizeof(HTEntry));
  if (entries != NULL) {
    for (size_t i = 0; i < table->capacity; ++i) {
      HTEntry *entry = &table->entries[i];
      if (entry->key != NULL) {
        size_t index = hash(entry->key) & (table->capacity * 2 - 1);
        while (entries[index].key != NULL) {
          index = (index + 1) & (table->capacity * 2 - 1);
        }
        entries[index].key = entry->key;
        entries[index].value = entry->value;
      }
    }
    free(table->entries);
    table->entries = entries;
    table->capacity *= 2;
    return true;
  }
  return false;
}

HashTable *new_table(void) {
  HashTable *ret = malloc(sizeof(HashTable));
  if (ret != NULL) {
    ret->capacity = INITIAL_CAPACITY;
    if ((ret->entries = calloc(ret->capacity, sizeof(HTEntry))) == NULL) {
      free(ret);
      return NULL;
    }
    ret->length = 0;
  }
  return ret;
}

void **table_insert_or_get(HashTable *table, const char *key) {
  if (table != NULL) {
    if (table->length >= (table->capacity / 2) && table_grow(table) == false) {
      return NULL;
    }
    
    size_t index = hash(key) & (table->capacity - 1);
    HTEntry *entry = &table->entries[index];
    while (entry->key != NULL) {
      if (strcmp(entry->key, key) == 0) {
        return &entry->value;
      }

      index = (index + 1) % (table->capacity - 1);
    }

    {
      size_t len = strlen(key);
      char *buffer = malloc((len + 1) * sizeof(char));
      buffer[len] = '\0';
      strcpy(buffer, key);
    }
    ++table->length;
    return &entry->value;
  }
  return NULL;
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
