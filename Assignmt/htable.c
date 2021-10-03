#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "mylib.h"
#include "htable.h"

/**
 *Struct htable with its fields.
 */
struct htablerec {
    int capacity;
    int num_keys;
    int *freqs; /*pointer to array of frequencies*/
    char **keys; /*Pointer of a pointer*/
    int  *stats;
    hashing_t method;
};

/**
 * A function which calculates and returns a position
 * of a word to be inserted in the hashtable.
 *
 * @param word an array of characters whose position will be calculated.
 * @return result an integer which is the position of a word.
 */
static unsigned int htable_word_to_int(char *word) {
    unsigned int result = 0;
    while (*word != '\0') {
        result = (*word++ + 31 * result);
    }
    return result;
}


/**
 * Function for double hashing which calculates and
 * returns a 'step'. This step is added to the position of a word
 * each time a collision occurs during insertion or searching.
 *
 * @param h is the hashtable to calculate its step for double hashing.
 * @param i_key is the current position/index of a word which is occupied.
 * @return int to be added to a current index of a word when collision occurs.
 */
static unsigned int htable_step(htable h, unsigned int i_key){
    return 1+ (i_key % (h-> capacity -1));
}



/**
 *Prints out the entire hash table on stderr showing each string
 * in the keys arrays with its corresponding frequency and stat
 * in the freqs and stats array.
 * @param h is hashtable whose contents needs to be displayed.
 */
void htable_print_entire_table(htable h){
    int i;
    fprintf(stderr, "%5s %5s %5s   %s\n", "Pos","Freq","Stats","Word");
    fprintf(stderr,"--------------------------------------\n");
    for(i =0 ; i<h->capacity ; i++){
        if(h->keys[i] != NULL){

            fprintf(stderr, "%5d %5d %5d   %s\n",i,h->freqs[i],
                    h->stats[i],h->keys[i]);
        } else {
            fprintf(stderr, "%5d %5d %5d    %s\n",i,h->freqs[i],h->stats[i],"");
        }
    }
}

/**
 *Initialise htable structure and allocates memory for it.
 * Memory is also allocated for the htable frequency array,keys and stats arrays.
 *
 * @param capacity is size of hashtable
 * @param method to choose to use linear probing by default
 * or double hashing once -d option is selected.
 * @return table which has been created with null and zeroes values.
 */
htable htable_new(int capacity , hashing_t method) {
    /* initialise htbale structure (including items array) */
    int i ;
    htable table= emalloc(sizeof *table);
    table->capacity = capacity;
    table ->num_keys = 0;
    table->keys = emalloc(table->capacity * sizeof table->keys[0]);
    table->freqs = emalloc(table-> capacity * sizeof table->freqs[0]);
    table->stats = emalloc(table-> capacity * sizeof table->stats[0]);
    table->method = method;

    for(i=0 ; i<capacity ; i++){
        table->keys[i] = NULL;
        table->freqs[i] = 0;
	table->stats[i] = 0;
    }
    return table;
}

/**
 * Insert words into into their calculated position in the key array.
 * Insertion by linear probing or double hashing when collision occurs.
 * Memory is allocated in the key cell before inserting the string.
 * Number of collisions is recorded by the stats to measure efficiency.
 *
 * @param h is hashtable to insert words to.
 * @param str is a word or string to be added.
 * @return int 1 for an open space, 0 if there isn't or the frequency.
 */
int htable_insert(htable h, char *str){
    int collision = 0;
    unsigned int wordToInt, index,step;
    wordToInt = htable_word_to_int(str);
    index = wordToInt  % h->capacity;
    step = htable_step(h, wordToInt);

    while(collision < h->capacity){
        if(h->keys[index] == NULL){
            h->keys[index] = emalloc((strlen(str)+1)*sizeof str[0]);
            strcpy(h->keys[index],str);
            h->freqs[index] = 1;
            h->stats[h->num_keys] = collision;
            h->num_keys++;
        
            return 1;

        } else if (strcmp(h->keys[index] ,str) == 0){
            h->freqs[index]++;
            return h->freqs[index];

        }else if(h->method == DOUBLE_H){
            index+=step;
            index = index%h->capacity;
            collision++;
        } else {
            index = (index+1)%h->capacity;
            collision++;
        }
    
    }
    return 0;
}

