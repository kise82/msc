#include <ast.h>

#include <stdio.h>
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

void print_ast(const Node *root, String *buffer) {
  if (root == NULL) {
    string_append(buffer, "NULL");
    return;
  }

  if (root->type == AST_VALUE) {
    char scratch[32];
    switch (root->token.kind) {
      case TOK_INTEGER: {
        sprintf(scratch, "%ld", root->token.data.i64);
        break;
      }
      case TOK_FLOAT: {
        sprintf(scratch, "%lf", root->token.data.f64);
        break;
      }
      default: {
        scratch[0] = '\0';
        break;
      }
    }
    string_append(buffer, scratch);
    return;
  }
  
  string_append(buffer, "(");
  string_append(buffer, token_to_c_str(root->token));
  string_append(buffer, " ");
  switch (root->type) {
    case AST_BINARY: {
      print_ast(root->data.binary.lhs, buffer);
      string_append(buffer, " ");
      print_ast(root->data.binary.rhs, buffer);
      break;
    }
    case AST_UNARY: {
      print_ast(root->data.unary.operand, buffer);
      break;
    }
    default: {
      string_append(buffer, "?");
      break;
    }
  }
  string_append(buffer, ")");
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
