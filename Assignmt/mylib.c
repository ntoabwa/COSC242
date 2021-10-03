#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <ctype.h>
#include "mylib.h"
#include <math.h>

/**
 * Uses emalloc for memory allocation and  error checking
 * @return a void pointer
 * @param  takes a size_t
 */

void *emalloc(size_t s){
    void *result = malloc(s);
    if(NULL == result){
        fprintf(stderr, "memory allocation failed\n");
        exit(EXIT_FAILURE);
    }
    return result;
}


/**
 *Use erealloc to resize allocated memory
 * @param *p, pointer to first byte of memory
 * @param size_t s size
 * @return the memory if memory reallocation fails
 */
void *erealloc(void *p, size_t s){
    void *result = realloc(p,s);
    if(NULL == result){
        fprintf(stderr, "memory allocation failed\n");
        exit(EXIT_FAILURE);
    }
    return result;
}


/*A function that is a adapted from the labs to get words from files.*/

int getword(char *s, int limit, FILE *stream) {
    int c;
    char *w = s;
    assert(limit > 0 && s != NULL && stream != NULL);
    /* skip to the start of the word */
    while (!isalnum(c = getc(stream)) && EOF != c)
        ;
    if (EOF == c) {
        return EOF;
    } else if (--limit > 0) { /* reduce limit by 1 to allow for the \0 */
        *w++ = tolower(c);
    }
    while (--limit > 0) {
        if (isalnum(c = getc(stream))) {
            *w++ = tolower(c);
        } else if ('\'' == c) {
            limit++;
        } else {
            break;
        }
    }
    *w ='\0';
    return w - s;
}

