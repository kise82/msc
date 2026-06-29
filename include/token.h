#ifndef TOKEN_H
#define TOKEN_H
#include <stdint.h>
#include <stddef.h>

typedef enum {
  TOK_UNKNOWN,

  // Identifiers
  TOK_IDENT,
  
  // Keywords
  TOK_TRUE,
  TOK_FALSE,
  
  // Literals
  TOK_INTEGER,
  TOK_FLOAT,
  
  // Operators
  TOK_PLUS,
  TOK_MINUS,
  TOK_STAR,
  TOK_SLASH,
  TOK_EQUALS,
  TOK_EQUALS_EQUALS,
  TOK_BANG,
  TOK_BANG_EQUALS,
  TOK_LESS,
  TOK_LESS_EQUALS,
  TOK_GREATER,
  TOK_GREATER_EQUALS,

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
      char *ptr;
      size_t length;
    } lexeme;
    int64_t i64;
    double f64;
  } data;
} Token;

const char *token_to_c_str(Token token);

#endif
