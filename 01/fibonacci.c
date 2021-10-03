#include <stdio.h>
#include <stdlib.h>

int main (void) {
    int f = 0;
    int g = 1;
    int i;
    int temp;
    int j = 1;
    for (i = 0; i < 40; i++) {
        printf("%10d ", g);
        temp = g;
        g += f;
        f = temp;
        j++;
        if (j > 5) {
            printf("\n");
            j = 1;
        }
    }

    return EXIT_SUCCESS;
}
