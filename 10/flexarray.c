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
        printf("%d\n", f->items[i]);
    }
}


    


static void quick_sort(int *a, int n) {
    int left = 0;
    int temp, pivot, i, j;

    if (n < 2) {
        return;
    }

    pivot = a[left];
    i = left -1;
    j = n;

    while (1) {

        do {
            i++;
        } while (a[i] < pivot);

        do {
            j--;
        } while (a[j] > pivot);

        if (i < j) {
            temp = a[j];
            a[j] = a[i];
            a[i] = temp;
        } else {
            break;
        }
    }
    
    /*printf("indices: %d, %d\n", i, j);*/
    
    /*quick_sort(*/
    
    quick_sort(a, j+1);
    quick_sort(a+j+1, n-(j+1));
    

   
        

    
}



void flexarray_sort(flexarray f) {

    quick_sort(f->items, f->itemcount);
   
}


void flexarray_free(flexarray f) {
      free(f->items); 
}




    
    
    
