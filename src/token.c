#include <token.h>

const char *token_to_c_str(Token token) {
  #define CASE(tok, str) case (tok): return (str);
  switch (token.kind) {
    CASE(PLUS, "+")
    CASE(MINUS, "-")
    CASE(STAR, "*")
    CASE(SLASH, "/")
    CASE(EQUALS, "=")
    CASE(LPAREN, "(")
    CASE(RPAREN, ")")
    CASE(SEMICOLON, ";")
    default: return "";
  }
}
