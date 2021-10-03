#include <stdio.h>
#include <stdlib.h>
#include "mylib.h"
#include "bst.h"
#include <assert.h>
#include <ctype.h>

void *emalloc(size_t s) {
    void *result = malloc(s);
    if (NULL == result) {
        fprintf(stderr, "Memory allocation failed!\n");
        exit(EXIT_FAILURE);
    }
    return result;
}






    








