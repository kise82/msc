#include <parser.h>
#include <interpreter.h>
#include <ast.h>
#include <adt/string.h>

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
    String s_expr = string_from_c_str(NULL);
    print_ast(ast_root, &s_expr);
    int64_t val = evaluate(ast_root);
    printf("%ld\n", val);
    printf("%s\n", s_expr.buffer);
    free_string(&s_expr);
    free_ast(ast_root);
  }
  return 0;
}
