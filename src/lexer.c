#include <lexer.h>
#include <stdio.h>
#include <token.h>

#include <ctype.h>

Lexer new_lexer(const char *input) {
  Lexer ret = {
    .input = input != NULL ? input : "",
    .pos = 0,
    .peeked = false,
    .peekable = { .kind = TOK_EOF }
  };
  return ret;
}

Token lex(Lexer *lexer) {
  #define NEXT() (lexer->input[lexer->pos++])
  #define ADVANCE() ((void) ++lexer->pos)
  #define PEEK(n) (lexer->input[lexer->pos + (n)])
  
  if (lexer->peeked == true) {
    lexer->peeked = false;
    return lexer->peekable;
  }

  Token ret = { .kind = TOK_UNKNOWN };
  
  char current;
  do {
    current = NEXT();
  } while (isspace(current));

  #define SC_TOK(chr, tok) case (chr): { ret.kind = (tok); break; }
  #define DC_TOK(chr1, tok1, chr2, tok2) \
case (chr1): { \
  ret.kind = (tok1); \
  if (PEEK(0) == (chr2)) { \
    ret.kind = (tok2); \
    ADVANCE(); \
  } \
  break; \
}
  switch (current) {
    SC_TOK('\0', TOK_EOF)

    SC_TOK('+', TOK_PLUS)
    SC_TOK('-', TOK_MINUS)
    SC_TOK('*', TOK_STAR)
    SC_TOK('/', TOK_SLASH)
    DC_TOK('=', TOK_EQUALS, '=', TOK_EQUALS_EQUALS)
    DC_TOK('!', TOK_BANG, '=', TOK_BANG_EQUALS)
    DC_TOK('<', TOK_LESS, '=', TOK_LESS_EQUALS)
    DC_TOK('>', TOK_GREATER, '=', TOK_GREATER_EQUALS)

    SC_TOK('(', TOK_LPAREN)
    SC_TOK(')', TOK_RPAREN)
    SC_TOK(';', TOK_SEMICOLON)

    default: {
      if (isdigit(current)) {
        size_t start = lexer->pos - 1;

        while (isdigit(PEEK(0))) {
          ADVANCE();
        }

        if (PEEK(0) == '.' && isdigit(PEEK(1))) {
          ret.kind = TOK_FLOAT;
          ADVANCE();
          do {
            current = NEXT();
          } while (isdigit(current));

          sscanf(&lexer->input[start], "%lf", &ret.data.f64);
        } else {
          ret.kind = TOK_INTEGER;
          sscanf(&lexer->input[start], "%ld", &ret.data.i64);
        }
      }
      break;
    }
  }
  
  lexer->peeked = false;
  
  return ret;
}

const Token* peek(Lexer *lexer) {
  if (lexer->peeked == false) {
    lexer->peekable = lex(lexer);
    lexer->peeked = true;
  }
  return &lexer->peekable;
}
