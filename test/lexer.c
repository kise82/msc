#include "test.h"
#include <lexer.h>

#include <stdio.h>
#include <stdbool.h>
#include <string.h>

#define MATCH_BODY(body) \
Lexer lexer = new_lexer(input); \
Token tok; \
for (size_t i = 0; i < n; ++i) { \
  tok = lex(&lexer); \
  { \
    body \
  } \
} \
return lex(&lexer).kind == EOS;

static bool match_kinds(const char *input, const TokenKind expected[], const size_t n) {
  MATCH_BODY(
    if (tok.kind != expected[i]) {
      return false;
    }
  )
}

static bool match_lexemes(const char *input, const char *expected[], const size_t n) {
  MATCH_BODY(
    if (expected != NULL && expected[i] != NULL
        && strncmp(&input[tok.data.lexeme.offset], expected[i], strlen(expected[i])) != 0) {
      return false;
    }
  )
}

static bool match_i64(const char *input, const int64_t expected[], const size_t n) {
  Lexer lexer = new_lexer(input);
  Token tok;
  for (size_t i = 0; (tok = lex(&lexer)).kind != EOS && i < n; ) {
    if (tok.kind == INTEGER) {
      if (tok.data.i64 != expected[i]) {
        return false;
      }
      ++i;
    }
  }
  return tok.kind == EOS;
}

// Tests

static bool empty() {
  const char *SCRIPT = "\t  \v\n \t";
  bool ws = match_kinds(SCRIPT, NULL, 0);
  bool null = match_kinds(NULL, NULL, 0);
  return ws && null;
}

static bool operators() {
  const char *SCRIPT = "    +  /   +  /=  -  *-= *  ";
  const TokenKind KINDS[] = {
    PLUS, SLASH, PLUS, SLASH, EQUALS, MINUS, STAR, MINUS, EQUALS, STAR
  };
  return match_kinds(SCRIPT, KINDS, ARR_SIZE(KINDS));
}

static bool literals() {
  const char *SCRIPT = "123 4  56";
  const TokenKind KINDS[] = {INTEGER, INTEGER, INTEGER};
  const int64_t VALUES[] = {123, 4, 56};
  bool kinds = match_kinds(SCRIPT, KINDS, ARR_SIZE(KINDS));
  bool values = match_i64(SCRIPT, VALUES, ARR_SIZE(VALUES));
  return kinds && values;
}

static bool mixed() {
  const char *SCRIPT = "(8 + 42 )* 2";
  const TokenKind KINDS[] = {
    LPAREN, INTEGER, PLUS, INTEGER, RPAREN, STAR, INTEGER 
  };
  const int64_t VALUES[] = {8, 42, 2};
  bool kinds = match_kinds(SCRIPT, KINDS, ARR_SIZE(KINDS));
  bool values = match_i64(SCRIPT, VALUES, ARR_SIZE(VALUES));
  return kinds && values;
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
