#include <adt/string.h>

#include <stdlib.h>

String string_from_c_str(const char *c_str) {
  const size_t INITIAL_CAPACITY = 16;
  
  String ret = {
    .buffer = NULL,
    .length = 0,
    .capacity = 0
  };

  if (c_str != NULL && (ret.buffer = calloc(1, sizeof(char) * INITIAL_CAPACITY)) != NULL) {
    ret.capacity = INITIAL_CAPACITY;

    string_append(&ret, c_str);
  }

  return ret;
}

void string_append(String *string, const char *c_str) {
  if (string != NULL && c_str != NULL) {
    if (string->capacity == 0) {
      string->capacity = 16;
      string->buffer = realloc(string->buffer, string->capacity);
    }
    
    for (size_t i = 0; c_str[i] != '\0'; ++i) {
      if (string->capacity <= string->length) {
        do {
          string->capacity *= 2;
        } while (string->capacity <= string->length);
        string->buffer = realloc(string->buffer, string->capacity);
      }
      string->buffer[string->length] = c_str[i];
      ++string->length;
    }

    if (string->capacity <= string->length) {
      string->capacity += 1 + (string->length - string->capacity);
      string->buffer = realloc(string->buffer, string->capacity);
    }
    string->buffer[string->length] = '\0';
  }
}

void free_string(String *string) {
  if (string != NULL) {
    if (string->buffer != NULL) {
      free(string->buffer);
      string->buffer = NULL;
    }
    string->length = string->capacity = '\0';
  }
}
