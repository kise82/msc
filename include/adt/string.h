#ifndef STRING_H
#define STRING_H
#include <stdint.h>
#include <stddef.h>

typedef struct {
  char *buffer;
  size_t length;
  size_t capacity;
} String;

String new_string(const char *c_str);
void string_append(String *string, const char *c_str);
void string_truncate(String *string);
void free_string(String *string);

#endif
