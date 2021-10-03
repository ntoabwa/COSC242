#include <stdio.h>
#include <stdlib.h>
#include "mylib.h"
#include "queue.h"
#include <string.h>


struct queue {
    double *items;
    int head;
    int capacity;
    int num_items;
};        



queue queue_new() {
    
    int default_size = 7;
    queue q = emalloc(sizeof *q);
    q->capacity = default_size;
    q->num_items = 0;
    q->head = 0;
    q->items = emalloc(q->capacity * sizeof q->items[0]);

    return q;
   
}



void enqueue (queue q, double item){
    
    if (q->num_items < q->capacity) {
        q->items[(q->head + q->num_items++) % q->capacity] = item;
    }
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


   
    

    










