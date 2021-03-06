#include <stdio.h>
#include <stdlib.h>
#include "bst.h"
#include <string.h>

struct bstnode { /* should live in bst.c */
    char *key;
    bst left;
    bst right;
};

       


bst bst_free(bst b) {
    /* what about left and right subtrees??? */
    if (b == NULL) {
        return b;
    }
    bst_free(b->left);
    bst_free(b->right);

    free(b->key);
    free(b);

    return b;
}


void bst_inorder(bst b, void f(char *str)) {
     
    if (b == NULL) {
        return;
    }
    bst_inorder(b->left, f);
    f(b->key);
    bst_inorder(b->right, f);

}


void bst_preorder(bst b, void f(char *str)) {
    
    if (b == NULL) {
        return;
    }
    
    f(b->key);
    bst_preorder(b->left, f);
    bst_preorder(b->right, f);

}


bst bst_insert(bst b, char *s) {

    if (b == NULL) {
        b = malloc(sizeof(*b));
        b->left = NULL;
        b->right = NULL;
        b->key = malloc(sizeof(b->key[0]) * (strlen(s) + 1));
        strcpy(b->key, s);
        return b;
    }

    
    if (strcmp(b->key, s) == 0) {
        return b;
    }

    if (strcmp(s, b->key) < 0) {
        b->left = bst_insert(b->left, s);
    } else {
        b->right = bst_insert(b->right, s);
    }

    return b;
  
}


bst bst_new() {
    return NULL;
}



int bst_search(bst b, char *str) {

    if (b == NULL) {
        return 0;
    }

    if (strcmp(b->key, str) == 0) {
        return 1;
    }

    if (strcmp(b->key, str) < 0) {
        return bst_search(b->right, str);
    } else {
        return bst_search(b->left, str);
    }
   
    return 0;
}










