#include "my_bc.h"
#include <stdio.h>

int main(int argc, char **argv) {
    if (argc != 2) {
        err_set_parse();
        err_print_and_clear();
        return 1;
    }
    (void)argv;

    // vector tokens, vector rpn
    t_vec tokens, rpn; 
    vec_init(&tokens, sizeof(t_token));
    vec_init(&rpn, sizeof(t_token));

    // lexer (makes the tokens usable)
    lex(argv[1], &tokens);

    // ---- print all tokens ----
    for (size_t i = 0; i < tokens.size; ++i) {
        t_token *tk = (t_token *)vec_at(&tokens, i);

        if (tk->type == TOK_INT) 
            printf("TOKEN[%zu]: INT -> %lld\n", i, tk->ival);
        else if (tk->type == TOK_OP)
            printf("TOKEN[%zu]: OP -> '%c' (prec=%d, assoc%s)\n",
            i, tk->op, tk->prec,
            tk->assoc == ASSOC_LEFT ? "LEFT" : "RIGHT");
        else if (tk->type == TOK_LPAREN)
            printf("TOKEN[%zu]: LPAREN -> '('\n", i);
        else
            printf("TOKEN[%zu]: UNKNOWN\n", i);
    }

    vec_free(&tokens);

    // shunting yard algorithm -> rpn 

    // evaluate rpn

    // success

    return 0;
}