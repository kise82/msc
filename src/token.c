#include <token.h>

const char *token_to_c_str(Token token) {
  #define CASE(tok, str) case (tok): return (str);
  switch (token.kind) {
    CASE(TOK_PLUS, "+")
    CASE(TOK_MINUS, "-")
    CASE(TOK_STAR, "*")
    CASE(TOK_SLASH, "/")
    CASE(TOK_EQUALS, "=")
    CASE(TOK_LPAREN, "(")
    CASE(TOK_RPAREN, ")")
    CASE(TOK_SEMICOLON, ";")
    default: return "";
  }
}
