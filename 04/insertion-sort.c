
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define ARRAY_MAX 30000

/* method to sort the numbers.
 * receives an array and its length
 * as inputs
 */
void insertion_sort(int *a, int n) {
    
    int key;
    int p;
    int i;

    /*for loop to run through the array.*/
    /*and initially store the second item as the key.*/
    for (p = 1; p < n; p++) {
        key = a[p];
        i = p -1;
        /* item is moved one place to the right */
        /* if it is greater than key and is at the left of p*/
        while (i > -1 && a[i] > key) {
            a[i+1] = a[i];
            i--;
        }
        /*key is always placed in the leftmost vacated position*/
        a[i+1] = key;
    }
    
}

/* Send the array of numbers to
 * insertion_sort to sort it out.
 * have timer to record the sorting algorithm rate.
 */
int main(void) {
    clock_t start, end;
    
    int my_array[ARRAY_MAX];
    int i, count = 0;

    while (count < ARRAY_MAX && 1 == scanf("%d", &my_array[count])) {
        count++;
    }
    
    start = clock();
    insertion_sort(my_array, count);
    end = clock();
    
    for (i = 0; i < count; i++) {
        printf("%d\n", my_array[i]);
    }

    fprintf(stderr, "%d %f\n", count, (end - start) / (double)CLOCKS_PER_SEC);
    
    
    return EXIT_SUCCESS;
}
   