/**
 * Search a word at its position calculated position.
 * Search is either by linear probing or double hashing.
 *
 * @param h hashtable to seach the word in.
 * @param key is the word to be searched.
 * @return int 0 if the key is not found.
 */
int htable_search(htable h, char *key){
    int collisions = 0 , position,step;
    unsigned int word ;
    word = htable_word_to_int(key);
    position = word % h->capacity;
    step = htable_step(h, word);

    while(h->keys[position] != NULL && strcmp(h->keys[position], key) != 0
          && collisions != h-> capacity){
	if(h->method == DOUBLE_H){
            position += step;
            position = position % h-> capacity;
	} else {
            position = (position+1) % h->capacity;
        }
        collisions++;
    }if(collisions == h->capacity){
        return 0;
    }else {
        return h->freqs[position];
    }

    return 0;
}


/**
 *  Display the words in the keys array with
 * their corresponding frequencies.
 * Does not print out the keys with NULL values.
 *
 * @param h hashtable to print its contents.
 * @param f function to print each word with its frequency.
 */
void htable_print(htable h, void print_info(int freq, char *str)){
    int i;
    for(i=0 ; i< h->capacity ; i++){
        if(h->keys[i] != NULL){
            print_info(h->freqs[i], h->keys[i]);
        }
    }
}

/**
 * Dealloacate all the memory that have been allocated to each string
 * in the keys array then deallocates the keys, frequency and stats arrays.
 * Finally it free the memory allocated for the hashtable.
 *
 * @param h hashtable to free all its allocated memory.
 */
void htable_free(htable h){
    /* free the memory associated with the htable */
    int i;
    for(i = 0; i < h->capacity ; i++){
        free(h->keys[i]);
    }
    free(h->keys);
    free(h->freqs);
    free(h->stats);
    free(h);

}

/**
 * Prints out a line of data from the hash table to reflect the state
 * the table was in when it was a certain percentage full.
 * Note: If the hashtable is less full than percent_full then no data
 * will be printed.
 *
 * @param h - the hash table.
 * @param stream - a stream to print the data to.
 * @param percent_full - the point at which to show the data from.
 */
static void print_stats_line(htable h, FILE *stream, int percent_full) {
    int current_entries = h->capacity * percent_full / 100;
    double average_collisions = 0.0;
    int at_home = 0;
    int max_collisions = 0;
    int i = 0;

    if (current_entries > 0 && current_entries <= h->num_keys) {
        for (i = 0; i < current_entries; i++) {
            if (h->stats[i] == 0) {
                at_home++;
            }
            if (h->stats[i] > max_collisions) {
                max_collisions = h->stats[i];
            }
            average_collisions += h->stats[i];
        }

        fprintf(stream, "%4d %10d %11.1f %10.2f %11d\n", percent_full,
                current_entries, at_home * 100.0 / current_entries,
                average_collisions / current_entries, max_collisions);
    }
}

/**
 * Prints out a table showing what the following attributes were like
 * at regular intervals (as determined by num_stats) while the
 * hashtable was being built.
 *
 * @li Percent At Home - how many keys were placed without a collision
 * occurring.
 * @li Average Collisions - how many collisions have occurred on
 *  average while placing all of the keys so far.
 * @li Maximum Collisions - the most collisions that have occurred
 * while placing a key.
 *
 * @param h the hashtable to print statistics summary from.
 * @param stream the stream to send output to.
 * @param num_stats the maximum number of statistical snapshots to print.
 */
void htable_print_stats(htable h, FILE *stream, int num_stats) {
    int i;

    fprintf(stream, "\n%s\n\n", 
            h->method == LINEAR_P ? "Linear Probing" : "Double Hashing"); 
    fprintf(stream, "Percent   Current    Percent    Average      Maximum\n");
    fprintf(stream, " Full     Entries    At Home   Collisions   Collisions\n");
    fprintf(stream, "------------------------------------------------------\n");
    for (i = 1; i <= num_stats; i++) {
        print_stats_line(h, stream, 100 * i / num_stats);
    }
    fprintf(stream,"------------------------------------------------------\n\n");
}
