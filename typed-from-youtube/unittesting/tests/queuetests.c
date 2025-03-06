#include <criterion/criterion.h>

#include "../src/queue_array.h"

queue *q = NULL;

void suitesetup(void) {
  q = (queue *)malloc(sizeof(queue));
}

void suiteteardown(void) {
  free(q);
}

TestSuite(queuetests, .init=suitesetup, .fini=suiteteardown);

Test(queuetests, create) {
  cr_expect(q != NULL, "queue should not be NULL");
  init_queue(q, 5);
  cr_expect(queue_empty(q) == true, "queue should be empty");
}
