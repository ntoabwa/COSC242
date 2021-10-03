#include <stdio.h>
#include <stdlib.h>

int main (void) {
    int n;
    double a, b, c;
    double best_score = 0;
    double score;
    int best_competitor;
    int competitor;
    
    
    while (4 == scanf("%d%lg%lg%lg", &n, &a, &b, &c)) {
        competitor = n;
        score = a + b + c;
        if ( score > best_score ) {
            best_score = score;
            best_competitor = competitor;
        }
        
    }

    printf("Winner is: %d\n", best_competitor);

    return EXIT_SUCCESS;
}

        

           
        

    

    
