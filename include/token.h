#ifndef TOKEN_H
#define TOKEN_H
#include <stdint.h>
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
  LPAREN,
  RPAREN,
  SEMICOLON,

  // End-of-stream
  EOS = 0xFF
} TokenKind;

typedef struct {
  uint16_t offset;
  uint16_t length;
} Span;

typedef struct {
  TokenKind kind;
  union {
    size_t __filler__;
    Span lexeme;
  } data;
} Token;

#endif
