#include <lexer.h>
#include <token.h>

#include <ctype.h>

Lexer new_lexer(const char *input) {
  Lexer ret = {
    .input = input != NULL ? input : "",
    .pos = 0,
    .peekable = { .kind = EOS }
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

  #define SC_TOK(chr, tok) case (chr): { ret.kind = (tok); break; }
  switch (current) {
    SC_TOK('\0', EOS)

    SC_TOK('+', PLUS)
    SC_TOK('-', MINUS)
    SC_TOK('*', STAR)
    SC_TOK('/', SLASH)
    SC_TOK('=', EQUALS)

    SC_TOK('(', LPAREN)
    SC_TOK(')', RPAREN)
    SC_TOK(';', SEMICOLON)

    default: {
      if (isdigit(current)) {
        ret.kind = INTEGER;
        // TODO Handle overflowing literals
        int64_t value = current - '0';
        while (isdigit(PEEK())) {
          value = 10 * value + (PEEK() - '0');
          ADVANCE();
        }
        ret.data.i64 = value;
      }
      break;
    }
  }
  
  return ret;
}

const Token* peek(Lexer *lexer) {
  size_t prev = lexer->pos;
  lexer->peekable = lex(lexer);
  lexer->pos = prev;
  return &lexer->peekable;
}
