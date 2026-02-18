# my qna's

Q1: What is the purpose of include/, src/, and Makefile in a C project?

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

