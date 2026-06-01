#include "test.h"
#include <lexer.h>

#include <stdio.h>
#include <stdbool.h>

static bool matches(const char *input, const TokenKind expected[], const size_t n) {
  Lexer lexer = new_lexer(input);
  Token tok;
  for (size_t i = 0; i < n; ++i) {
    if ((tok = lex(&lexer)).kind != expected[i]) {
      return false;
    }
  }
  return lex(&lexer).kind == EOS;
}

// Tests

static bool empty() {
  const char *SCRIPT = "\t  \v\n \t";
  const TokenKind KINDS[] = {};
  bool ws = matches(SCRIPT, KINDS, ARR_SIZE(KINDS));
  bool null = matches(NULL, KINDS, ARR_SIZE(KINDS));
  return ws && null;
}

static bool operators() {
  const char *SCRIPT = "    +  /   +  /=  -  *-= *  ";
  const TokenKind KINDS[] = {
    PLUS, SLASH, PLUS, SLASH, EQUALS, MINUS, STAR, MINUS, EQUALS, STAR
  };
  return matches(SCRIPT, KINDS, ARR_SIZE(KINDS));
}

static bool literals() {
  const char *SCRIPT = "123 4  56";
  const TokenKind KINDS[] = {INTEGER, INTEGER, INTEGER};
  return matches(SCRIPT, KINDS, ARR_SIZE(KINDS));
}

static bool mixed() {
  const char *SCRIPT = "(8 + 42 )* 2";
  const TokenKind KINDS[] = {
    LPAREN, INTEGER, PLUS, INTEGER, RPAREN, STAR, INTEGER 
  };
  return matches(SCRIPT, KINDS, ARR_SIZE(KINDS));
}

// Runner

SETUP_RUNNER();

int main() {
  TEST(empty);
  TEST(operators);
  TEST(literals);
  TEST(mixed);
  return TESTS_RESULT;
}
