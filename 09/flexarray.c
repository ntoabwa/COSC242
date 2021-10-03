#include <stdio.h>
#include <stdlib.h>
#include "mylib.h"
#include "flexarray.h"

struct flexarrayrec {
    int capacity;
    int itemcount;
    int *items;
};

flexarray flexarray_new() {
    flexarray result = emalloc(sizeof *result);
    result->capacity = 2;
    result->itemcount = 0;
    result->items = emalloc(result->capacity * sizeof result->items[0]);
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
        printf("%d", f->items[i]);
    }
}


void merge(int *array, int *workspace, int len) {
    int k = 0;
    int i = 0;
    int j = len/2;

    while (k < len) {

        while (i < len/2 && j < len) {
            if (array[i] < array[j]) {
                workspace[k] = array[i];
                i++;
                k++;
            } else {
                workspace[k] = array[j];
                j++;
                k++;
            }
        }

        while (i < len/2) {
            workspace[k] = array[i];
            i++;
            k++;
        }

        while (j < len) {
            workspace[k] = array[j];
            j++;
            k++;
        }
    }
}
    


static void merge_sort(int *a, int *w,  int n) {
    int i;

    if (n < 2) {
        return;
    }

    merge_sort(a, w, n/2);
    merge_sort(a+(n/2), w, n-(n/2));
    merge(a, w, n);

    for (i = 0; i < n; i++) {
        a[i] = w[i];
    }
}



void flexarray_sort(flexarray f) {

    int *workspace = emalloc(f->itemcount * sizeof f->items[0]);
    merge_sort(f->items, workspace, f->itemcount);
    free(workspace);
}


void flexarray_free(flexarray f) {
      free(f->items); 
}




    
    
    
