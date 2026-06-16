#include <stdio.h>
#include <string.h>
#include <value.h>

#include <assert.h>

const Value ZERO_I64 = { .type = INTEGER, .value.i64 = 0L };
const Value ZERO_F64 = { .type = FLOAT, .value.f64 = 0.0F };

Value new_value(Token literal) {
  Value ret;
  switch (literal.kind) {
    case TOK_INTEGER: {
      ret.type = INTEGER;
      ret.value.i64 = literal.data.i64;
      break;
    }
    case TOK_FLOAT: {
      ret.type = FLOAT;
      ret.value.f64 = literal.data.f64;
      break;
    }
    default: {
      assert(0 && "Invalid token passed to `new_value`");
      break;
    }
  }
  return ret;
}

#define OP_BODY(op) \
assert(lhs.type == rhs.type); \
Value ret = { .type = lhs.type }; \
switch (ret.type) { \
  case INTEGER: APPLY_OP(i64, op) \
  case FLOAT: APPLY_OP(f64, op) \
  default: { \
    ret = ZERO_I64; \
    assert(0 && "Invalid operand size passed"); \
    break; \
  } \
} \
return ret; \

#define APPLY_OP(field, op) { ret.value.field = lhs.value.field op rhs.value.field; break; }

Value add_values(Value lhs, Value rhs) {
  OP_BODY(+)
}

Value sub_values(Value lhs, Value rhs) {
  OP_BODY(-)
}

Value mul_values(Value lhs, Value rhs) {
  OP_BODY(*)
}

Value div_values(Value lhs, Value rhs) {
  OP_BODY(/)
}
