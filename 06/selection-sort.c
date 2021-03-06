#include <stdio.h>
#include <stdlib.h>

#define ARRAY_MAX 100

void selection_sort(int *a, int n) {

    int p;
    int index = 0;
    int temp;
    int i;
    
    for (p = 0; p < n; p++) {
        index = p;
        
        for (i = p+1; i < n; i++) {
            if (a[i] < a[index]) {
                index = i;
            }
        }

        temp = a[index];
        a[index] = a[p];
        a[p] = temp;
    }
    
}

void print_array(int a[], int n) {
    
    if (n > 0) {
        printf("%d\n", a[0]);
        print_array(a + 1, n - 1);
    }
}


int main(void) {
    
    int my_array[ARRAY_MAX];
    int count = 0;

    while (count < ARRAY_MAX && 1 == scanf("%d", &my_array[count])) {
        count++;
    }

    selection_sort(my_array, count);

    print_array(my_array, count);
    
    return EXIT_SUCCESS;
}

