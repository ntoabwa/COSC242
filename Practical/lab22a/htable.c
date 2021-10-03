#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "mylib.h"
#include "htable.h"

struct htablerec {
    int capacity;
    int num_keys;
    char **keys;
};


htable htable_new(int num) {
    int i;
    htable table = emalloc(sizeof *table);
    table->capacity = num;
    table->num_keys = 0;
    table->keys = emalloc(table->capacity * sizeof table->keys[0]);

    for (i = 0; i < num; i++) {
        table->keys[i] = NULL;
    }
    
    return table;
}



static unsigned int htable_word_to_int(char *word) {
    unsigned int result = 0;

    while (*word != '\0') {
       result = (*word++ + 31 * result);
    }

    return result;
}



int htable_insert(htable h, char *s) {
    unsigned int result, index;
    int key = 0;

    result =  htable_word_to_int(s);
    index = result%h->capacity;

    if (h->keys[index] == NULL) {
        h->keys[index] = emalloc(sizeof(h->keys[0]) * (strlen(s) + 1));
        strcpy(h->keys[index], s);
        h->num_keys++;
        return 1;
    }

    if (strcmp(h->keys[index], s) == 0) {/*adding a duplicate key should have no key*/
        return 0;
    }

    while (key <= h->capacity) {
        index++;
        index = index%h->capacity;
            
        if (h->keys[index] == NULL) {
            h->keys[index] = emalloc(sizeof(h->keys[0]) * (strlen(s) + 1));
            strcpy(h->keys[index], s);
            h->num_keys++;
            return 1;
        }

        if (strcmp(h->keys[index], s) == 0) { /*adding a duplicate key should have no key*/
            return 0;
        }
        
        key++;
    }

    return 0;
 
   
}
    


void htable_print(htable h, FILE *stream ) {
      int i;
      
      for (i = 0; i < h->capacity; i++) {
          fprintf(stream, "%2d %s\n", i, h->keys[i] == NULL ? "" : h->keys[i]);
      }
}



void htable_free(htable h) {
    int i;

    for (i = 0; i < h->capacity; i++) {
        free(h->keys[i]);
    }
    free(h->keys);
    free(h);
}




    
    
    
