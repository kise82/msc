#ifndef VALUE_H
#define VALUE_H
#include <token.h>
#include <adt/string.h>

#include <stdint.h>
#include <stdbool.h>

typedef enum {
  VOID,
  BOOL,
  INTEGER,
  FLOAT
} Type;

typedef struct {
  Type type;
  union {
    int64_t i64;
    double f64;
    bool bool_;
  } value;
} Value;

extern const Value ZERO_I64;
extern const Value ZERO_F64;

Value new_value(Token literal);

Value add_values(Value lhs, Value rhs);
Value sub_values(Value lhs, Value rhs);
Value mul_values(Value lhs, Value rhs);
Value div_values(Value lhs, Value rhs);

Value cmp_values(Token op, Value lhs, Value rhs);

#endif
