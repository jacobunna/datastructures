#include <stdio.h>

#include "minunit.h"
#include "ll.h"

static char * test_queue()
{
  Queue q;

  q = getQueue();

  mu_assert(q->len == 0, "Initial length of queue is not 0 [0001]");

  q->enqueue(q, 15);
  q->enqueue(q, 150);
  q->enqueue(q, 1500);
  q->enqueue(q, 15000);
  q->enqueue(q, 150000);

  mu_assert(q->len == 5, "Queue with 5 elements does not have length 5 "
    "[0002]");
  mu_assert(q->pop(q) == 15, "Unexpected element popped from queue [0003]");
  mu_assert(q->len == 4, "Queue length should be 4 after popping 1 element "
    "[0004]");
  mu_assert(q->pop(q) == 150, "Unexpected element popped from queue [0005]");
  mu_assert(q->len == 3, "Queue length should be 3 after popping 1 element "
    "[0006]");

  q->enqueue(q, 1);

  mu_assert(q->len == 4, "Queue length should be 4 after enqueueing [0007]");

  q->destroy(q);

  return 0;
}

static char * test_stack()
{
  Stack s;

  s = getStack();

  mu_assert(s->len == 0, "Initial length of stack is not 0 [0008]");

  s->add(s, 15);
  s->add(s, 150);
  s->add(s, 1500);
  s->add(s, 15000);
  s->add(s, 150000);

  mu_assert(s->len == 5, "Stack with 5 elements does not have length 5 "
    "[0009]");
  mu_assert(s->pop(s) == 150000, "Unexpected element popped from stack "
    "[0010]");
  mu_assert(s->len == 4, "Stack length should be 4 after popping 1 element "
    "[0011]");
  mu_assert(s->pop(s) == 15000, "Unexpected element popped from stack [0012]");
  mu_assert(s->len == 3, "Stack length should be 3 after popping 1 element "
    "[0013]");

  s->add(s, 1);

  mu_assert(s->len == 4, "Stack length should be 4 after enqueueing [0014]");

  s->destroy(s);

  return 0;
}

static char * test_deque()
{
  Deque d;

  d = getDeque();

  /* Check initial length */

  mu_assert(d->len == 0, "Initial length of deque is not 0 [0015]");

  /* Check we can add left from length zero and pop it */

  d->addLeft(d, 15);
  mu_assert(d->len == 1, "Deque with 1 element does not have length 1 [0016]");
  mu_assert(d->popLeft(d) == 15, "Unexpected element popped from left of "
    "deque [0017]");
  mu_assert(d->len == 0, "Deque with 0 elements does not have length 0 "
    "[0018]");

  /* Check we can add right from length zero and pop it */

  d->addRight(d, 150);
  mu_assert(d->len == 1, "Deque with 1 element does not have length 1 [0019]");
  mu_assert(d->popRight(d) == 150, "Unexpected element popped from right of "
    "deque [0020]");
  mu_assert(d->len == 0, "Deque with 0 elements does not have length 0 "
    "[0021]");

  /* Check we can insert from left and pop from right and vice versa */

  d->addLeft(d, 1500);
  mu_assert(d->len == 1, "Deque with 1 element does not have length 1 [0022]");
  mu_assert(d->popRight(d) == 1500, "Unexpected element popped from right of "
    "deque [0023]");
  mu_assert(d->len == 0, "Deque with 0 elements does not have length 0 "
    "[0024]");
  d->addRight(d, 15000);
  mu_assert(d->len == 1, "Deque with 1 element does not have length 1 [0025]");
  mu_assert(d->popLeft(d) == 15000, "Unexpected element popped from left of "
    "deque [0026]");
  mu_assert(d->len == 0, "Deque with 0 elements does not have length 0 "
    "[0027]");

  /* More complicated test with multiple insertions and pops from both sides */

  d->addLeft(d, 1);
  d->addLeft(d, 3);
  d->addRight(d, 2);
  d->addLeft(d, 5);
  d->addRight(d, 4);
  d->addRight(d, 6);
  mu_assert(d->len == 6, "Deque with 6 elements does not have length 6 "
    "[0028]");
  mu_assert(d->popLeft(d) == 5, "Unexpected element popped from left of "
    "deque [0029]");
  mu_assert(d->popRight(d) == 6, "Unexpected element popped from right of "
    "deque [0030]");
  mu_assert(d->popRight(d) == 4, "Unexpected element popped from right of "
    "deque [0031]");
  mu_assert(d->popRight(d) == 2, "Unexpected element popped from right of "
    "deque [0032]");
  mu_assert(d->popRight(d) == 1, "Unexpected element popped from right of "
    "deque [0033]");
  mu_assert(d->popLeft(d) == 3, "Unexpected element popped from left of "
    "deque [0034]");
  mu_assert(d->len == 0, "Deque with 0 elements does not have length 0 "
    "[0035]");

  d->destroy(d);

  return 0;
}

static char * all_tests()
{
  mu_suite_start();
  mu_run_test(test_queue);
  mu_run_test(test_stack);
  mu_run_test(test_deque);
  return 0;
}

RUN_TESTS(all_tests)
