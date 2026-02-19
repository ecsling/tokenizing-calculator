# my qna's

## Q1: What is the purpose of include/, src/, and Makefile in a C project?

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

flow: include/my_bc.h declares functions, src/tokenizer.c defines those functions, src/main.c includes the header and uses functions

## Q2: What does #ifndef do in .h files?

`#ifndef` means "if not defined" and is to prevent the header file from being included more than once. It prevents redefinition errors. 

## Q3: What is a size_t and enum datatype?

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

## Q4: (ref. dynarray.c) Why does vec_init return int, but vec_free returns nothing (void)?

initialization can fail. It returns int because we want an error code. vec_free is not expected to fail.
