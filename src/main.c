#include <lexer.h>

#include <stdio.h>

int main(int argc, char **argv) {
  if (argc > 1) {
    Lexer lexer = new_lexer(argv[1]);
    Token tok;

    do {
      tok = lex(&lexer);
      printf("%d ", tok.kind);
    } while (tok.kind != EOS);
    putchar('\n');
  }
}
