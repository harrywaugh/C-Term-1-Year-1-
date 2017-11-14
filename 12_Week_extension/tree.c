#include <stdlib.h>
#include <stdio.h>
#include <memory.h>
#include "tree.h"

node* newNode(void* p, int b)
{
    node* newNode = malloc(sizeof(node));
    newNode->key = malloc((size_t)b);
    *newNode = (node) {NULL, NULL, p, NULL };
    return newNode;
}

tree* newTree(int b)
{
    tree *t = malloc(sizeof(tree));
    t->bytes = b;
    t->root = NULL;
    return t;
}

int treeLength(tree *t)
{
    t->current = t->root;
    int length = 0;
    while(t->current->next !=NULL)
    {
        t->current = t->current->next;
        length++;
    }
    t->current = t->root;
    return length+1;
}

void startTree(tree* t)
{
    t->current = t->root;
}

void getVal(tree* t, node* n, void *p )
{
    if(n->key != NULL)
    {
        memcpy(p, n->key, (size_t)t->bytes);
    }
    else
    {
        fprintf(stderr, "ERROR: Node has NULL key field.\n");
        exit(1);
    }
}

void setVal(tree* t, node* n, void *p)
{
    if(n->key != NULL)
    {
        memcpy(n->key, p, (size_t)t->bytes);
    }
}
