#include <stdio.h>
#include <stdlib.h>
#include "mylib.h"
#include "queue.h"

typedef struct q_item *q_item;

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
    q->lenth = 0;

    return q;

}

void enqueue(queue q, double item) {
    q_item i = emalloc(sizeof *i);
    i->item = item;
    i->next = NULL;
    if (q->length == 0) {
        q->first = i;
    } else {
        q->last->next = i;
    }
    q->last = i;
    q->length++;
}

double dequeue(queue q) {
    q_item d;
    double item;

    if (q->length == 0) {
        return 0;
    }
    d = q->first;
    item = q->first->item;
    q->first = q->first->next;
    free(d);
    q->length--;
    return item;

}

void queue_print(queue q) {
    int i;
    q_item key = q->first;

    for (i = 0; i < q->length; i++) {
        printf("%.2f\n", key->item);
        key = key->next;
    }
}

void queue_print_info(queue q) {
    if (q->length == 0) {
        printf("The queue is empty\n");
    } else {
        printf("first %.2f, last %.2f, length %d\n", q->first->item,
               q->last->item, q->length);
    }
}

int queue_size(queue q) {
    return q->length;
}



void queue_free_aux(q_item i) {
    q_item q = i;
    q_item d = q;

    while (q != NULL) {
        q = q->next;
        free(d);
        d = q;
    }
}


queue queue_free(queue q) {
    queue_free_aux(q->first);
    free(q);
    return q;
}
