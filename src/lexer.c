#include <lexer.h>
#include <token.h>

#include <ctype.h>

Lexer new_lexer(const char *input) {
  Lexer ret = {
    .input = input != NULL ? input : "",
    .pos = 0,
    .peeked = false,
    .peekable = { .kind = EOS }
  };
  return ret;
}

Token lex(Lexer *lexer) {
  #define ADVANCE() ((void) ++lexer->pos)
  #define CONSUME() (lexer->input[lexer->pos++])
  #define PEEK() (lexer->input[lexer->pos])
  
  if (lexer->peeked == true) {
    lexer->peeked = false;
    return lexer->peekable;
  }

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
