#include <lexer.h>
#include <token.h>

#include <ctype.h>

Lexer new_lexer(const char *input) {
  Lexer ret = {
    .input = input != NULL ? input : "",
    .pos = 0
  };
  return ret;
}

Token lex(Lexer *lexer) {
  #define CURRENT (lexer->input[lexer->pos])
  #define ADVANCE ((void) (++lexer->pos))

  Token ret = { .kind = UNKNOWN };
  
  while (isspace(CURRENT))
    ADVANCE;

  if (CURRENT == '\0') {
    ret.kind = EOS;
    return ret;
  }

  #define SC_TOK(chr, tok) case (chr): { ret.kind = (tok); break; }
  switch (CURRENT) {
    SC_TOK('+', PLUS)
    SC_TOK('-', MINUS)
    SC_TOK('*', STAR)
    SC_TOK('=', EQUALS)
    SC_TOK('/', SLASH)

    SC_TOK('(', LPAREN)
    SC_TOK(')', RPAREN)
    SC_TOK(';', SEMICOLON)
  }

  if (isdigit(CURRENT)) {
    ret.kind = INTEGER;
    ret.data.lexeme.offset = lexer->pos;
    do {
      ++ret.data.lexeme.length;
      ADVANCE;
    } while (isdigit(CURRENT));

    // TODO Employ an uniform advancing of the input
    --lexer->pos;
  }

  ADVANCE;
  
  return ret;
}
