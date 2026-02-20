#include "my_bc.h"
#include <unistd.h>

// simple global error state

static int g_err = 0;

void err_set_parse(void) { if (!g_err) g_err = 1; }

// err_message consumes no arguments and returns a pointer to a constant char
const char *err_message(void) {
    if (g_err == 1) return "parse error";

    return "";
}

int err_print_and_clear(void) {
    const char *m = err_message();
    if (m && *m) {
        // compute the length
        size_t len = 0;
        while (m[len]) len++;
        (void)write(2, m, (unsigned int)len);
        (void)write(2, "\n", 1);
        g_err = 0;
        return 1;
    }
    return 0;
}