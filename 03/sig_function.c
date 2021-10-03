#include <stdio.h>
#include <stdlib.h>

void max_min(int *a, int n, int *max, int *min) {

    int i;
    int index;

    for (i = 0; i < n; i++) {
        index = i;
        if (a[i] > *max) {
            *max = a[index];

        }
    }

    for (i = 0; i < n; i++) {
        index = i;
        if (a[i] < *min) {
            *min = a[index];
        }
        
    }
        
}


int main (void) {

    int my_array[] = { 5, 2, 7, 3, 4 };
    int biggest = my_array[0]; //or 0
    int smallest = my_array[0]; //or 999999
    max_min(my_array, 5, &biggest, &smallest);
    printf("max value is %d, min value is %d\n", biggest, smallest);

    return EXIT_SUCCESS;
}


