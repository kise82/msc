#include <env.h>
#include <utils.h>

#include <stdlib.h>
#include <string.h>

Env new_env(void) {
  Env ret = {
    .entries = new_table()
  };
  return ret;
}

void env_register_kws(
                      Env *env,
                      const Keyword kws[],
                      const size_t n) {
  if (env != NULL && kws != NULL) {
    for (size_t i = 0; i < n; ++i) {
      Token *p = malloc(sizeof(Token));
      if (p == NULL) {
        break;
      }
      p->kind = kws[i].kind;
      Token **e = (Token **) table_insert_or_get(&env->entries, kws[i].lexeme);
      if (e == NULL) {
        free(p);
        break;
      }
      *e = p;
    }
  }
}

Token env_fetch(Env *env, const char *lexeme) {
  Token ret = {
    .kind = TOK_UNKNOWN
  };
  if (env != NULL) {
    Token **entry = (Token **) table_insert_or_get(&env->entries, lexeme);
    if (entry != NULL) {
      if (*entry == NULL) {
        ret.kind = TOK_IDENT;
        ret.data.lexeme.ptr = ((HTEntry *) (((uint8_t *) entry) - OFFSET_OF(HTEntry, value)))->key;
        ret.data.lexeme.length = strlen(ret.data.lexeme.ptr);
        *entry = malloc(sizeof(Token));
        if (*entry != NULL) {
          **entry = ret;
        }
      } else {
        ret.kind = (*entry)->kind;
      }
    }
  }
  return ret;
}

void free_env(Env *env) {
  if (env != NULL) {
    free_table(&env->entries);
  }
}
            
