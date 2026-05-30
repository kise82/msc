#include <lexer.h>

#include <stdio.h>
#include <stdbool.h>

#define ARR_SIZE(arr) (sizeof(arr) / sizeof((arr)[0]))
#define REPORT(res) (printf("TEST\t%s ... %s\n", __FUNCTION__, (res) ? "ok" : "FAILED"), (res))

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

static bool operators() {
  const char *script = "+  -  *   /-+* *";
  const TokenKind kinds[] = {PLUS, MINUS, STAR, SLASH, MINUS, PLUS, STAR, STAR};
  return REPORT(matches(script, kinds, ARR_SIZE(kinds)));
}

static bool literals() {
  const char *script = "123 4  56";
  const TokenKind kinds[] = {INTEGER, INTEGER, INTEGER};
  return REPORT(matches(script, kinds, ARR_SIZE(kinds)));
}

// Runner

int main() {
  bool ops = operators();
  bool lit = literals();
  return (ops && lit) ? 0 : 1;
}
