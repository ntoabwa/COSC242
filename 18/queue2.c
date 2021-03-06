#include <stdio.h>
#include <stdlib.h>
#include "mylib.h"
#include "queue.h"
#include <string.h>


struct q_item {
    double item;
    q_item next;
};

struct queue {
    q_item first;
    q_item last;
    int length;
};       


queue queue_new() {
    
    queue q = emalloc(sizeof *q);
    q->first = NULL;
    q->last = NULL;
    q->length = 0;

    return q;
   
}



void enqueue (queue q, double item){
    
    queue temp = queue_new();
    if (q->

    
   
}



double dequeue(queue q) {

    double item;
    
    if (q->num_items > 0) {
        item = q->items[q->head];
       
    }

    q->head++;
    q->num_items--;

    return item;
}


void queue_print(queue q) {
    
    int i;
    
    for (i = 0; i < q->capacity; i++) {
        printf("%.2f\n", q->items[i]);
    }   
}


void queue_print_info(queue q) {
    
    int i;
    printf("capacity % d, num_items % d, head % d\n[", q->capacity,
           q->num_items, q->head);

    for (i = 0; i < q->capacity; i++) {
        printf("%s%.2f", i == 0 ? "" : ", ", q->items[i]);
    }
    printf("]\n");
}




int queue_size(queue q) { 
    return q->num_items;    
}



queue queue_free(queue q) {
    
    /* for (i = 0; i < q->capacity; i++) { */
    /*     free(q->items[i]); */
    /* } */

    free(q->items);
    free(q);
    return NULL;
}


    

    










