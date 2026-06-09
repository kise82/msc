#include <parser.h>
#include <lexer.h>

#include <stdio.h>

static inline Node *term(Lexer *);
static inline Node *factor(Lexer *);
static inline Node *atom(Lexer *);

// expression -> term
static inline Node *expression(Lexer *lexer) {
  return term(lexer);
}

// term -> factor (('+' | '-') factor)*
static inline Node *term(Lexer *lexer) {
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
static inline Node *factor(Lexer *lexer) {
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
static inline Node *atom(Lexer *lexer) {
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
