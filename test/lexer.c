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
return lex(&lexer).kind == TOK_EOF;

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
  for (size_t i = 0; (tok = lex(&lexer)).kind != TOK_EOF && i < n; ) {
    if (tok.kind == TOK_INTEGER) {
      if (tok.data.i64 != expected[i]) {
        return false;
      }
      ++i;
    }
  }
  return tok.kind == TOK_EOF;
}

// Tests

static bool empty(void) {
  const char *SCRIPT = "\t  \v\n \t";
  bool ws = match_kinds(SCRIPT, NULL, 0);
  bool null = match_kinds(NULL, NULL, 0);
  return ws && null;
}

static bool operators(void) {
  const char *SCRIPT = "    +  /   +  /=  -  *-= *  ";
  const TokenKind KINDS[] = {
    TOK_PLUS, TOK_SLASH, TOK_PLUS, TOK_SLASH, TOK_EQUALS, TOK_MINUS, TOK_STAR, TOK_MINUS, TOK_EQUALS, TOK_STAR
  };
  return match_kinds(SCRIPT, KINDS, ARR_SIZE(KINDS));
}

static bool literals(void) {
  const char *SCRIPT = "123 4  56";
  const TokenKind KINDS[] = {TOK_INTEGER, TOK_INTEGER, TOK_INTEGER};
  const int64_t VALUES[] = {123, 4, 56};
  bool kinds = match_kinds(SCRIPT, KINDS, ARR_SIZE(KINDS));
  bool values = match_i64(SCRIPT, VALUES, ARR_SIZE(VALUES));
  return kinds && values;
}

static bool mixed(void) {
  const char *SCRIPT = "(8 + 42 )* 2";
  const TokenKind KINDS[] = {
    TOK_LPAREN, TOK_INTEGER, TOK_PLUS, TOK_INTEGER, TOK_RPAREN, TOK_STAR, TOK_INTEGER 
  };
  const int64_t VALUES[] = {8, 42, 2};
  bool kinds = match_kinds(SCRIPT, KINDS, ARR_SIZE(KINDS));
  bool values = match_i64(SCRIPT, VALUES, ARR_SIZE(VALUES));
  return kinds && values;
}

// Runner

SETUP_RUNNER();

int main(void) {
  TEST(empty);
  TEST(operators);
  TEST(literals);
  TEST(mixed);
  return TESTS_RESULT;
}
