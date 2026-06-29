#ifndef ENV_H
#define ENV_H
#include <adt/hashtable.h>
#include <token.h>

typedef struct {
  const char *lexeme;
  const TokenKind kind;
} Keyword;

typedef struct {
  HashTable entries;
} Env;

Env new_env(void);
void env_register_kws(
                      Env *env,
                      const Keyword kws[],
                      const size_t n
                    );
Token env_fetch(Env *env, const char *lexeme);
void free_env(Env *env);

#endif
