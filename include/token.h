#ifndef TOKEN_H
#define TOKEN_H

typedef enum {
  UNKNOWN,
  PLUS,
  MINUS,
  STAR,
  SLASH,

  // End-of-stream
  EOS = 0xFF
} TokenKind;

typedef struct {
  TokenKind kind;
} Token;

#endif
