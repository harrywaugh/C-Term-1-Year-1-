#include "stack.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>


bool bElem(char c, char *chs)
{
    for(int i = 0; i < strlen(chs); i++)
    {
        if(chs[i]==c)
        {
            return true;
        }
    }
    return false;
}

void pushResult(stack *currentStack, char operation)
{
    item operand2 = pop(currentStack);
    item operand1 = pop(currentStack);
    if(operation == '+')
    {
        push(currentStack, operand1+operand2);
    }
    else if(operation == '/')
    {
        push(currentStack, operand1/operand2);
    }
    else if(operation == '*')
    {
        push(currentStack, operand1*operand2);
    }
    else if(operation == '-')
    {
        push(currentStack, operand1-operand2);
    }
}

void loadStack(int argc, char *argv[argc], stack *currentStack)
{
    for (int i = 1; i < argc; i++)
    {
        if(bElem(argv[i][0], "+-*/"))
        {
            pushResult(currentStack, argv[i][0]);
        }
        else
        {
            push(currentStack, atoi(argv[i]));
        }
    }
}

int main(int argc, char *argv[argc])
{
    setbuf(stdout, NULL);
    stack *currentStack = create();
    loadStack(argc, argv, currentStack);
    printf("%f\n", top(currentStack));
    printf("Arguments: %d", argc);
    return 0;
}
