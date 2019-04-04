#include <stdio.h>
#include <assert.h>
#include <stdlib.h>

#include "array.h"

#define RB_DEQUE_INITIAL_SIZE (4)

/* Ring buffer deque */

static int _dequePopLeft(RbDeque d)
{
  int ret;
  if(d->len == 0)
  {
    return 0;
  }
  ret = d->content[d->base];
  d->base = (d->base + 1) % d->size;
  d->len--;
  return ret;
}

static int _dequePopRight(RbDeque d)
{
  int ret;
  if(d->len == 0)
  {
    return 0;
  }
  ret = d->content[(d->base + d->len - 1) % d->size];
  d->len--;
  return ret;
}

static void _dequePrint(RbDeque d)
{
  int i;
  for(i=0; i<d->len; i++)
  {
    printf("Element %d: %d\n", i, d->content[(i+d->base) % d->size]);
  }
}

static void _dequeDestroy(RbDeque d)
{
  free(d->content);
  free(d);
}

/* Note that this function does not populate `addLeft` and `addRight` because
 * this would create a circular reference. These need to be populated by the
 * caller.
 */
static RbDeque _getRbDequeInternal(int size)
{
  RbDeque ret;
  ret = malloc(sizeof(*ret));
  assert(ret);
  ret->base = 0;
  ret->len = 0;
  ret->size = size;
  ret->content = malloc(sizeof(int) * size);
  assert(ret->content);
  ret->popLeft = _dequePopLeft;
  ret->popRight = _dequePopRight;
  ret->print = _dequePrint;
  ret->destroy = _dequeDestroy;
  return ret;
}

static void _dequeAddInternal(RbDeque d, int elem, int direction)
{
  RbDeque tempDeque;
  int *oldContents;

  /* Grow the deque if necessary */
  assert(d->len <= d->size);
  if(d->len == d->size)
  {
    tempDeque = _getRbDequeInternal(d->size * 2);
    tempDeque->addLeft = d->addLeft;
    tempDeque->addRight = d->addRight;
    while(d->len)
    {
      tempDeque->addRight(tempDeque, d->popLeft(d));
    }
    oldContents = d->content;
    *d = *tempDeque;
    free(oldContents);
    free(tempDeque);
  }

  /* Add the element */
  if(direction == 0)
  {
    if(d->base == 0)
    {
      d->base = d->size - 1;
    }
    else
    {
      d->base--;
    }
    d->content[d->base] = elem;
  }
  else
  {
    d->content[(d->base + d->len) % d->size] = elem;
  }
  d->len++;
}

static void _dequeAddLeft(RbDeque d, int elem)
{
  _dequeAddInternal(d, elem, 0);
}

static void _dequeAddRight(RbDeque d, int elem)
{
  _dequeAddInternal(d, elem, 1);
}

RbDeque getRbDeque(void)
{
  RbDeque ret;
  ret = _getRbDequeInternal(RB_DEQUE_INITIAL_SIZE);
  ret->addLeft = _dequeAddLeft;
  ret->addRight = _dequeAddRight;
  return ret;
}
