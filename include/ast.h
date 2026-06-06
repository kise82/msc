#ifndef AST_H
#define AST_H
#include <token.h>
#include <adt/string.h>

#include <stdint.h>

typedef enum {
  BINARY,
  UNARY,
  VALUE
} NodeType;

typedef struct Node Node;
struct Node {
  NodeType type;
  Token token;
  union {
    struct {
      Node *lhs;
      Node *rhs;
    } binary;
    struct {
      Node *operand;
    } unary;
  } data;
};

Node *new_binary(Token op, Node *lhs, Node *rhs);
Node *new_unary(Token op, Node *operand);
Node *new_literal(Token literal);

void print_ast(const Node *root, String *buffer);
void free_ast(Node *root);

#endif
