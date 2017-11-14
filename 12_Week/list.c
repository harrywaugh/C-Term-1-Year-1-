#include "list.h"
#include <stdlib.h>
#include <stdio.h>
#include <memory.h>

struct node
{
    struct node* previous;
    void*        item;
    struct node* next;
};
typedef struct node node;
struct list
{
    node* first;
    node* current;
    node* last;
    int bytes;
    int length;
};
typedef struct list list;

list *newList(int b)
{
    list *nList = (list *)malloc(sizeof(list *));

    node *leftSentinel      = (node *)malloc(sizeof(node *));
    leftSentinel->item      = malloc((size_t)b);
    *leftSentinel           = (node) {leftSentinel, NULL, leftSentinel};

    *nList = (list) {leftSentinel, leftSentinel, leftSentinel->previous, b, 0};
    return nList;
}

void start(list *l)
{
    l->current = l->first;
}

void end(list *l)
{
    l->current=l->last;
}

bool atStart(list *l)
{
    if(l->current == l->first){
        return true;
    }
    return false;
}

bool atEnd(list *l)
{
    if(l->current == l->last){
        return true;
    }
    return false;
}

void forward(list *l)
{
    if(l->current != l->last)
    {
        l->current = l->current->next;
    }
    else
    {
        printf("ERROR: Already at last position, can not go forwards.\n");
    }
}

void backward(list *l)
{
    if(l->current != l->first)
    {
        l->current = l->current->previous;
    }
    else
    {
        printf("ERROR: Already at first position, can not go backwards.\n");
    }
}

void insertBefore(list *l, void *p)
{
    node *newNode = (node *)malloc(sizeof(node *));
    newNode->item = malloc((size_t)l->bytes);
    *newNode = (node) {l->current, p, l->current->next};

    l->current->next->previous = newNode;
    l->current->next           = newNode;
    l->current                 = newNode;
    l->last                    = l->first->previous;
    l->length++;
}

void insertAfter(list *l, void *p)
{
    node *newNode = (node *)malloc(sizeof(node *));
    newNode->item = malloc((size_t)l->bytes);
    *newNode = (node) {l->current, p, l->current->next};

    l->current->next->previous      = newNode;
    l->current->next                = newNode;
    l->last                         = l->first->previous;
    l->length++;
}

void getBefore(list *l, void *p)
{
    if(!atStart(l))
    {
        memcpy(p, l->current->item, (size_t)l->bytes);
    }
    else
    {
        fprintf(stderr, "ERROR: Already at first position, therefore can not get previous item.\n");
        exit(1);
    }
}

void getAfter(list *l, void *p)
{
    if(!atEnd(l))
    {
        memcpy(p, l->current->next->item, (size_t)l->bytes);

    }
    else
    {
        fprintf(stderr, "ERROR: Already at last position, therefore can not get next item.\n");
        exit(1);
    }
}

void setBefore(list *l, void *p)
{
    if(!atStart(l))
    {
        memcpy(l->current->item, p, (size_t)l->bytes);

    }
    else
    {
        fprintf(stderr, "ERROR: Already at first position, therefore can not set previous item.\n");
        exit(1);
    }
}

void setAfter(list *l, void *p)
{
    if(!atEnd(l))
    {
        memcpy(l->current->next->item, p, (size_t)l->bytes);

    }
    else
    {
        fprintf(stderr, "ERROR: Already at last position, therefore can not set next item.\n");
        exit(1);
    }
}

void deleteBefore(list *l)
{
    if(!atStart(l))
    {
        node* removedNode               = l->current;
        l->current->previous->next      = l->current->next;
        l->current->next->previous      = l->current->previous;

        l->current                      = l->current->previous;
        l->last                         = l->first->previous;
        l->length--;
        free(removedNode);
    }
    else
    {
        printf("ERROR: Already at first position, therefore can not delete previous item.\n");
    }
}

