#include <stdio.h>
#include <stdlib.h>
#include "bst.h"
#include <string.h>

struct bstnode { /* should live in bst.c */
    char *key;
    bst left;
    bst right;
};


bst findmin( bst b) {
    
    if (b == NULL || b->left == NULL) {
    return b;
    }
    return findmin(b->left);
}
        


bst bst_delete(bst b, char *str) {
    
    bst successor;
    char *temp;

    if (strcmp(b->key, str) == 0) {
        
        if (b->right == NULL && b->left == NULL) {
            /*No children exist*/
            free(b->key);
            free(b);
            b = NULL;
            return b;
        } else if (b->right != NULL && b->left != NULL) {
            /*Both children exist*/
            successor = findmin(b->right);
            temp = successor->key;
            successor->key = b->key;
            b->key = temp;
            b->right = bst_delete(b->right, temp);
            return b;    
        } else if (b->left != NULL) {
            /*Left child exists*/
            bst tmp = b->left;
            free(b->key);
            free(b);
            b = tmp;
            return b;
        } else {
             /*Right child exists*/
            bst tmp = b->right;
            free(b->key);
            free(b);
            b = tmp;
            return b;
        }
        
    } else if (strcmp(str, b->key) < 0) {
        b->left = bst_delete(b->left, str);
        return b;
    } else {
        b->right = bst_delete(b->right, str);
        return b;
    }
               
    return b;

}


bst bst_free(bst b) {
    /* what about left and right subtrees??? */
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

    if (b->key == str) {
        return 1;
    }

    if (b->key > str) {
        bst_search(b->left, str);
    } else {
        bst_search(b->right, str);
    }
    return 0;
}










