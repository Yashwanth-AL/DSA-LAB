#include <stdio.h>
#include <stdlib.h>

struct Node {
    int data;
    struct Node* link;
};

struct Stack {
    struct Node* top;
};

typedef struct Stack Stack;
typedef struct Node Node;

Stack* createStack() {
    Stack* stack = (Stack*)malloc(sizeof(Stack));
    if (stack == NULL) {
        printf("Memory allocation failed for stack.\n");
        exit(1);
    }
    stack->top = NULL;
    return stack;
}

Node* createNode(int data){
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    if (newNode == NULL) {
        printf("Memory allocation failed.\n");
        exit(1);
    }
    newNode->data = data;
    newNode->link = NULL;
    return newNode;
}

int isEmpty(Stack* stack) {
    return stack->top == NULL;
}

void push(Stack* stack, int value) {
    struct Node* newNode = createNode(value);
    newNode->link = stack->top;
    stack->top = newNode;
    printf("%d pushed to the stack\n", value);
}

int pop(Stack* stack) {
    if (isEmpty(stack)) {
        printf("Stack underflow! Cannot pop from an empty stack\n");
        return -1;
    }

    struct Node* temp = stack->top;
    int poppedValue = temp->data;
    stack->top = temp->link;
    free(temp);

    return poppedValue;
}

int peek(Stack* stack){
    return stack->top->data;
}

void display(Stack* stack) {
    if (isEmpty(stack)) {
        printf("Stack is empty\n");
        return;
    }

    printf("Stack elements: ");
    struct Node* current = stack->top;
    while (current != NULL) {
        printf("%d ", current->data);
        current = current->link;
    }
    printf("\n");
}

void freeStack(Stack* stack) {
    while (stack->top != NULL) {
        struct Node* temp = stack->top;
        stack->top = temp->link;
        free(temp);
    }
}

int main() {
    Stack* stack = createStack();

    int choice, value;

    do {
        // Display menu
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
                printf("Peeked element is %d\n", peek(stack));
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

    freeStack(stack);
    return 0;
}