void deleteAfter(list *l)
{
    if(!atEnd(l))
    {
        node* removedNode                      = l->current->next;
        l->current->next->next->previous       = l->current;
        l->current->next                       = l->current->next->next;

        l->last                         = l->first->previous;
        l->length--;
        free(removedNode);
    }
    else
    {
        printf("ERROR: Already at last position, therefore can not delete next item.\n");
    }
}

int testLists()
{
    int testCompleted = 0;
    //TESTS 1 TO 3 - newList(), atEnd(), atStart()
    //Create new int list pointer
    list* int_list = newList(sizeof(int));
    //Checks that initial list length is 0, and that the current position is both the
    // beginning and the end position
    if(atStart(int_list)) testCompleted++;
    else return testCompleted;
    if(atEnd(int_list)) testCompleted++;
    else return testCompleted;
    if(int_list->length == 0) testCompleted++;
    else return testCompleted;

    //TESTS 4 TO 8 - insertBefore(), insertAfter(), backward(), atEnd(), atStart()
    //Add new node before current position
    int nodeItem1 = 2;
    insertBefore(int_list, &nodeItem1);
    //Check length is now 1
    if(int_list->length == 1) testCompleted++;
    else return testCompleted;
    //Check current position is not at start position
    if(!atStart(int_list)) testCompleted++;
    else return testCompleted;
    //Check current position is now at the end position
    if(atEnd(int_list)) testCompleted++;
    else return testCompleted;
    //Move backwards and then check that the current position is at the start
    backward(int_list);
    //Insert new node after current position
    int nodeItem0 = 1;
    insertAfter(int_list, &nodeItem0);
    if(atStart(int_list)) testCompleted++;
    else return testCompleted;
    //Check that current position is no longer the last
    if(!atEnd(int_list)) testCompleted++;
    else return testCompleted;

    //TESTS 9 TO 11 - start(), end()
    //First test confirms that current position is the first in a
    //list with two items
    if(atStart(int_list) && int_list->length == 2) testCompleted++;
    else return testCompleted;
    //Move current position to last position, and check it
    end(int_list);
    if(atEnd(int_list)) testCompleted++;
    else return testCompleted;
    //Move current position to first position, and check it
    start(int_list);
    if(atStart(int_list)) testCompleted++;
    else return testCompleted;

    //TESTS 12 TO 13 - forward(), getBefore(), getAfter()
    //List should be at start position, list is of length 2,
    //and the values are: Node 1's value should be 1, Node
    //2's values should be 2.
    //First move current position to inbetween the Node 1 and 2.
    start(int_list);
    forward(int_list);
    //Check Node 1's value is 1;
    int test_value = 42;
    getBefore(int_list, &test_value);
    if(test_value == 1) testCompleted++;
    else return testCompleted;
    //Check Node 2's value is 2
    getAfter(int_list, &test_value);
    if(test_value == 2) testCompleted++;
    else return testCompleted;

    //TESTS 14 TO 15 - setBefore(), setAfter()
    //Now that we know that the list contains two nodes with
    //values 1 and 2, we will try setting them and retrieving them.
    //Set previous node to 100 and check it
    int firstNode = 100;
    setBefore(int_list, &firstNode);
    getBefore(int_list, &test_value);
    if(test_value == 100) testCompleted++;
    else return testCompleted;
    int secondNode = 200;
    setAfter(int_list, &secondNode);
    getAfter(int_list, &test_value);
    if(test_value == 200) testCompleted++;
    else return testCompleted;

    //TESTS 16 TO 18 - deleteBefore()
    //Send current position to the end of the list
    //Delete the element before it
    end(int_list);
    deleteBefore(int_list);
    //Check that there is only one element left by
    //checking length and that the current position ism last
    if(int_list->length == 1) testCompleted++;
    else return testCompleted;
    //Now we go to the start of the list and delete the final element.
    //And check this using length, and that it is the start and end.
    start(int_list);
    deleteAfter(int_list);
    if(int_list->length == 0) testCompleted++;
    else return testCompleted;
    if(atEnd(int_list) && atStart(int_list)) testCompleted++;




    return testCompleted;
}

























