#include <stdio.h>
#include <stdlib.h>

int main (void) {
    double s1, s2, s3, score;
    double best_score = 0;
    int winner = 0;
    int n, competitor;
   

    while (4 == scanf("%d%lg%lg%lg",&n, &s1, &s2, &s3)) {
        competitor = n;

        if (s1 < s2 && s1 < s3) {
            score = (s2 + s3) / 2;
        } else if (s2 < s1 && s2 < s3) {
            score = (s1 + s3) / 2;
        } else {
            score = (s1 + s2) / 2;
        }

        if (score > best_score) {
            best_score = score;
            winner = competitor;
        }
    }

    printf("%d\n", winner);

    return EXIT_SUCCESS;
        
        
}





















int main (void) {
    double s1, s2, s3, score;
    double best_score = 0;
    int winner = 0;
    int n, competitor;


    while (4 == scanf("%d%lg%lg%lg", &n, &s1, &s2, &s3)) {
        competitor = n;

        if (s1 < s2 && s1 < s3) {
            score = (s2 + s3) / 2;
        } else if (s2 < s3 && s2 < s1) {
            score = (s3 + s1) / 2;
        } else {
            score = (s1 + s2) / 2;
        }

        if (score > best_score) {
            best_score = score;
            winner = competitor;
        }

    }

    printf("%d\n", winner);

    return EXIT_SUCCESS;
    
}


        
        
    









