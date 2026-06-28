#include <utils.h>

#include <stddef.h>
#include <stdlib.h>
#include <string.h>

char *utils_strdup(const char *restrict original) {
  if (original == NULL) {
    return NULL;
  }

  size_t len = strlen(original);
  char *ret = malloc(len + 1);
  if (ret != NULL) {
    strcpy(ret, original);
    ret[len] = '\0';
  }
  return ret;
}
