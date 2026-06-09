#ifndef INTERPRETER_H
#define INTERPRETER_H
#include <ast.h>
#include <value.h>

Value evaluate(const Node *root);

#endif
