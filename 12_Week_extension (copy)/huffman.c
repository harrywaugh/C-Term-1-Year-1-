#include "list.h"
#include "tree.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
struct letterScore
{
    int frequency;
    char letter;
};
typedef struct letterScore letterScore;

letterScore* newStruct(char letter, int freq)
{
    letterScore* tempStruct = malloc(sizeof(letterScore));
    *tempStruct = (letterScore) {freq, letter};
    return tempStruct;
}

int containsChar(tree *t, char letter)
{
    t->current = t->root;
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
    t->current = t->root;
    letterScore* tempStruct = malloc(sizeof(letterScore));
    for(int i = 0; i < element; i++)    t->current = t->current->next;
    memcpy(tempStruct, t->current->key, sizeof(letterScore));
    (*tempStruct).frequency++;
    memcpy( t->current->key, tempStruct, sizeof(letterScore));

}

void endTree(tree *t)
{
    t->current = t->root;
    int count = 0;
    while(t->current->next !=NULL)
    {
        t->current = t->current->next;
        count++;
    }
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

void getFrequencies(tree* huffmanTree, char* text)
{
    huffmanTree->current = huffmanTree->root;
    int treeLength = 0;
    for(int i = 0; i < strlen(text); i++)
    {
        int itemPosition = containsChar(huffmanTree, text[i]);
        if(itemPosition != -1)
        {
            increaseFreq(huffmanTree, itemPosition);
        }
        else
        {
            if(huffmanTree->root == NULL)
            {
                huffmanTree->root = newNode(newStruct(text[i], 1), sizeof(letterScore));
                huffmanTree->current =huffmanTree->root;
            }
            else
            {
                endTree(huffmanTree);
                huffmanTree->current->next = newNode(newStruct(text[i], 1), sizeof(letterScore));
            }
            treeLength++;
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

tree* insertionSort(tree* t)
{
    tree* sortedTree = newTree();
    letterScore tempStruct2;
    node* lowestNode = newNode(&tempStruct2, sizeof(letterScore));

    int length = treeLength(t);
    int usedPositions[treeLength(t)];
    for(int i = 0; i < length; i++) usedPositions[i] = -1;
    int lowVal;
    letterScore tempStruct;
    for(int i = 0; i < length; i++)
    {
        lowVal = 0;
        t->current = t->root;
        for(int j = 0; j < length; j++)
        {
            memcpy(&tempStruct, t->current->key, sizeof(letterScore));
            if(tempStruct.frequency > lowVal && !inArray(usedPositions, j, length))
            {
                lowVal = tempStruct.frequency;
                lowestNode = t->current;
                usedPositions[i] = j;
            }
            t->current = t->current->next;
        }
        node* nNode = malloc(sizeof(node));
        memcpy(nNode, lowestNode, sizeof(node));
        if(i == 0)
        {
            sortedTree->root = malloc(sizeof(node));
            memcpy(sortedTree->root, nNode, sizeof(letterScore));
            sortedTree->current = sortedTree->root;
            sortedTree->current->next = NULL;
            endTree(sortedTree);
            sortedTree->current->next = malloc(sizeof(node));
            memcpy(sortedTree->current->next, nNode, sizeof(letterScore));
            sortedTree->current->next->next = NULL;
        }
        else
        {
            endTree(sortedTree);
            sortedTree->current->next = malloc(sizeof(node));
            memcpy(sortedTree->current->next, nNode, sizeof(letterScore));
            sortedTree->current->next->next = NULL;
        }
        sortedTree->current->key = malloc(sizeof(letterScore));
        memcpy(sortedTree->current->key, nNode->key, sizeof(letterScore));
        sortedTree->current->right = nNode->right;
        sortedTree->current->left =nNode->left;
        free(nNode);
    }
    sortedTree->current = sortedTree->root;
    for(int i = 1; i < length; i++)
    {
        sortedTree->current =sortedTree->current->next;
    }
    sortedTree->current->next =NULL;
    return sortedTree;

}

tree* huffmanAlgorithm(tree* huffmanTree)
{
    int Initlength = treeLength(huffmanTree);
    for(int i = 1; i < Initlength; i++)
    {
        int length = treeLength(huffmanTree);
        huffmanTree = insertionSort(huffmanTree);
        huffmanTree->current = huffmanTree->root;
        if(length > 3)
        {
            for(int y = 0; y < length-3; y++)
            {
                huffmanTree->current = huffmanTree->current->next;
            }
            letterScore tempStruct, tempStruct2;
            memcpy(&tempStruct, huffmanTree->current->next->key, sizeof(letterScore));
            memcpy(&tempStruct2, huffmanTree->current->next->next->key, sizeof(letterScore));
            int newFreq = tempStruct.frequency + tempStruct2.frequency;
            letterScore* tempStructP;
            tempStructP = newStruct('*', newFreq);
            node* nNode = newNode(tempStructP, sizeof(letterScore));
            nNode->right = huffmanTree->current->next;
            nNode->left = huffmanTree->current->next->next;
            //nNode->right->next = nNode;
            //nNode->left->next = nNode;
            huffmanTree->current->next = nNode;
        }
        else if(length == 2)
        {
            letterScore tempStruct, tempStruct2;
            memcpy(&tempStruct, huffmanTree->root->key, sizeof(letterScore));
            memcpy(&tempStruct2, huffmanTree->root->next->key, sizeof(letterScore));

            int newFreq = tempStruct.frequency + tempStruct2.frequency;
            letterScore* tempStructP;
            tempStructP = newStruct('*', newFreq);
            node* nNode = newNode(tempStructP, sizeof(letterScore));
            nNode->left = huffmanTree->root->next;
            nNode->right = huffmanTree->root;
            //nNode->right->next = nNode;
            //nNode->left->next = nNode;
            huffmanTree->root = nNode;
            huffmanTree->current = huffmanTree->root;

        }
        else if(length == 3)
        {
            letterScore tempStruct, tempStruct2;
            memcpy(&tempStruct, huffmanTree->root->next->key, sizeof(letterScore));
            memcpy(&tempStruct2, huffmanTree->root->next->next->key, sizeof(letterScore));

            int newFreq = tempStruct.frequency + tempStruct2.frequency;
            letterScore* tempStructP;
            tempStructP = newStruct('*', newFreq);
            node* nNode = newNode(tempStructP, sizeof(letterScore));
            nNode->right = huffmanTree->root->next;
            nNode->left = huffmanTree->root->next->next;
           //nNode->right->next = nNode;
            //nNode->left->next = nNode;
            huffmanTree->root->next= nNode;
            huffmanTree->current = huffmanTree->root;

        }
    }
    return huffmanTree;
}

int main(int argc, char *argv[argc])
{
    tree* huffmanTree = newTree();
    char *text = "aaaaaaaaaaaaaaaaaaaaaaaabbbbbbbbbbbbcccccccccceeeeeeeedddddddd";
    getFrequencies(huffmanTree, text);
    huffmanTree = insertionSort(huffmanTree);
    huffmanTree = huffmanAlgorithm(huffmanTree);
    printTree(huffmanTree->root, 4);
    return 0;
}
