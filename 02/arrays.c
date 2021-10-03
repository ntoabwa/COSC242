#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int main (void) {

#define ARRAY_SIZE 10
    
    double judge_1[ARRAY_SIZE], judge_2[ARRAY_SIZE], judge_3[ARRAY_SIZE];
    double a, b, c;
    int n;
    int lines = 0;
    int i;
    double total_1 = 0, total_2 = 0, total_3 = 0;
    double sd1 = 0, sd2 = 0, sd3 = 0;
    double mean_1, mean_2, mean_3;

    
    while (4 == scanf("%d%lg%lg%lg", &n, &a, &b, &c)) {
           
                judge_1[lines] = a;
                judge_2[lines] = b;
                judge_3[lines] = c;
            
            lines++;
    }

    for ( i = 0; i < ARRAY_SIZE; i++) {
        total_1 += judge_1[i];
        total_2 += judge_2[i];
        total_3 += judge_3[i];
    }

    mean_1 = total_1 / lines;
    mean_2 = total_2 / lines;
    mean_3 = total_3 / lines;

    for ( i = 0; i < lines; i++) {
        sd1 += pow(judge_1[i] - mean_1, 2.0);
        sd2 += pow(judge_2[i] - mean_2, 2.0);
        sd3 += pow(judge_3[i] - mean_3, 2.0);
    }

    printf("Average SD\n");

    printf("judge 1 : %.1f %.1f\n", mean_1,sqrt(sd1 / (lines-1)));
    printf("judge 2 : %.1f %.1f\n", mean_2,sqrt(sd2 / (lines-1)));
    printf("judge 3 : %.1f %.1f\n", mean_3,sqrt(sd3 / (lines-1)));
    
    
    return EXIT_SUCCESS;
        
        
            
                                           
                                                                              
}
    
                                                       
    
    
