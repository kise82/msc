#ifndef LEXER_H
#define LEXER_H
#include <token.h>

#include <stddef.h>

typedef struct {
  const char *input;
  size_t pos;
} Lexer;

Lexer new_lexer(const char *input);
Token lex(Lexer *lexer);

#endif
