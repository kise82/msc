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
  #define ADVANCE() ((void) ++lexer->pos)
  #define CONSUME() (lexer->input[lexer->pos++])
  #define PEEK() (lexer->input[lexer->pos])

  Token ret = { .kind = UNKNOWN };
  
  char current;
  do {
    current = CONSUME();
  } while (isspace(current));

  if (current == '\0') {
    ret.kind = EOS;
    return ret;
  }

  #define SC_TOK(chr, tok) case (chr): { ret.kind = (tok); break; }
  switch (current) {
    SC_TOK('+', PLUS)
    SC_TOK('-', MINUS)
    SC_TOK('*', STAR)
    SC_TOK('=', EQUALS)
    SC_TOK('/', SLASH)

    SC_TOK('(', LPAREN)
    SC_TOK(')', RPAREN)
    SC_TOK(';', SEMICOLON)

    default: {
      if (isdigit(current)) {
        ret.kind = INTEGER;
        ret.data.lexeme.offset = lexer->pos - 1;
        ret.data.lexeme.length = 1;
        while (isdigit(PEEK())) {
          ++ret.data.lexeme.length;
          ADVANCE();
        }
      }
      break;
    }
  }
  
  return ret;
}
