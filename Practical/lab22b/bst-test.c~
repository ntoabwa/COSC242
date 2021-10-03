#include <stdio.h>
#include <stdlib.h>
#include "mylib.h"
#include "bst.h"
#include <string.h>

void print_key(char *s) {
    printf("%s\n", s);
}


int main(void) {

    bst b = bst_new();
    char word[256];
    char op = '\0';
  

    while (2 == scanf(" %c %255s", &op, word)) {
        if (op == '+') {
            printf("ADDING: %s\n", word);
            b = bst_insert(b, word);
        } else if (op == '-') {
            printf("DELETING: %s\n", word);
            b = bst_delete(b, word);
        } else if (op == 'p'){
            printf("PRINTING: %s\n", word);
            if (strcmp(word, "inorder")) {
                bst_inorder(b, print_key);
            } else {
                bst_preorder(b, print_key);
            }
        }
    }
    bst_inorder(b, print_key);
    bst_free(b);

    return EXIT_SUCCESS;
}
    

    
    
        
       
