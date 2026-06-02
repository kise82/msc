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
  TokenKind kind;
  union {
    struct {
      size_t offset;
      size_t length;
    } lexeme;
    int64_t i64;
  } data;
} Token;

#endif
