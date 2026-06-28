#ifndef HASHTABLE_H
#define HASHTABLE_H

#include <stddef.h>
typedef struct {
  char *key;
  void *value;
} HTEntry;

typedef struct {
  HTEntry *entries;
  size_t length;
  size_t capacity;
} HashTable;

HashTable new_table(void);
void **table_insert_or_get(HashTable *table, const char *key);
void *table_delete(HashTable *table, const char *key);
void free_table(HashTable *table);

#endif
