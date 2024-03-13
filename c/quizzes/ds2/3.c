#include <stdio.h>

#define MAX_SIZE 10
struct Stack * SortStack(struct Stack * myStack,struct Stack * SortedStack);


struct Stack {
    int data[MAX_SIZE];
    int top;
};
 
void initialize(struct Stack* stack) {
    stack->top = -1;
}

 
int isempty(struct Stack* stack) {
    return stack->top == -1;
}

 
void push(struct Stack* stack, int value) {
    if (stack->top < MAX_SIZE - 1) {
        stack->data[++stack->top] = value;
        printf("Pushed %d onto the stack.\n", value);
    } else {
        printf("Error: Stack overflow. Cannot push %d onto the stack.\n", value);
    }
}

 
int pop(struct Stack* stack) {
    if (!isempty(stack)) {
        printf("Popped %d from the stack.\n", stack->data[stack->top]);
        return stack->data[stack->top--];
    } else {
        printf("Error: Stack underflow. Cannot pop from an empty stack.\n");
        return -1; 
    }
}

int peek(struct Stack* stack) {
    if (!isempty(stack)) {
        printf("Peeked at the top of the stack: %d\n", stack->data[stack->top]);
        return stack->data[stack->top];
    } else {
        printf("Error: Cannot peek from an empty stack.\n");
        return -1;  
    }
}

void insert(struct Stack* stack , int value )
{
    int temp = 0;
    if(isempty(stack) || peek(stack)  < value)
    {
        push(stack, value);
        return;
    }
    temp = peek(stack);
    pop(stack);
    insert(stack, value);
    push(stack, temp);

    return;
}

int main() {
 
    struct Stack myStack;
    struct Stack SortedStack;
    int i = 0;
    initialize(&myStack);
    initialize(&SortedStack);
 
    insert(&myStack, 5);
    insert(&myStack, 10);
    insert(&myStack, -3);
    insert(&myStack, 7);
    insert(&myStack, 1);
    insert(&myStack, -8);
    insert(&myStack, 12);
    insert(&myStack, 0);
    insert(&myStack, -5);
    insert(&myStack, 9);
    
     printf("\n\nSORTEDl \n");
    for(i = 0 ; i < 10 ; ++i)
    {
        pop(&myStack);
    }

    printf("\n\n");

    for(i = 0 ; i < 10 ; ++i)
    {
        pop(&SortedStack);
    }
    return 0;
}


struct Stack * SortStack(struct Stack * myStack,struct Stack * SortedStack)
{
    
    int temp = 0; 

    while (isempty(myStack) != -1)
    {
        temp = peek(myStack);
        pop(myStack);

        while(!isempty(SortedStack) && peek(SortedStack) > temp)
        {
            printf("to hre \n");
            push(myStack, peek(SortedStack));
            pop(SortedStack);
        }
        push(SortedStack, temp);
    }
    return SortedStack;
}