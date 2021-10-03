#include <stdio.h>
#include <stdlib.h>


void repeated_nums(int *a, int n) {
    int *new_array;
    int i, value;
    
    new_array = malloc(n * sizeof new_array[0]);

    for (i = 0; i < n; i++) {
        new_array[i] = 0;
    }

    for (i = 0; i < n; i++) {
        value = a[i];
        new_array[value]++;
    }

    for (i = 0; i < n; i++) {
        if (new_array[i] > 1) {
            printf("%d occurs %d times\n", i, new_array[i]); 
        }
    }

    free(new_array);
}





/*void repeated_nums(int *a, int n) {
   
    int i;
    int j, count = 0;

    while (j < n) {

        for (i = 0; i < n; i++) {
            if (j == a[i]) {
                count++;
            }
        }

        if (count > 1) {
            printf("%d occurs %d times\n", j, count);
        }

        j++;
        count = 0;
    }
        
}
*/

int main(void) {
    int array_size = 0;
    int *my_array;
    int i = 0;

    printf("Enter the size of the array:\n");
    scanf("%d", &array_size);

    my_array = malloc(array_size * sizeof my_array[0]);
    if (NULL == my_array) {
        fprintf(stderr, "memory allocation failed!\n");
        return EXIT_FAILURE;
    }

    for (i = 0; i < array_size; i++) {
        my_array[i] = rand() % array_size;
    }

    printf("What's in the array:\n");
    for (i = 0; i < array_size; i++) {
        printf("%d ", my_array[i]);
    }

    printf("\n");

    repeated_nums(my_array, array_size);

    free(my_array);

    return EXIT_SUCCESS;
}
