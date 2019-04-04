#include <stdio.h>
#include <assert.h>
#include <stdlib.h>

#include "ll.h"

/* Element in a singly linked list */
struct llElt
{
  struct llElt *next;
  int value;
};

/* Element in a doubly linked list
 *
 * We store the next element as an array of length 2. In the public API 0 is
 * "left" and 1 is "right".
 */
struct llEltDbl
{
  struct llEltDbl *next[2];
  int value;
};

/* Queue */

static int _queuePop(Queue q)
{
  /* Remove an element from the head of the queue and return its value */
  struct llElt *removeElem;
  int ret;
  if(q->head == 0)
  {
    /* The queue is empty */
    assert(q->tail == 0);
    return 0;
  }
  removeElem = q->head;
  if(removeElem->next == 0)
  {
    /* This is the only element in the queue */
    assert(q->head == q->tail);
    q->head = 0;
    q->tail = 0;
  }
  else
  {
    q->head = removeElem->next;
  }
  ret = removeElem->value;
  free(removeElem);
  q->len--;
  return ret;
}

static void _queueEnqueue(Queue q, int elem)
{
  /* Add an element to the tail of the queue */
  struct llElt *newElem;
  newElem = malloc(sizeof(struct llElt));
  assert(newElem);
  newElem->value = elem;
  newElem->next = 0;
  if(q->head == 0)
  {
    /* The queue is empty */
    assert(q->tail == 0);
    q->head = newElem;
  }
  else
  {
    assert(q->tail);
    q->tail->next = newElem;
  }
  q->tail = newElem;
  q->len++;
}

static void _queuePrint(Queue q)
{
  struct llElt *e;
  int i = 0;
  for(e = q->head; e != 0; e = e->next)
  {
    printf("Element %d: %d\n", ++i, e->value);
  }
}

static void _queueDestroy(Queue q)
{
  struct llElt *e;
  for(e = q->head; e != 0; e = e->next)
  {
    q->pop(q);
  }
  free(q);
}

Queue getQueue(void)
{
  Queue ret;
  ret = malloc(sizeof(*ret));
  assert(ret);
  ret->head = 0;
  ret->tail = 0;
  ret->len = 0;
  ret->pop = _queuePop;
  ret->enqueue = _queueEnqueue;
  ret->print = _queuePrint;
  ret->destroy = _queueDestroy;
  return ret;
}

/* Stack */

static int _stackPop(Stack s)
{
  /* Remove an element from the head of the stack and return its value */
  struct llElt *removeElem;
  int ret;
  if(s->head == 0)
  {
    /* The stack is empty */
    return 0;
  }
  removeElem = s->head;
  if(removeElem->next == 0)
  {
    /* This is the only element in the stack */
    s->head = 0;
  }
  else
  {
    s->head = removeElem->next;
  }
  ret = removeElem->value;
  free(removeElem);
  s->len--;
  return ret;
}

static void _stackAdd(Stack s, int elem)
{
  /* Add an element to the head of the stack */
  struct llElt *newElem;
  newElem = malloc(sizeof(struct llElt));
  assert(newElem);
  newElem->value = elem;
  if(s->head == 0)
  {
    /* The stack is empty */
    newElem->next = 0;
  }
  else
  {
    newElem->next = s->head;
  }
  s->head = newElem;
  s->len++;
}

static void _stackPrint(Stack s)
{
  struct llElt *e;
  int i = 0;
  for(e = s->head; e != 0; e = e->next)
  {
    printf("Element %d: %d\n", ++i, e->value);
  }
}

static void _stackDestroy(Stack s)
{
  struct llElt *e;
  for(e = s->head; e != 0; e = e->next)
  {
    s->pop(s);
  }
  free(s);
}

Stack getStack(void)
{
  Stack ret;
  ret = malloc(sizeof(*ret));
  assert(ret);
  ret->head = 0;
  ret->len = 0;
  ret->pop = _stackPop;
  ret->add = _stackAdd;
  ret->print = _stackPrint;
  ret->destroy = _stackDestroy;
  return ret;
}

/* Deque */

static int _dequePopInternal(Deque d, int direction)
{
  struct llEltDbl *removeElem;
  int ret;

  assert(direction == 0 || direction == 1);

  if(d->head == 0)
  {
    /* The deque is empty */
    assert(d->tail == 0);
    return 0;
  }
  if(direction == 0)
  {
    removeElem = d->head;
  }
  else
  {
    removeElem = d->tail;
  }
  if(d->head == d->tail)
  {
    /* removeElem is the only element in the deque */
    d->head = 0;
    d->tail = 0;
  }
  else
  {
    if(direction == 0)
    {
      d->head = removeElem->next[1];
      d->head->next[0] = 0;
    }
    else
    {
      d->tail = removeElem->next[0];
      d->tail->next[1] = 0;
    }
  }
  ret = removeElem->value;
  /*free(removeElem);*/
  d->len--;
  return ret;
}

