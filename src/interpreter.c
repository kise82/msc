#include <interpreter.h>

int64_t evaluate(const Node *root) {
  switch (root->type) {
    case AST_VALUE: {
      return root->token.data.i64;
    }
    case AST_UNARY: {
      int64_t value = evaluate(root->data.unary.operand);
      switch (root->token.kind) {
        case TOK_MINUS: return -value;
        default: return value;
      }
    }
    case AST_BINARY: {
      int64_t lhs = evaluate(root->data.binary.lhs);
      int64_t rhs = evaluate(root->data.binary.rhs);
      switch (root->token.kind) {
        case TOK_PLUS: return lhs + rhs;
        case TOK_MINUS: return lhs - rhs;
        case TOK_STAR: return lhs * rhs;
        case TOK_SLASH: return lhs / rhs;
        default: return 0;
      }
    }
    default: return 0;
  }
}
