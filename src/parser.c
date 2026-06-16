#include <parser.h>
#include <lexer.h>

#include <stdio.h>

static inline Node *program(Lexer *lexer);
static inline Node *expression(Lexer *lexer);
static inline Node *relational(Lexer *lexer);
static inline Node *term(Lexer *);
static inline Node *factor(Lexer *);
static inline Node *atom(Lexer *);

// program -> expression
Node *program(Lexer *lexer) {
  return expression(lexer);
}

// expression -> relational
Node *expression(Lexer *lexer) {
  return relational(lexer);
}

// relational -> term (('==' | '!=') term)
Node *relational(Lexer *lexer) {
  Node *ret = term(lexer);
  Token t = *peek(lexer);
  if (t.kind == TOK_EQUALS_EQUALS || t.kind == TOK_BANG_EQUALS) {
    t = lex(lexer);
    ret = new_binary(t, ret, term(lexer));
  }
  return ret;
}

// term -> factor (('+' | '-') factor)*
Node *term(Lexer *lexer) {
  Node *ret = factor(lexer);
  Token t = *peek(lexer);
  while (t.kind == TOK_PLUS || t.kind == TOK_MINUS) {
    t = lex(lexer);
    ret = new_binary(t, ret, factor(lexer));
    t = *peek(lexer);
  }
  return ret;
}

// factor -> atom (('*' | '/') atom)*
Node *factor(Lexer *lexer) {
  Node *ret = atom(lexer);
  Token t = *peek(lexer);
  while (t.kind == TOK_STAR || t.kind == TOK_SLASH) {
    t = lex(lexer);
    ret = new_binary(t, ret, atom(lexer));
    t = *peek(lexer);
  }
  return ret;
}

// atom -> ('+' | '-') atom | INTEGER | FLOAT | '(' expression ')'
Node *atom(Lexer *lexer) {
  Node *ret = NULL;
  Token t;
  switch ((t = lex(lexer)).kind) {
    case TOK_PLUS:
    case TOK_MINUS: {
      ret = new_unary(t, atom(lexer));
      break;
    }
    case TOK_INTEGER:
    case TOK_FLOAT: {
      ret = new_literal(t);
      break;
    }
    case TOK_LPAREN: {
      ret = expression(lexer);
      if (lex(lexer).kind != TOK_RPAREN) {
        ret = NULL;
      }
      break;
    }
    default: {
      ret = NULL;
      break;
    }
  }
  return ret;
}

Node *parse(const char *input) {  
  Lexer lexer = new_lexer(input);
  return expression(&lexer);
}
