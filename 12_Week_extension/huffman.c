#include "tree.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
struct letterScore
{
    int frequency;
    char letter;
};
typedef struct letterScore letterScore;

bool inArray(int *Arr, int element, int length)
{
    for(int i = 0; i < length; i++)
    {
        if(Arr[i] == element)
        {
            return true;
        }
    }
    return false;
}

letterScore* newStruct(char letter, int freq)
{
    letterScore* tempStruct = malloc(sizeof(letterScore));
    *tempStruct = (letterScore) {freq, letter};
    return tempStruct;
}

int containsChar(tree *t, char letter)
{
    startTree(t);
    letterScore tempStruct;
    int count = 0;
    while(t->current != NULL)
    {
        memcpy(&tempStruct, t->current->key, sizeof(letterScore));
        if(tempStruct.letter == letter)
        {
            return count;
        }
        t->current = t->current->next;
        count++;
    }
    return -1;
}

void increaseFreq(tree *t, int element)
{
    startTree(t);
    letterScore* tempStruct = malloc(sizeof(letterScore));
    for(int i = 0; i < element; i++)    t->current = t->current->next;
    getVal(t, t->current, tempStruct);
    (*tempStruct).frequency++;
    setVal(t, t->current, tempStruct);
}

void endTree(tree *t)
{
    startTree(t);
    int count = 0;
    while(t->current->next !=NULL)
    {
        t->current = t->current->next;
        count++;
    }
}

void getFrequencies(tree* huffmanTree, char* text)
{
    startTree(huffmanTree);
    huffmanTree->root = newNode(newStruct(text[0], 1), sizeof(letterScore));
    huffmanTree->current =huffmanTree->root;
    for(int i = 1; i < strlen(text); i++)
    {
        int itemPosition = containsChar(huffmanTree, text[i]);
        if(itemPosition != -1)
        {
            increaseFreq(huffmanTree, itemPosition);
        }
        else
        {
            endTree(huffmanTree);
            huffmanTree->current->next = newNode(newStruct(text[i], 1), sizeof(letterScore));
        }
    }
}

void printTree(node* t, int indent)
{
    for(int i = 0; i < indent; i++) printf(" ");
    if(t->key != NULL)
    {
        letterScore tempStruct;
        memcpy(&tempStruct, t->key, sizeof(letterScore));
        printf("%c:%d\n", tempStruct.letter, tempStruct.frequency);
    }
    if(t->left != NULL)
    {
        printTree(t->left, indent + 4);
    }
    if(t->right != NULL)
    {
        printTree(t->right, indent + 4);
    }

}

tree* insertionSort(tree* t)
{
    tree* sortedTree = newTree(sizeof(letterScore));
    node* highestNode;

    int length = treeLength(t);
    int usedPositions[length];
    for(int i = 0; i < length; i++) usedPositions[i] = -1;
    int highestFrequency;
    letterScore tempStruct;
    for(int i = 0; i < length; i++)
    {
        highestFrequency = 0;
        startTree(t);
        for(int j = 0; j < length; j++)
        {
            getVal(sortedTree, t->current, &tempStruct);
            if(tempStruct.frequency > highestFrequency && !inArray(usedPositions, j, length))
            {
                highestFrequency = tempStruct.frequency;
                highestNode      = t->current;
                usedPositions[i] = j;
            }
            t->current = t->current->next;
        }
        node* nNode = malloc(sizeof(node));
        memcpy(nNode, highestNode, sizeof(node));
        if(i == 0)
        {
            sortedTree->root = malloc(sizeof(node));
            memcpy(sortedTree->root, nNode, sizeof(letterScore));
            startTree(sortedTree);
            sortedTree->current->next = NULL;
        }
        endTree(sortedTree);
        sortedTree->current->next          = malloc(sizeof(node));
        //memcpy(sortedTree->current->next, nNode, sizeof(letterScore));
        getVal(sortedTree, nNode, sortedTree->current->next);
        sortedTree->current->next->next    = NULL;
        sortedTree->current->key = malloc(sizeof(letterScore));
        memcpy(sortedTree->current->key, nNode->key, sizeof(letterScore));
        sortedTree->current->right         = nNode->right;
        sortedTree->current->left          = nNode->left;
        free(nNode);
    }
    startTree(sortedTree);
    for(int i = 1; i < length; i++)
    {
        sortedTree->current = sortedTree->current->next;
    }
    sortedTree->current->next =NULL;
    return sortedTree;

}

tree* huffmanAlgorithm(tree* huffmanTree)
{
    int Initlength = treeLength(huffmanTree);
    for(int i = 0; i < Initlength - 1; i++)
    {
        int length      = treeLength(huffmanTree);
        huffmanTree     = insertionSort(huffmanTree);
        letterScore leftStruct, rightStruct;
        letterScore* parentStructP;
        startTree(huffmanTree);
        if(length > 2)
        {
            for(int y = 0; y < length-3; y++)
            {
                huffmanTree->current = huffmanTree->current->next;
            }
            getVal(huffmanTree, huffmanTree->current->next, &leftStruct);
            getVal(huffmanTree, huffmanTree->current->next->next, &rightStruct);

            int newFreq                = leftStruct.frequency + rightStruct.frequency;
            parentStructP              = newStruct('*', newFreq);
            node* nNode                = newNode(parentStructP, sizeof(letterScore));
            nNode->right               = huffmanTree->current->next;
            nNode->left                = huffmanTree->current->next->next;
            nNode->right->next         = nNode;
            nNode->left->next          = nNode;
            huffmanTree->current->next = nNode;
        }
        else
        {
            getVal(huffmanTree, huffmanTree->root, &leftStruct);
            getVal(huffmanTree, huffmanTree->root->next, &rightStruct);

            int newFreq                = leftStruct.frequency + rightStruct.frequency;
            parentStructP              = newStruct('*', newFreq);
            node* nNode                = newNode(parentStructP, sizeof(letterScore));
            nNode->left                = huffmanTree->root->next;
            nNode->right               = huffmanTree->root;
            nNode->right->next         = nNode;
            nNode->left->next          = nNode;
            huffmanTree->root          = nNode;
            startTree(huffmanTree);
        }

    }
    return huffmanTree;
}

int main(int argc, char *argv[argc])
{
    tree* huffmanTree = newTree(sizeof(letterScore));
    char *text = "aaaaaaaaaaaaaaaaaaaaaaaabbbbbbbbbbbbcccccccccceeeeeeeedddddddd";
    getFrequencies(huffmanTree, text);
    huffmanTree = insertionSort(huffmanTree);
    huffmanTree = huffmanAlgorithm(huffmanTree);
    printTree(huffmanTree->root, 4);
    return 0;
}
