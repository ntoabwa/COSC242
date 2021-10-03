#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define ARRAY_MAX 10000

void selection_sort(char *a[], int n) {

    int p;
    int index = 0;
    char *temp;
    int i;

    for (p = 0; p < n; p++) {
        index = p;

        for (i = p+1; i < n; i++) {
            if (strcmp(a[index], a[i]) > 0) {
                index = i;
            }
        }
        
        temp = a[index];
        a[index] = a[p];
        a[p] = temp;

    }
}

/*
  type * is a block of memory containg types.
  type ** is a block memoty containts points to blocks of type.
  char a = 'a';
  char *b or char b[] = ['a', 'b', 'a', 'c']
  char ** or char *b[] = [['a', 'b'], ['a'], ['a', 'b', 'a', 'c']]

 */

int main (void) {
    char* my_array[ARRAY_MAX];
    int i, count = 0;
    char temp[80];

    while (count < ARRAY_MAX && 1 == scanf("%79s", temp)) {
        my_array[count] = malloc(sizeof(char) * (strlen(temp)+1));
        strcpy(my_array[count], temp);
        count++;
    }

    selection_sort(my_array, count);

    for (i = 0; i < count; i++) {
        printf("%s\n", my_array[i]);
    }

    return EXIT_SUCCESS;
}
