
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define ARRAY_MAX 30000

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

int binsearch(int *a, int n, int t) {
    int i;

    if (n <= 0) {
        return 0;
    }

    if ( t == a[n]) {
        return 1;
    }

    i = n/2;
    
    if (t == a[i]) {
        return 1;
    } else if (t > a[i]) {
        return binsearch(a+i+1, n-(i+1), t);
    } else {
        return binsearch(a, i, t);
    }
}



int main(int argc, char **argv) {
    FILE *infile;
    int my_array[ARRAY_MAX];
    int i, count = 0;
    int num;

    if (NULL == (infile = fopen(argv[1], "r"))) {
        fprintf(stderr, "%s: can't find file %s\n", argv[0], argv[1]);
        return EXIT_FAILURE;
    }

    while (count < ARRAY_MAX && 1 == fscanf(infile, "%d", &my_array[count])) {
        count++;
    }

    fclose(infile);
   
    selection_sort(my_array, count);

   
    printf("Enter an integer: ");
    i = scanf("%d", &num)!= null;
    printf("%d\n", binsearch(my_array, count, num));

    return EXIT_SUCCESS;
 
  
}
