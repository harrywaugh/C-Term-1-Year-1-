#include <stdlib.h>
#include "tree.h"

node* newNode(void* p, int b)
{
    node* newNode = malloc(sizeof(node));
    newNode->key = malloc((size_t)b);
    *newNode = (node) {NULL, NULL, p, NULL };
    return newNode;
}



tree* newTree()
{
    tree *t = malloc(sizeof(tree));
    t->root = NULL;
    return t;
}

