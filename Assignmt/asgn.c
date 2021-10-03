#include <stdio.h>
#include <stdlib.h>
#include "getopt.h"
#include <time.h>
#include <string.h>
#include "mylib.h"
#include "htable.h"
#include <math.h>


/**
 * Function to print out each word with its
 * corresponding frequency.
 *
 * @param freq in the frequency array.
 * @param word in the keys array.
 */

static void print_info(int freq, char *word) {
    printf("%-4d %s\n", freq, word);
}

/**
 * Checks if the size is a prime number by calculating
 * prime numbers up to the size.
 * @param x size of hash table.
 * @return 0 if its not a prime_number.
 * @return 1 if its a prime_number.
 */
static int isPrime(int x) {
    int f = 2;
    while (f <= sqrt(x)){
        if (x % f == 0) {
            return 0;
        } else {
            f = f + 1;
        }
    }
    return 1;
}


/**
 * Check if the size of hash table is a prime_number.
 * @param s size of hash table.
 * @return size as first prime number that is greater or equal to given size.
 */
int prime_size(int s){
    int size = s;
    while (size > 0) {
        if (isPrime(size)){
            break;
        } else {
            size = size + 1;
        }
    }
    return size;
}

/**
 * Main function that uses the getopt function to handle input options
 * from the user  and performs a number of tasks.
 * Creates a hash table, read in the contents of a file in stdin and takes 
 * arguments as options from the user.
 * @options -c takes in a file argument, compares its words with the one from
 * stdin , prints out the unknown words in stdout and prints out timing and
 * number of words in stderr.
 * -d specifies the hashing method to double hashing.
 * -e prints entire table in stderr.
 * -p printout stats information to record efficiency of a hashing method.
 * -s specify number of snapshots (if -p option is used).
 * -t specify size of hashtable.
 * -h prints out instructions on how to use this program to user.
 * @param argc number of arguments.
 * @param argv array of arguments given by the user using command lines.
 * @return EXIT_SUCCESS.
 */
int main(int argc, char **argv){
    htable h;
    FILE *file = NULL;
    char option;
    char word[256];
    const char *optstring = "c:deps:t:h";
    int capacity = 113;
    hashing_t method = LINEAR_P;
    double search, insertion;
    clock_t end, start;
    int unknownWords , snapshots, checkFile, displayTable , printStats ,snapShots;
    unknownWords = 0;
    snapshots = 0;
    checkFile = 0;
    displayTable = 0;
    printStats = 0;
    snapShots = 0;

    /**
     *While loop that manages the arguments entered by the user.
     *
     */   
	
    while ((option = getopt(argc, argv, optstring)) != EOF) {
	switch (option) {
            case 'c':
                checkFile = 1;
                file = fopen(optarg, "r");
                if(file == NULL){
                    fprintf(stderr, "Can't open file '%s' using more r.\n", argv[optind-1]);
                    exit(EXIT_FAILURE);
                }
                break;
            case 'd':
                method = DOUBLE_H;
                break;
            case 'e':
                displayTable = 1;
                break;
            case 'p':
                printStats = 1;
                break;
            case 's':
                snapShots = 1;
                snapshots = atoi(optarg);
                break;
              
            case 't':
                capacity = prime_size(atoi(optarg));
                break;
            case 'h':
                printf("Usage: ./asgn [OPTION]... <STDIN>\n\n");
                printf("Perform various operations using a hash table. By default, words are\n");
                printf("read from stdin and added to the hash table, before being printed out\n");
                printf("alongside their frequencies to stdout.\n\n");
                printf(" -c FILENAME  Check spelling of words in FILENAME using words\n");
                printf(" \t      from stdin as dictionary. Print unknown words to\n");
                printf(" \t	 stdout, timing infor & count to stderr (ignore -p)\n");
                printf(" -d           Use double hashing (linear probing is the default\n");
                printf(" -e           Display entire contents of hash table on stderr\n");
                printf(" -p           Print stats info instead of frequencies & words\n");
                printf(" -s SNAPSHOTS Show SNAPSHOTS stats snapshots (if -p is used)\n");
                printf(" -t TABLESIZE Use the first prime >= TABLESIZE as htable size\n\n");
                printf(" -h           Display this message\n");
        
                return EXIT_SUCCESS;
                break;
            default :
                exit(EXIT_FAILURE);
        }
    }
    h = htable_new(capacity, method);
    start = clock();
    while (getword(word,sizeof word, stdin) != EOF){
        htable_insert(h, word);
    } 
    end = clock();
    insertion = ((double) (end - start)) / CLOCKS_PER_SEC;

    if(displayTable == 1){
        htable_print_entire_table(h);
    } 

     
    if(checkFile == 1 || (checkFile == 1 && printStats == 1)){
        start = clock();
        while (getword(word,sizeof word, file) != EOF){
            if(htable_search(h, word) == 0){
                printf("%s\n", word);
                unknownWords++;
            }
        }
        end = clock();
	search = ((double) (end - start)) / CLOCKS_PER_SEC;
        
        printf("Fill Time\t: %2.6f\n", insertion);
        printf("Search Time\t: %2.6f\n", search);
        fprintf(stderr, "Unknown Words\t: %d\n", unknownWords);
    }

    
    
    if(printStats == 1 && checkFile == 0 && snapShots == 0){
	htable_print_stats(h, stdout , 10);
    }

    if(printStats == 1 && snapShots ==1 && checkFile == 0){
	htable_print_stats(h,stdout,snapshots);
        
    } else if( printStats == 0 && checkFile == 0) {
     	htable_print(h, print_info);
    }

    htable_free(h);

    return EXIT_SUCCESS;
}
