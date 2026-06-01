#include "test.h"
#include <lexer.h>

#include <stdio.h>
#include <stdbool.h>
#include <string.h>

static bool matches(const char *input, const TokenKind kinds[], const char *lexemes[], const size_t n) {
  Lexer lexer = new_lexer(input);
  Token tok;
  for (size_t i = 0; i < n; ++i) {
    if (kinds != NULL && (tok = lex(&lexer)).kind != kinds[i]) {
      return false;
    } else if (lexemes != NULL && lexemes[i] != NULL
               && strncmp(&input[tok.data.lexeme.offset], lexemes[i], tok.data.lexeme.length) != 0) {
      return false;
    }
  }
  return lex(&lexer).kind == EOS;
}

// Tests

static bool empty() {
  const char *SCRIPT = "\t  \v\n \t";
  bool ws = matches(SCRIPT, NULL, NULL, 0);
  bool null = matches(NULL, NULL, NULL, 0);
  return ws && null;
}

static bool operators() {
  const char *SCRIPT = "    +  /   +  /=  -  *-= *  ";
  const TokenKind KINDS[] = {
    PLUS, SLASH, PLUS, SLASH, EQUALS, MINUS, STAR, MINUS, EQUALS, STAR
  };
  return matches(SCRIPT, KINDS, NULL, ARR_SIZE(KINDS));
}

static bool literals() {
  const char *SCRIPT = "123 4  56";
  const TokenKind KINDS[] = {INTEGER, INTEGER, INTEGER};
  const char *LEXEMES[] = {"123", "4", "56"};
  return matches(SCRIPT, KINDS, LEXEMES, ARR_SIZE(KINDS));
}

static bool mixed() {
  const char *SCRIPT = "(8 + 42 )* 2";
  const TokenKind KINDS[] = {
    LPAREN, INTEGER, PLUS, INTEGER, RPAREN, STAR, INTEGER 
  };
  const char *LEXEMES[] = {
    NULL, "8", NULL, "42", NULL, NULL, "2"
  };
  return matches(SCRIPT, KINDS, LEXEMES, ARR_SIZE(KINDS));
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
