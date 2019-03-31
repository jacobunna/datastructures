/* Linked list interfaces
 *
 * In these data structures we always store the length so we can retrieve this
 * in O(1) time, even though this isn't a strict requirement of the data
 * structure.
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
