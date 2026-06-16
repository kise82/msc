#include <parser.h>
#include <interpreter.h>
#include <ast.h>
#include <adt/string.h>
#include <prettyprint.h>

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

    String output = new_string(NULL);
    Node *ast_root = parse(BUFFER);
    
    Value val = evaluate(ast_root);
    print_value(val, &output);
    printf("%s\n", output.buffer);

    string_truncate(&output);
    print_ast(ast_root, &output);
    printf("%s\n", output.buffer);
    
    free_ast(ast_root);
    free_string(&output);
  }
  return 0;
}
