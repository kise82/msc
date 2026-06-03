#include <parser.h>
#include <interpreter.h>
#include <ast.h>

#include <stdio.h>

static char BUFFER[4096];

int main(int argc, char **argv) {
  for (;;) {
    printf("> ");
    fflush(stdout);
    if (fgets(BUFFER, sizeof(BUFFER) / sizeof(BUFFER[0]), stdin) == NULL) {
      break;
    }
    fflush(stdin);
    Node *ast_root = parse(BUFFER);
    int64_t val = evaluate(ast_root);
    printf("%ld\n", val);
    free_ast(ast_root);
  }
  return 0;
}
