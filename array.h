/* Array data structure interfaces */

/* Ring buffer deque
 *
 * This looks very similar to the `Deque` in `ll.h`, and should behave
 * identically. However, the implementation will use a ring buffer instead of a
 * linked list.
 */

/* Deque typedef */
typedef struct rbDeque *RbDeque;

/* Get a deque of integers */
RbDeque getRbDeque(void);

/* Deque struct */
struct rbDeque
{
  size_t base;
  size_t len;
  size_t size;
  int *content;

  void (*addLeft) (RbDeque d, int elem);
  void (*addRight) (RbDeque d, int elem);
  int (*popLeft) (RbDeque d);
  int (*popRight) (RbDeque d);
  void (*print) (RbDeque d);
  void (*destroy) (RbDeque d);
};
