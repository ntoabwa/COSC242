#include <stdio.h>
#include <stdlib.h>
#include "rbt.h"
#include <string.h>

#define IS_BLACK(x) ((NULL == (x)) || (BLACK == (x)->color))
#define IS_RED(x) ((NULL != (x)) && (RED == (x)->color))


typedef enum { RED, BLACK } rbt_colour;

struct rbtnode { /* should live in bst.c */
    char *key;
    rbt_colour color;
    rbt left;
    rbt right;
};


rbt findmin( rbt r) {
    
    if (r == NULL || r->left == NULL) {
    return r;
    }
    return findmin(r->left);
}
        


rbt rbt_delete(rbt r, char *str) {
    
    rbt successor;
    char *temp;

    if (strcmp(r->key, str) == 0) {
        
        if (r->right == NULL && r->left == NULL) {
            /*No children exist*/
            free(r->key);
            free(r);
            r = NULL;
            return r;
        } else if (r->right != NULL && r->left != NULL) {
            /*Both children exist*/
            successor = findmin(r->right);
            temp = successor->key;
            successor->key = r->key;
            r->key = temp;
            r->right = rbt_delete(r->right, temp);
            return r;    
        } else if (r->left != NULL) {
            /*Left child exists*/
            rbt tmp = r->left;
            free(r->key);
            free(r);
            r = tmp;
            return r;
        } else {
             /*Right child exists*/
            rbt tmp = r->right;
            free(r->key);
            free(r);
            r = tmp;
            return r;
        }
        
    } else if (strcmp(str, r->key) < 0) {
        r->left = rbt_delete(r->left, str);
        return r;
    } else {
        r->right = rbt_delete(r->right, str);
        return r;
    }
               
    return r;


}


rbt rbt_free(rbt r) {
    /* what about left and right subtrees??? */
    if (r == NULL) {
        return NULL;
    }
    
    rbt_free(r->left);
    rbt_free(r->right);
    
    free(r->key);
    free(r);
    return NULL;
}


void rbt_inorder(rbt r, void f(char *str)) {
     
    if (r == NULL) {
        return;
    }
    rbt_inorder(r->left, f);
    if (IS_RED(r)) {
        printf("Red:");
    }else {
        printf("Black:");
    }
    
    f(r->key);
    rbt_inorder(r->right, f);

}


void rbt_preorder(rbt r, void f(char *str)) {
    
    if (r == NULL) {
        return;
    }
    
    if (IS_RED(r)) {
        printf("Red:");
    }else {
        printf("Black:");
    }
    f(r->key);
    rbt_preorder(r->left, f);
    rbt_preorder(r->right, f);

}


static rbt right_rotate(rbt r) {
    
    rbt temp = r;
    r = r->left;
    temp->left = r->right;
    r->right = temp;

    return r;
    
}


static rbt left_rotate(rbt r) {
    
    rbt temp = r;
    r = r->right;
    temp->right = r->left;
    r->left = temp;

    return r;
    
}


static rbt rbt_fix(rbt r) {


    if (IS_RED(r->left)) {     
        if (IS_RED(r->left->left)) {
            
            if (IS_RED(r->right)) {
                r->color = RED;
                r->left->color = BLACK;
                r->right->color = BLACK;
                return r;
            } else {/*right rotate root, color new root, and new child*/
                r->color = RED;
                r->left->color = BLACK;
                r = right_rotate(r);
                return r;
            }

            
        } else if (IS_RED(r->left->right)) {
            if (IS_RED(r->right)) {
                r->color = RED;
                r->left->color = BLACK;
                r->right->color = BLACK;
                return r;
            } else {/*left rotate left child, right rotate root, color root black and new child red*/
                r->left->right->color = BLACK;
                r->color = RED;
                r->left = left_rotate(r->left);
                r = right_rotate(r);
                return r;
            }
        }
      
    
    } else if (IS_RED(r->right)) {
        
        if (IS_RED(r->right->left)) {
            if (IS_RED(r->left)) {
                r->color = RED;
                r->left->color = BLACK;
                r->right->color = BLACK;
                return r;
            } else { /* if A is black then right_rotate B ..*/
                r->right->left->color = BLACK;
                r->color = RED;
                r->right = right_rotate(r->right);
                r = left_rotate(r);
                return r;
            }

            
        } else if (IS_RED(r->right->right)) {
            if (IS_RED(r->left)) {
                r->color = RED;
                r->left->color = BLACK;
                r->right->color = BLACK;
                return r;
            } else {
                r->color = RED;
                r->right->color = BLACK;
                r = left_rotate(r);
                return r;
            }
        }
    }

    return r;

}


rbt rbt_insert(rbt r, char *s) {

    
    if (r == NULL) {
        r = malloc(sizeof(*r));
        r->left = NULL;
        r->right = NULL;
        r->key = malloc(sizeof(r->key[0]) * (strlen(s) + 1));
        strcpy(r->key, s);
        r->color = RED;
        r = rbt_fix(r);
        return r;
    }

    
    if (strcmp(r->key, s) == 0) {
        return r;
    }

    if (strcmp(s, r->key) < 0) {
        r->left = rbt_insert(r->left, s);
    } else {
        r->right = rbt_insert(r->right, s);
    }

    r = rbt_fix(r);
    return r;
    
  
}


rbt rbt_new() {
    return NULL;
}



int rbt_search(rbt r, char *str) {

    if (r == NULL) {
        return 0;
    }

    if (r->key == str) {
        return 1;
    }

    if (r->key > str) {
        rbt_search(r->left, str);
    } else {
        rbt_search(r->right, str);
    }
    return 0;
}


 








