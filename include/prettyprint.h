#ifndef PRETTYPRINT_H
#define PRETTYPRINT_H
#include <adt/string.h>
#include <token.h>
#include <ast.h>
#include <value.h>

void print_token(const Token token, String *buffer);
void print_ast(const Node *root, String *buffer);
void print_value(const Value value, String *buffer);

#endif
