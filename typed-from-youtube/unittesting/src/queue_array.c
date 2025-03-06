#include <stdio.h>
#include <stdlib.h>

#include "queue_array.h"

void init_queue(queue *q, int max_size) {
  q->size = max_size;
  q->values = malloc(sizeof(int) * q->size);
  q->num_entries = 0; // we're empty
  q->head = 0;
  q->tail = 0;
}

bool queue_empty(queue *q) {
  return (q->num_entries == 0);
}

bool queue_full(queue *q) {
  return (q->num_entries == q->size);
}

void queue_destroy(queue *q) {
  free(q->values);
}

bool enqueue(queue *q, int value) {
  if(queue_full(q)) {
    return false;
  }
  q->values[q->tail] = value;
  q->num_entries++;
  q->tail = (q->tail + 1) % q->size;
  return true;
}

int dequeue(queue *q) {
  int result;

  if (queue_empty(q)) {
    return QUEUE_EMPTY;
  }
  result = q->values[q->head];
  q->head = (q->head + 1) % q->size;
  q->num_entries--;

  return result;
}

/*
int main() {
  queue q1;
  init_queue(&q1, 5);

  enqueue(&q1, 56);
  enqueue(&q1, 47);
  enqueue(&q1, 3);
  enqueue(&q1, 148);
  enqueue(&q1, 72);
  enqueue(&q1, 11);

  int t;
  while ((t = dequeue(&q1)) != QUEUE_EMPTY) {
    printf("t = %d\n", t);
  }
}

*/
