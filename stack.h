/* Stacks, implemented as linked lists. Items are copied into the list.  The
implementation uses linked nodes, and nodes are re-used, so all the functions
run in O(1) time. Illegal operations cause the program to crash. */
#include <stdbool.h>

// The type of items stored in stacks.  The default is double, but can be
// changed to another type here.  If a pointer type is used, only the pointer is
// copied into the stack, not the memory pointed to.
typedef double item;

// The type of a stack (declared here and implemented in stack.c).
struct stack;
typedef struct stack stack;

// Create a new empty stack of items.
stack *create();

// Push an item onto the top of a stack.
void push(stack *s, item x);

// Pop an item from the top of a non-empty stack.
item pop(stack *s);

// Get the top item from a non-empty stack without removing it.
item top(stack *s);

// Check whether a stack is empty.
bool empty(stack *s);
