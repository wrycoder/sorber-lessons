#ifndef __QUEUE_ARRAY_H
#define __QUEUE_ARRAY_H

#include <limits.h>
#include <stdbool.h>

#define QUEUE_EMPTY INT_MIN

typedef struct {
  int *values;
  int head, tail, num_entries, size;
} queue;

void init_queue(queue *, int);
bool queue_empty(queue *);
bool queue_full(queue *);
void queue_destroy(queue *);
bool enqueue(queue *, int);
int dequeue(queue *);
int main();

#endif // __QUEUE_ARRAY_H
