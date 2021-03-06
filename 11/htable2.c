#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "mylib.h"
#include "htable.h"

struct htablerec {
    int capacity;
    int num_keys;
    int *frequency;
    char **keys;
};





htable htable_new(int num) {
    int i;
    htable table = emalloc(sizeof *table);
    table->capacity = num;
    table->num_keys = 0;
    table->frequency = emalloc(table->capacity * sizeof table->frequency[0]);
    table->keys = emalloc(table->capacity * sizeof table->keys[0]);

    for (i = 0; i < num; i++) {
        table->frequency[i] = 0;
        table->keys[i] = NULL;
    }
    
    return table;
}



static unsigned int htable_step(htable h, unsigned int i_key) {
    return 1 + (i_key % (h->capacity - 1));
}


static unsigned int htable_word_to_int(char *word) {
    unsigned int result = 0;

    while (*word != '\0') {
       result = (*word++ + 31 * result);
    }

    return result;
}



int htable_insert(htable h, char *s) {
    unsigned int result, index, step;
    int key = 0;

    result =  htable_word_to_int(s);
    index = result%h->capacity;
    step = htable_step(h, result);
    
    while (key < h->capacity) {

    if (h->keys[index] == NULL) {
        h->keys[index] = emalloc(sizeof(h->keys[0]) * (strlen(s) + 1));
        strcpy(h->keys[index], s);
        h->frequency[index] = 1;
        h->num_keys++;
        return 1;
    }

    if (strcmp(h->keys[index], s) == 0) {

        h->frequency[index]++;
        return h->frequency[index];
    }
      

     
   /*index += step;*/
        index = (index +1 )%h->capacity;
        key++;    
      
        
        
        
    }

    return 0;
 
   
}
    


void htable_print(htable h, FILE *stream ) {
      int i;
      for (i = 0; i < h->capacity; i++) {
          if (h->frequency[i] > 0) {
              fprintf(stream, "%d %s\n", h->frequency[i], h->keys[i]);
          }
      }

    
}



int htable_search(htable h, char *str) {
    int i = 0;
    unsigned int result, index, step;
    

    result = htable_word_to_int(str);
    index = result%h->capacity;
    step = htable_step(h, result);
  
    while (i < h->capacity) {       
        if (h->keys[index] == NULL) {
            return 0;
        }

        if (strcmp(h->keys[index], str) == 0) {
            return h->frequency[index];
        }
        
        i++;
        index += step;
        index = index%h->capacity;
    }
    
    return 0;
         
}




void htable_free(htable h) {
      free(h); 
}





    
    
    
