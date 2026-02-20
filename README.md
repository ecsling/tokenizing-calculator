# GOALS
* Learn C
* Learn tokenization
* Implement shunting yard algorithm
* Understand how lexing, shunting yard algorithm, and evaluation connect together


# Q&A

### Q1: What is a "token"?

A token is the smallest meaningful unit of the input expression. 
Instead of interpreting raw characters (i.e '+'), we convert the input string into a sequence of typed tokens with enough metadata for later stages to work mechanically (reduces guesswork). 

turns raw text into "units" that LLMs can actually work with. 

### Q2: (ref. dynarray.c) Why does vec_init return int, but vec_free returns nothing (void)?

initialization returns int because we want an error code if it fails. vec_free is not expected to fail, so we don't need it to return anything.

### Q3: What is the "shunting yard algorithm"? 

Converts math expressions written in infix form `3 + 4 * 2` into postfix form (AKA Reverse Polish Notation / RPN) `3 4 2 * +`
It's like a rail yard. Numbers are sent to the output, operators are placed on a stack until it's time to send them out in the right order.
In this project:
* process tokens L -> R using output list/queue and an operator stack
* For each token: 
    1. Number / variable -> put it in the output
    2. Operator -> push to operator stack
    3. Left Parenthesis -> push to operator stack 
    4. Right Parenthesis -> pop operators to output until you pop the matching "("
* after all tokens are read, pop remaining operators to the output

### Q3: Why are t_vec tokens and t_vec rpn separate?

`t_vec tokens` will hold the infix 
- holds size, capacity, element size

`t_vec rpn` will hold the postfix

### Q3: What is the actual purpose of include/, src/, and Makefile in a C project?

include/ -- stores header files (h.) which are the *declarations* that your program needs, like:
* function prototypes (what functions exist)
* struct / enum definitions 
* constants (#define, const)
Putting them in the header files means they can be shared across multple .c files

src/ -- stores source files (.c) which are the actual *implementations* (code) for your project

Makefile -- tells the `make` command how to compile and link your program. Why use it?
* helps avoid retyping compile commands 
* rebuilds only the files that have changed (faster compile time)
* provides useful commands like `make` and `make clean`
* lets you set compiler flags and include paths (i.e `-Iinclude`)

flow: include/my_bc.h declares functions, src/error.c and src/dynarray.c defines those functions, src/main.c includes the header and uses functions

### Q4: What does #ifndef actually do in .h files?

`#ifndef` means "if not defined" and is to prevent the header file from being included more than once. It prevents redefinition errors. 

### Q5: What is a size_t and enum datatype?

size_t -- Unsigned (cannot be negative) integer type. Useful when representing counts and sizes
enum -- Enumeration. Lets you define a set of named integer constants. 
```
    enum ErrorCode {
        ERR_NONE = 0,
        ERR_PARSE = 1,
        ERR_OOM = 2
    };

    if (err == ERR_PARSE) {
        printf("parse error");
    }
```
Helps with readability and helps you group related constants together