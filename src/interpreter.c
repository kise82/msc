#include <interpreter.h>
#include <stdlib.h>

int64_t evaluate(const Node *root) {
  switch (root->type) {
    case VALUE: {
      return root->token.data.i64;
    }
    case UNARY: {
      int64_t value = evaluate(root->data.unary.operand);
      switch (root->token.kind) {
        case MINUS: return -value;
        default: return value;
      }
    }
    case BINARY: {
      int64_t lhs = evaluate(root->data.binary.lhs);
      int64_t rhs = evaluate(root->data.binary.rhs);
      switch (root->token.kind) {
        case PLUS: return lhs + rhs;
        case MINUS: return lhs - rhs;
        case STAR: return lhs * rhs;
        case SLASH: return lhs / rhs;
        default: return 0;
      }
    }
    default: return 0;
  }
}
