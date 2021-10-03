#include <stdio.h>
#include <stdlib.h>

int is_prime (int candidate) {
    int n;
    int i = 1;
    for (n = 2; n <=candidate; n++) {
        if (candidate % n == 0) {
            i++;
            if (i > 2) {
                return 0;
            }
        }
    }
    return 1;
}




int main (void) {
    int candidate = 2;
    int num_printed = 0;
    int j = 1;

    while (num_printed < 200) {
        if (is_prime(candidate)) {
            printf("%5d", candidate);
            num_printed++;
            j++;
            if (j > 10) {
                printf("\n");
                j = 1;
            }
        }
        candidate++;
    }

    return EXIT_SUCCESS;
}
