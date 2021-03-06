
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define ARRAY_MAX 30000

/* method to sort the numbers in the array.
 * recieves an array and its length 
 * as inputs.
 */
void selection_sort(int *a, int n) {

    int p;
    int index = 0;
    int temp;
    int i;
    
    /* runs through the array to find the smallest number*/
    /* keeps its position at int index*/
    for (p = 0; p < n; p++) {
        index = p;
        
        /*runs through the array to the end to find the smallest item*/
        /*stores the smallest item in the position index.*/
        for (i = p+1; i < n; i++) {
            if (a[i] < a[index]) {
                index = i;
            }
        }

        /*swaps the smallest item*/
        /*with the current item at the position p*/
        temp = a[index];
        a[index] = a[p];
        a[p] = temp;
    }
    
}


/*main method which sends the array to 
 *selection_sort method to sort it out
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
    selection_sort(my_array, count);
    end = clock();

    for (i = 0; i < count; i++) {
        printf("%d\n", my_array[i]);
    }
    
    fprintf(stderr, "%d %f\n", count, (end - start) / (double)CLOCKS_PER_SEC);
    return EXIT_SUCCESS;
}
