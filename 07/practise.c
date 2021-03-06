#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define STRING_LEN 80
#define ARRAY_LEN 100

void *emalloc(size_t s) {
    void *result = malloc(s);
    if (NULL == result) {
        fprintf(stderr, "Memory allocation failed!\n");
        exit(EXIT_FAILURE);
    }
    return result;
}

void average_word(char *a[], int i, int length, double the_average) {
    if (i < length) {
        if (strlen(a[i]) > the_average) {
            printf("%s\n", a[i]);
        }
        average_word(a, i + 1, length, the_average);
    }
}

int main(void) {
    char word[STRING_LEN];
    char *wordlist[ARRAY_LEN];
    int num_words;
    double average;
    int i;

    num_words = 0;

    while (num_words < ARRAY_LEN && 1 == scanf("%79s", word)) {
        wordlist[num_words] = emalloc((strlen(word) + 1) * sizeof wordlist[0][0]);
        strcpy(wordlist[num_words], word);
        num_words++;
    }

    average = 0.0;

    for (i = 0; i < num_words; i++) {
        average += strlen(wordlist[i]);
    }

    average = average / num_words;

    average_word(wordlist, 0, num_words, average);

    if (num_words != 0) {
        fprintf(stderr, "%.2f\n", average);
    }

    for (i = 0; i < num_words; i++) {
        free(wordlist[i]);
    }

    return EXIT_SUCCESS;
}
        
        
            