static int _dequePopLeft(Deque d)
{
  return _dequePopInternal(d, 0);
}

static int _dequePopRight(Deque d)
{
  return _dequePopInternal(d, 1);
}

static void _dequeAddInternal(Deque d, int elem, int direction)
{
  struct llEltDbl *newElem;

  assert(direction == 0 || direction == 1);

  newElem = malloc(sizeof(struct llEltDbl));
  assert(newElem);
  newElem->value = elem;
  newElem->next[0] = 0;
  newElem->next[1] = 0;
  if(d->head == 0)
  {
    /* The deque is empty */
    assert(d->tail == 0);
    d->head = d->tail = newElem;
  }
  else
  {
    assert(d->tail);
    if(direction == 0)
    {
      newElem->next[1] = d->head;
      d->head->next[0] = newElem;
      d->head = newElem;
    }
    else
    {
      newElem->next[0] = d->tail;
      d->tail->next[1] = newElem;
      d->tail = newElem;
    }
  }
  d->len++;
}

static void _dequeAddLeft(Deque d, int elem)
{
  _dequeAddInternal(d, elem, 0);
}

static void _dequeAddRight(Deque d, int elem)
{
  _dequeAddInternal(d, elem, 1);
}

static void _dequePrint(Deque d)
{
  struct llEltDbl *e;
  int i = 0;
  for(e = d->head; e != 0; e = e->next[1])
  {
    printf("Element %d: %d\n", ++i, e->value);
  }
}

static void _dequeDestroy(Deque d)
{
  struct llEltDbl *e;
  for(e = d->head; e != 0; e = e->next[1])
  {
    d->popLeft(d);
  }
  free(d);
}

Deque getDeque(void)
{
  Deque ret;
  ret = malloc(sizeof(*ret));
  assert(ret);
  ret->head = 0;
  ret->tail = 0;
  ret->len = 0;
  ret->popLeft = _dequePopLeft;
  ret->popRight = _dequePopRight;
  ret->addLeft = _dequeAddLeft;
  ret->addRight = _dequeAddRight;
  ret->print = _dequePrint;
  ret->destroy = _dequeDestroy;
  return ret;
}

/* Circular linked list */

static CllElt _cllAddInternal(CllElt e, int elem, int direction)
{
  CllElt ret;

  assert(direction == 0 || direction == 1);

  /* If we try and share code with `getCll` we will end up with a circular
   * reference. To get around this we "borrow" the function pointers from `e`
   * when creating a new `CllElt` here. This allows us to in effect do some
   * introspection, as we can get a pointer to the function (`_cllAddLeft` or
   * `_cllAddRight`) that is calling this one.
   */
  ret = malloc(sizeof(*ret));
  assert(ret);

  ret->value = elem;
  ret->addLeft = e->addLeft;
  ret->addRight = e->addRight;
  ret->pop = e->pop;
  ret->print = e->print;
  ret->destroy = e->destroy;

  if(direction == 0)
  {
    ret->next = e;
    ret->previous = e->previous;
    e->previous->next = ret;
    e->previous = ret;
  }
  else
  {
    ret->previous = e;
    ret->next = e->next;
    e->next->previous = ret;
    e->next = ret;
  }

  return ret;
}

static CllElt _cllAddLeft(CllElt e, int elem)
{
  return _cllAddInternal(e, elem, 0);
}

static CllElt _cllAddRight(CllElt e, int elem)
{
  return _cllAddInternal(e, elem, 1);
}

static int _cllPop(CllElt e)
{
  int ret;

  ret = e->value;
  e->next->previous = e->previous;
  e->previous->next = e->next;
  free(e);

  return ret;
}

static void _cllPrint(CllElt e)
{
  CllElt t;
  int i = 0;

  t = e;
  do
  {
    printf("Element %d: %d\n", ++i, t->value);
    t = t->next;
  } while(t != e);
}

static void _cllDestroy(CllElt e)
{
  CllElt thisDeletion;
  CllElt nextDeletion;

  thisDeletion = e;
  do
  {
    nextDeletion = thisDeletion->next;
    free(thisDeletion);
    thisDeletion = nextDeletion;
  } while(thisDeletion != e);
}

CllElt getCll(int elem)
{
  CllElt ret;
  ret = malloc(sizeof(*ret));
  assert(ret);

  ret->value = elem;
  ret->addLeft = _cllAddLeft;
  ret->addRight = _cllAddRight;
  ret->pop = _cllPop;
  ret->print = _cllPrint;
  ret->destroy = _cllDestroy;

  ret->previous = ret;
  ret->next = ret;
  return ret;
}
