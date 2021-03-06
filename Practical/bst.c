#include <stdio.h>
#include <stdlib.h>
#include "bst.h"
#include <string.h>

struct bstnode {
    char *key;
    bst left;
    bst right;
};


bst bst_free(bst b) {
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

bst bst_new() {
    return NULL;
}

bst bst_insert(bst b, char*str) {

    if (b == NULL) {
        b = malloc(sizeof(*b));
        b->left = NULL;
        b->right = NULL;
        b->key = malloc(sizeof(b->key[0]) * (strlen(str) + 1));
        strcpy(b->key, str);
        return b;
    }

    if (strcmp(b->key, str) == 0) {
        return b;
    }

    if (strcmp(str, b->key) < 0) {
        b->left = bst_insert(b-left, str);
    } else {
        b->right = bst_insert(b->rght, str);
    }

    return b;
}

int bst_search(bst b, char *str) {

    if (b == NULL) {
        return 0;
    }

    if (strcmp(b->key, str) == 0) {
        return 1;
    }

    if (strcmp(b->left, str) < 0) {
        return bst_search(b->right, str);
    } else {
        return bst_search(b->left, str);
    }

    return 0;
}
        
        
    


        
