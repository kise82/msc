#include <ast.h>

#include <stdlib.h>

#define ALLOC_NODE() (calloc(1, sizeof(Node)))

Node *new_binary(Token op, Node *lhs, Node *rhs) {
  Node *node = ALLOC_NODE();
  node->type = AST_BINARY;
  node->token = op;
  node->data.binary.lhs = lhs;
  node->data.binary.rhs = rhs;
  return node;
}

Node *new_unary(Token op, Node *operand) {
  Node *node = ALLOC_NODE();
  node->type = AST_UNARY;
  node->token = op;
  node->data.unary.operand = operand;
  return node;
}

Node *new_literal(Token literal) {
  Node *node = ALLOC_NODE();
  node->type = AST_VALUE;
  node->token = literal;
  return node;
}

void free_ast(Node *root) {
  if (root != NULL) {
    switch (root->type) {
      case AST_BINARY: {
        free_ast(root->data.binary.lhs);
        free_ast(root->data.binary.rhs);
        break;
      }
      case AST_UNARY: {
        free_ast(root->data.unary.operand);
        break;
      }
      default: break;
    }
    free(root);
  }
}
