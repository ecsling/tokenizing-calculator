/*
SHUNTING YARD (infix -> RPN tokens)

Rules:
- Numbers go to output queue
- Operators: stack by precedence & associativity
- ( push to op stack, ) pop until (
- ( ) mismatch => parse error

Precedence:
    3: unary, ` ~   (right associative)
    2: * / %        (left associative)
    1: + -          (left associative)   

*/

#include "my_bc.h"

static int is_op_token(const t_token *tok) {
    return tok->type == TOK_OP;
}

// to_rpn converts infix tokens to rpn using the shunting yard algorithm
int to_rpn(const t_vec *tokens, t_vec *out_rpn) {
    t_vec stack;
    vec_init(&stack, sizeof(t_token));

    for (size_t i = 0; i < tokens->size; i++) {
        t_token tok = *(t_token*)((char*)tokens->data + i * tokens->elem);
        
        // if number
        if (tok.type == TOK_INT) {
            // push to output queue
            if (vec_push(out_rpn, &tok) != 0) {
                err_set_parse();
                vec_free(&stack);
                return -1;
            }
        } else if (tok.type == TOK_OP) {
            // if operator. pop while top has higher prec, or same prec and current is left-assoc
            t_token *top = vec_back(&stack);

            while (top && is_op_token(top) &&
                   ((tok.assoc == ASSOC_LEFT && top->prec >= tok.prec) ||
                    (tok.assoc == ASSOC_RIGHT && top->prec > tok.prec))) {
                if (vec_push(out_rpn, top) != 0) {
                    err_set_parse();
                    vec_free(&stack);
                    return -1;
                }
                vec_pop(&stack);
                top = vec_back(&stack);
            }
            if (vec_push(&stack, &tok) != 0) {
                err_set_parse();
                vec_free(&stack);
                return -1;
            }

        } else if (tok.type == TOK_LPAREN) {
            // if left paren
            if (vec_push(&stack, &tok) != 0) {
                err_set_parse();
                vec_free(&stack);
                return -1;
            }
        } else if (tok.type == TOK_RPAREN) {
            // if right paren
            // pop until matching ( is found 
            t_token *top = vec_back(&stack);
            int matched = 0;
            while (top) {
                if (top->type == TOK_LPAREN) {
                    matched = 1;
                    vec_pop(&stack);
                    break;
                }
                if (vec_push(out_rpn, top) != 0) {
                    err_set_parse();
                    vec_free(&stack);
                    return -1;
                }
                vec_pop(&stack);
                top = vec_back(&stack);
            }
            if (!matched) {
                // match doesn't exist
                err_set_parse();
                vec_free(&stack);
                return -1;
            }
        }
    }

    // pop remaining operators. any paren? => mismatch
    while (stack.size) {
        t_token *top = vec_back(&stack);
        if (top->type == TOK_LPAREN || top->type == TOK_RPAREN) {
            err_set_parse();
            vec_free(&stack);
            return -1;
        }
        if (vec_push(out_rpn, top) != 0) {
            err_set_parse();
            vec_free(&stack);
            return -1;
        }
        vec_pop(&stack);
    }

    vec_free(&stack);
    return 0;
}
