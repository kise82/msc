#ifndef LEXER_H
#define LEXER_H
#include <token.h>
#include <env.h>

#include <stddef.h>
#include <stdbool.h>

typedef struct {
  const char *input;
  size_t pos;
  
  bool peeked;
  Token peekable;

  Env env;

  char lexeme_buf[64 + 1];
} Lexer;

Lexer new_lexer(const char *input);
Token lex(Lexer *lexer);
const Token *peek(Lexer *lexer);

#endif
