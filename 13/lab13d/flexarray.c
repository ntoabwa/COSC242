#include <stdio.h>
#include <stdlib.h>
#include "flexarray.h"

struct flexarrayrec {
    int capacity;
    int itemcount;
    int *items;
};

flexarray flexarray_new() {
    flexarray result = malloc(sizeof *result);
    result->capacity = 2;
    result->itemcount = 0;
    result->items = malloc(result->capacity * sizeof result->items[0]);
    return result;
}

void flexarray_append(flexarray f, int num) {
    if (f->itemcount == f->capacity) {
        f->capacity *= 2;
        f->items = realloc(f->items, f->capacity * sizeof f->items[0]);
    }
    f->items[f->itemcount] = num;
    f->itemcount++;   
}

void flexarray_print(flexarray f) {
    int i;
    for (i = 0; i < f->itemcount; i++) {
        printf("%d\n", f->items[i]);
    }
}

 

static void insertion_sort(int *a, int n) {
    int key, p, i, k;

    for (p = 1; p < n; p++) {

        if (p == n/2) {
            for (k = 0; k < n; k++) {
                fprintf(stderr, "%d\n", a[k]);
            }
        }
        
        key = a[p];
        i = p - 1;

        while (i > -1 && a[i] > key) {
            a[i+1] = a[i];
            i--;
        }

        a[i+1] = key;
    }
                    

}

void flexarray_sort(flexarray f) {
    
    insertion_sort(f->items, f->itemcount);
   
}


void flexarray_free(flexarray f) {
      free(f->items);
      free(f);
}


void *emalloc(size_t s) {
    void *result = malloc(s);
    if (NULL == result) {
        fprintf(stderr, "Memory allocation failed!\n");
        exit(EXIT_FAILURE);
    }
    return result;
}


void *erealloc(void *p, size_t s) {
    void *result = realloc(p, s);
    if (NULL == result) {
        fprintf(stderr, "Memory reallocation failed.\n");
        exit(EXIT_FAILURE);
    }
    return result;
}




    
    
    
