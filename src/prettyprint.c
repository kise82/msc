#include <prettyprint.h>

#include <stdio.h>
#include <string.h>

void print_token(const Token token, String *buffer) {
  const char *lexeme = NULL;
  #define CASE(tok, str) case (tok): { lexeme = (str); break; }
  switch (token.kind) {
    CASE(TOK_PLUS, "+")
    CASE(TOK_MINUS, "-")
    CASE(TOK_STAR, "*")
    CASE(TOK_SLASH, "/")
    CASE(TOK_EQUALS, "=")
    CASE(TOK_EQUALS_EQUALS, "==")
    CASE(TOK_BANG, "!")
    CASE(TOK_BANG_EQUALS, "!=")
    CASE(TOK_LESS, "<")
    CASE(TOK_LESS_EQUALS, "<=")
    CASE(TOK_GREATER, ">")
    CASE(TOK_GREATER_EQUALS, ">=")
    CASE(TOK_LPAREN, "(")
    CASE(TOK_RPAREN, ")")
    CASE(TOK_SEMICOLON, ";")
    default: break;
  }

  if (lexeme != NULL) {
    string_append(buffer, lexeme);
    return;
  }
}

void print_ast(const Node *root, String *buffer) {
  if (root == NULL) {
    string_append(buffer, "NULL");
    return;
  }

  if (root->type == AST_VALUE) {
    print_value(new_value(root->token), buffer);
    return;
  }
  
  string_append(buffer, "(");
  print_token(root->token, buffer);
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

void print_value(const Value value, String *buffer) {
  char scratch[32] = { '\0' };
  switch (value.type) {
    case BOOL: {
      if (value.value.bool_ == true) {
        strncpy(scratch, "true", 4);
      } else {
        strncpy(scratch, "false", 5);
      }
      break;
    }
    case INTEGER: {
      sprintf(scratch, "%ld", value.value.i64);
      break;
    }
    case FLOAT: {
      sprintf(scratch, "%lf", value.value.f64);
      break;
    }
    default: break;
  }
  string_append(buffer, scratch);
}
