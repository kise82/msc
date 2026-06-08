#include <lexer.h>
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
  switch (current) {
    SC_TOK('\0', TOK_EOF)

    SC_TOK('+', TOK_PLUS)
    SC_TOK('-', TOK_MINUS)
    SC_TOK('*', TOK_STAR)
    SC_TOK('/', TOK_SLASH)
    SC_TOK('=', TOK_EQUALS)

    SC_TOK('(', TOK_LPAREN)
    SC_TOK(')', TOK_RPAREN)
    SC_TOK(';', TOK_SEMICOLON)

    default: {
      if (isdigit(current)) {
        ret.kind = TOK_INTEGER;
        // TODO Handle overflowing literals
        int64_t value = current - '0';
        while (isdigit(PEEK(0))) {
          value = 10 * value + (PEEK(0) - '0');
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
