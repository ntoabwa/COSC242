#include <stdio.h>
#include <string.h>
#include "htable.h"
#include "mylib.h"

struct htablerec {
    int capacity;
    int num_keys;
    char **keys;
};

static unsigned int htable_word_to_int(char *word) {
    unsigned int result = 0;

    while (*word != '\0') {
        result = (*word++ + 31 * result);
    }
    return result;
}

static unsigned int htable_hash(htable h, unsigned int i_key) {
    return i_key % h->capacity;
}

int htable_insert(htable h, char *key) {
    unsigned int result, index;
    int collision = 0;
    
    result = htable_word_to_int(key);
    index = htable_hash(h, result);

    if (h->keys[index] == NULL) {
        h->keys[index] = emalloc(sizeof(h->keys[0]) * (strlen(key) + 1));
        strcpy(h->keys[index], key);
        h->num_keys++;
        return 1;
    }

    if (strcpmp(h->keys[index], key) == 0) {
        return 0;
    }

    while (collision <= h->capacity) {
        index++;
        index = index%h->capacity;

        if (h->keys[index] == NULL) {
            h->keys[index] = emalloc(sizeof(h->keys[0]) * (strlen(key) + 1));
            strcpy(h->keys[index], key);
            h->num_keys++;
            return 1;
        }

        if (strcpmp(h->keys[index], key) == 0) {
            return 0;
        }

        collision++;
    }
    return 0;
    
}

htable htable_new(int capacity) {

    int i;
    htable result = emalloc(sizeof *result);
    result->capacity = capacity;
    result->num_keys = 0;
    result->keys = emalloc(result->capacity * sizeof result->keys[0]);
    
    for (i = 0; i < capacity; i++) {
        result->keys[i] = NULL;
    }

    return result;

}

void htable_free(htable h) {
    int i;
    for (i = 0; i < h->capacity; i++) {
        free(h->keys[i]);
    }

    free(h->keys);
    free(h);


}



void htable_print(htable h, FILE *stream) {
    int i;

    for (i = 0; i < h->capacity; i++) {
        fprintf(stream, "%d %s\n", i, h->keys[i] == NULL ? "" : h->keys[i]);
    }

}
