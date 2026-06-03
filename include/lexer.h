#ifndef LEXER_H
#define LEXER_H
#include <token.h>

#include <stddef.h>
#include <stdbool.h>

typedef struct {
  const char *input;
  size_t pos;
  Token peekable;
} Lexer;

Lexer new_lexer(const char *input);
Token lex(Lexer *lexer);
const Token *peek(Lexer *lexer);

#endif
