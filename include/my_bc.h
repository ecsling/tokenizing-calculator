#ifndef MY_BC_H
#define MY_BC_H

#include <stdlib.h>
// for tokens and vectors public types 

// malloc, free ...

// error handling
void err_set_parse(void);
void err_print_and_clear(void);

// tiny dynamic array
typedef struct s_vec {
    void *data;     // raw bytes
    size_t size;    // element count
    size_t cap;     // allocated capacity in elements
    size_t elem;    // size of elements: sizeof(element)
} t_vec;

int vec_init(t_vec *v, size_t elem_size);
int vec_free(t_vec *v);

// tokens
typedef enum e_toktype {
    TOK_INT,        // int literal
    TOK_OP,         // + - * / % ~ (unary minus) `(unary plus)
    TOK_LPAREN,     // (
    TOK_RPAREN,     // )
} t_toktype;

typedef enum e_assoc {
    ASSOC_LEFT, 
    ASSOC, RIGHT
} t_assoc;

typedef struct s_token {
    t_toktype type;
    long long ival;     // valid when type == TOK_INT
    char op;            // operator char
    int prec;           // precedence
    t_assoc assoc;
} t_token;

#endif /* MY_BC_H */