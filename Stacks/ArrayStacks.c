#include <stdio.h>
#include <stdlib.h>

#define MAX_SIZE 5

typedef struct{
    int top;
    int array[MAX_SIZE];
}Stack;

Stack* createStack() {
    Stack* stack = (Stack*)malloc(sizeof(Stack));
    if (!stack) {
        printf("Memory allocation failed for stack.\n");
        exit(1);
    }
    stack->top = -1;
    return stack;
}

int isEmpty(Stack* stack) {
    return stack->top == -1;
}

int isFull(Stack* stack) {
    return stack->top == MAX_SIZE - 1;
}

void push(Stack* stack, int value) {
    if (isFull(stack)) {
        printf("Stack overflow! Cannot push into a full stack\n");
        return;
    }
    stack->array[++stack->top] = value;
    printf("%d pushed to the stack\n", value);
}

int pop(Stack* stack) {
    if (isEmpty(stack)) {
        printf("Stack underflow! Cannot pop from an empty stack\n");
        return -1;
    }
    return stack->array[stack->top--];
}

int peek(Stack* stack){
    if (isEmpty(stack)) {
        printf("Stack is empty\n");
        return -1;
    }
    return stack->array[stack->top];
}

void display(Stack* stack) {
    if (isEmpty(stack)) {
        printf("Stack is empty\n");
        return;
    }
    printf("Stack elements: ");
    for (int i = 0; i <= stack->top; i++) {
        printf("%d ", stack->array[i]);
    }
    printf("\n");
}

int main() {
    Stack* stack = createStack();

    int choice, value;

    do {
        
        printf("\nStack Operations Menu\n");
        printf("1. Push\n");
        printf("2. Pop\n");
        printf("3. Peek\n");
        printf("4. Display\n");
        printf("5. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Enter the value to push: ");
                scanf("%d", &value);
                push(stack, value);
                break;
            case 2:
                value = pop(stack);
                if(value != -1)
                    printf("Popped element: %d\n", value);
                break;
            case 3:
                value = peek(stack);
                if(value != -1){
                    printf("Peeked element is %d\n", value);
                }
                break;    
            case 4:
                display(stack);
                break;
            case 5:
                printf("Exiting program...\n");
                break;
            default:
                printf("Invalid choice! Please enter a valid option.\n");
        }
    } while (choice != 5);

    return 0;
}
