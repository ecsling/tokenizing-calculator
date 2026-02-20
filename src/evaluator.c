#include "my_bc.h"

#include <stddef.h>

// Evaluate an RPN vector and return the result as a long long.
// On any error (stack underflow, div by zero, unknown token, OOM)
// we call err_set_parse() and return 0.
long long eval_rpn(const t_vec *rpn) {
	t_vec stack;
	if (vec_init(&stack, sizeof(long long)) != 0) {
		err_set_parse();
		return 0;
	}

	for (size_t i = 0; i < rpn->size; i++) {
		const t_token *tok = (const t_token *)((const char *)rpn->data + i * rpn->elem);

		if (tok->type == TOK_INT) {
			long long v = tok->ival;
			if (vec_push(&stack, &v) != 0) {
				err_set_parse();
				vec_free(&stack);
				return 0;
			}
		} else if (tok->type == TOK_OP) {
			// unary operators: '`' (unary plus), '~' (unary minus)
			if (tok->op == '`' || tok->op == '~') {
				long long *p = vec_back(&stack);
				if (!p) {
					err_set_parse();
					vec_free(&stack);
					return 0;
				}
				long long v = *p;
				vec_pop(&stack);
				long long out = (tok->op == '~') ? -v : v;
				if (vec_push(&stack, &out) != 0) {
					err_set_parse();
					vec_free(&stack);
					return 0;
				}
			} else {
				// binary operators: need two operands
				long long *rp = vec_back(&stack);
				if (!rp) {
					err_set_parse();
					vec_free(&stack);
					return 0;
				}
				long long right = *rp;
				vec_pop(&stack);

				long long *lp = vec_back(&stack);
				if (!lp) {
					err_set_parse();
					vec_free(&stack);
					return 0;
				}
				long long left = *lp;
				vec_pop(&stack);

				long long res = 0;
				switch (tok->op) {
					case '+': res = left + right; break;
					case '-': res = left - right; break;
					case '*': res = left * right; break;
					case '/':
						if (right == 0) { err_set_parse(); vec_free(&stack); return 0; }
						res = left / right;
						break;
					case '%':
						if (right == 0) { err_set_parse(); vec_free(&stack); return 0; }
						res = left % right;
						break;
					default:
						err_set_parse();
						vec_free(&stack);
						return 0;
				}

				if (vec_push(&stack, &res) != 0) {
					err_set_parse();
					vec_free(&stack);
					return 0;
				}
			}
		} else {
			// unexpected token type in RPN
			err_set_parse();
			vec_free(&stack);
			return 0;
		}
	}

	if (stack.size != 1) {
		err_set_parse();
		vec_free(&stack);
		return 0;
	}

	long long *res = vec_back(&stack);
	long long out = *res;
	vec_free(&stack);
	return out;
}

