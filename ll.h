/* Linked list interfaces
 *
 * In these data structures we store the length so we can retrieve this in O(1)
 * time, even though this isn't a strict requirement of the data structure. The
 * only exception is for circular linked lists, where no such global
 * information can be held.
 */

/* Queue */

/* Queue typedef */
typedef struct queue *Queue;

/* Get a queue of integers */
Queue getQueue(void);

/* Queue struct */
struct queue
{
  struct llElt *head;
  int len;
  struct llElt *tail;

  void (*enqueue) (Queue q, int elem);
  int (*pop) (Queue q);
  void (*print) (Queue q);
  void (*destroy) (Queue q);
};

/* Stack */

/* Stack typedef */
typedef struct stack *Stack;

/* Get a stack of integers */
Stack getStack(void);

/* Stack struct */
struct stack
{
  struct llElt *head;
  int len;

  void (*add) (Stack s, int elem);
  int (*pop) (Stack s);
  void (*print) (Stack s);
  void (*destroy) (Stack s);
};

/* Deque */

/* Deque typedef */
typedef struct deque *Deque;

/* Get a deque of integers */
Deque getDeque(void);

/* Deque struct */
struct deque
{
  struct llEltDbl *head;
  struct llEltDbl *tail;
  int len;

  void (*addLeft) (Deque d, int elem);
  void (*addRight) (Deque d, int elem);
  int (*popLeft) (Deque d);
  int (*popRight) (Deque d);
  void (*print) (Deque d);
  void (*destroy) (Deque d);
};

/* Circular linked list
*
* There is no concept of a circular linked list per se, only its constituent
* elements. All operations on a circular linked list are done locally with
* respect to that element. The `addLeft` and `addRight` methods return a
* pointer to the new element.
*
* The methods `print` and `destroy` both act on the entire list by starting
* with the supplied element and cycling through the list until the first
* element is reached again.
*/

/* Circular linked list element typedef */
typedef struct cllElt *CllElt;

/* Get a circular linked list element */
CllElt getCll(int elem);

/* Circular linked list struct */
struct cllElt
{
  struct cllElt *previous;
  struct cllElt *next;
  int value;

  CllElt (*addLeft) (CllElt e, int elem);
  CllElt (*addRight) (CllElt e, int elem);
  int (*pop) (CllElt e);
  void (*print) (CllElt e);
  void (*destroy) (CllElt e);
};
