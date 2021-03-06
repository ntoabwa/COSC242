#include <stdio.h>
#include <stdlib.h>
#include "mylib.h"
#include "rbt.h"
#include <string.h>

void print_key(char *s) {
    printf("%s\n", s);
}


int main(void) {

    rbt r = rbt_new();
    char word[256];
    char op = '\0';
  

    while (2 == scanf(" %c %255s", &op, word)) {
        if (op == '+') {
            printf("ADDING: %s\n", word);
            r = rbt_insert(r, word);
        } else if (op == '-') {
            printf("DELETING: %s\n", word);
            r = rbt_delete(r, word);
        }

        /* else if (op == 'p'){ */
        /*     printf("PRINTING: %s\n", word); */
        /*     if (strcmp(word, "inorder")) { */
        /*         rbt_inorder(r, print_key); */
        /*     } else { */
        /*         rbt_preorder(r, print_key); */
        /*     } */
        /* } */
    }

    /* while ( 1 == scanf("%255s", word)) { */
    /*     r = rbt_insert(r, word); */
    /* } */

    
    rbt_inorder(r, print_key);
    puts("*****");
    rbt_preorder(r, print_key); 
    rbt_free(r);

    return EXIT_SUCCESS;
}
    

    
    
        
       
