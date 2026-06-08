#ifndef TOKEN_H
#define TOKEN_H
#include <stdint.h>
#include <stddef.h>

typedef enum {
  TOK_UNKNOWN,

  // Literals
  TOK_INTEGER,
  
  // Operators
  TOK_PLUS,
  TOK_MINUS,
  TOK_STAR,
  TOK_SLASH,
  TOK_EQUALS,

  // Markers
  TOK_LPAREN,
  TOK_RPAREN,
  TOK_SEMICOLON,

  // End-of-stream
  TOK_EOF = 0xFF
} TokenKind;

typedef struct {
  TokenKind kind;
  union {
    struct {
      size_t offset;
      size_t length;
    } lexeme;
    int64_t i64;
  } data;
} Token;

const char *token_to_c_str(Token token);

#endif
