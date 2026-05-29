#ifndef TOKEN_H
#define TOKEN_H
#include <stddef.h>

typedef enum {
  UNKNOWN,

  // Literals
  INTEGER,
  
  // Operators
  PLUS,
  MINUS,
  STAR,
  SLASH,
  EQUALS,

  // Markers
  SEMICOLON,

  // End-of-stream
  EOS = 0xFF
} TokenKind;

typedef struct {
  size_t offset;
  size_t length;
} Lexeme;

typedef struct {
  TokenKind kind;
  union {
    char nothing_;
    Lexeme lexeme;
  } data;
} Token;

#endif
