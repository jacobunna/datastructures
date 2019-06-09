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

/* Hash table */

/* Hash table typedef */
typedef struct hashTable *HashTable;

/* Get an integer hashtable */
HashTable getHashTable(void);

/* Individual hash table item
 * This is a linked list of items. If `next` is a null pointer then this is the
 * last element.
 */
struct hashTableItem
{
  struct hashTableItem *next;
  int value;
};

/* Hash table struct */
struct hashTable
{
  struct hashTableItem **items;
  int size;
  int len;

  void (*putItem) (HashTable t, int elem);
  int (*getItem) (HashTable t, int elem);
  void (*removeItem) (HashTable t, int elem);
  void (*destroy) (HashTable t);
};
