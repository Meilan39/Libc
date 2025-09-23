#ifndef LIBC_GLOBAL
#define LIBC_GLOBAL

#include <stdlib.h>
#include <stdio.h>

#define MEM_INIT_CAPACITY 10
#define MEM_GROWTH_MULTIPLIER 2

#define LIBCMAX(a, b) (a > b ? a : b)
#define LIBCMIN(a, b) (a < b ? a : b)

static void error(const char* message) {
    fprintf(stderr, "Libc error : %s\n", message);
    abort();
}


#endif