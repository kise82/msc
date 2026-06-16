#include <interpreter.h>
#include <value.h>

#include <assert.h>

Value evaluate(const Node *root) {
  switch (root->type) {
    case AST_VALUE: {
      return new_value(root->token);
    }
    case AST_UNARY: {
      Value value = evaluate(root->data.unary.operand);
      switch (root->token.kind) {
        case TOK_MINUS: {
          switch (value.type) {
            case INTEGER: return sub_values(ZERO_I64, value);
            case FLOAT: return sub_values(ZERO_F64, value);
            default: {
              assert(0 && "Invalid operand type passed to -");
              break;
            }
          }
        }
        default: return value;
      }
    }
    case AST_BINARY: {
      Value lhs = evaluate(root->data.binary.lhs);
      Value rhs = evaluate(root->data.binary.rhs);
      switch (root->token.kind) {
        case TOK_PLUS: return add_values(lhs, rhs);
        case TOK_MINUS: return sub_values(lhs, rhs);
        case TOK_STAR: return mul_values(lhs, rhs);
        case TOK_SLASH: return div_values(lhs, rhs);

        case TOK_EQUALS_EQUALS:
        case TOK_BANG_EQUALS: {
          Value ret = cmp_values(root->token, lhs, rhs);
          if (root->token.kind == TOK_BANG_EQUALS) {
            ret.value.bool_ = !ret.value.bool_;
          }
          return ret;
        }
        default: {
          assert(0 && "Invalid operator passed as binary node");
          break;
        }
      }
    }
    default: {
      assert(0 && "Unknown node type passed to `evaluate`");
      break;
    }
  }
}
