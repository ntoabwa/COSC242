#include <stdio.h>
#include <stdlib.h>



void array_sort(int *a, int n) {
    int key;
    int p;
    int i;

    for (p = 1; p < n; p++) {
        key = a[p];
        i = p-1;

        while (i > -1 && a[i] > key) {
            a[i+1] = a[i];
            i--;
        }

        a[i+1] = key;
    }
}



static void array_print(int *a, int n) {
    int i;
    for (i = 0; i < n; i++) {
        printf("%d\n", a[i]);
    }
}


int main(void) {
    int capacity = 2;
    int itemcount = 0;
    int item;
    int *my_array = malloc(capacity * sizeof my_array[0]);

    if (NULL == my_array) {
        fprintf(stderr, "memory allocation failed.\n");
        exit(EXIT_FAILURE);
    }

    while (1 == scanf("%d", &item)) {
        if (itemcount == capacity) {
            capacity += capacity;
            my_array = realloc(my_array, capacity * sizeof my_array[0]);
            if (NULL == my_array) {
                fprintf(stderr, "memory reallocation failed.\n");
                exit(EXIT_FAILURE);
            }
        }
        my_array[itemcount++] = item;
    }

    array_sort(my_array, itemcount);
    
    array_print(my_array, itemcount);
    
    free(my_array);
    
    return EXIT_SUCCESS;
}
