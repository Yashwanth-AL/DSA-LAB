#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <math.h>

#define MAX_SIZE 100

typedef struct {
    int top;
    char arr[MAX_SIZE];
} Stack;

void initialize(Stack *s) {
    s->top = -1;
}

int isEmpty(Stack *s) {
    return s->top == -1;
}

int isFull(Stack *s) {
    return s->top == MAX_SIZE - 1;
}

void push(Stack *s, char c) {
    if (isFull(s)) {
        printf("Stack overflow\n");
        exit(1);
    }
    s->arr[++(s->top)] = c;
}

char pop(Stack *s) {
    if (isEmpty(s)) {
        printf("Stack underflow\n");
        exit(1);
    }
    return s->arr[(s->top)--];
}

char peek(Stack *s) {
    if (isEmpty(s)) {
        printf("Stack is empty\n");
        exit(1);
    }
    return s->arr[s->top];
}

int precedence(char op) {
    if (op == '^') {
        return 3;
    } else if (op == '*' || op == '/' || op == '%') {
        return 2;
    } else if (op == '+' || op == '-') {
        return 1;
    } else {
        return -1;
    }
}

void infixToPrefix(char *infix, char *prefix) {
    Stack stack;
    initialize(&stack);
    int i, j = 0;
    int length = strlen(infix);
    
    // Reverse the infix expression and convert it into nearly postfix
    for (i = length - 1; i >= 0; i--) {
        if (isalnum(infix[i])) {
            prefix[j++] = infix[i];
        } else if (infix[i] == ')') {
            push(&stack, infix[i]);
        } else if (infix[i] == '(') {
            while (!isEmpty(&stack) && peek(&stack) != ')') {
                prefix[j++] = pop(&stack);
            }
            if (!isEmpty(&stack) && peek(&stack) == ')') {
                pop(&stack); // Discard the ')'
            } else {
                printf("Invalid expression\n");
                exit(1);
            }
        } else { // Operator
            while (!isEmpty(&stack) && 
                    (precedence(infix[i]) < precedence(peek(&stack)) || 
                    peek(&stack) == '^' && infix[i] == '^')) {
                prefix[j++] = pop(&stack);
            }
            push(&stack, infix[i]);
        }
    }
    // Pop remaining operators from the stack
    while (!isEmpty(&stack)) {
        if (peek(&stack) == '(' || peek(&stack) == ')') {
            printf("Invalid expression\n");
            exit(1);
        }
        prefix[j++] = pop(&stack);
    }
    prefix[j] = '\0';
    
    // Reverse the prefix expression to get the correct result
    length = strlen(prefix);
    for (i = 0; i < length / 2; i++) {
        char temp = prefix[i];
        prefix[i] = prefix[length - i - 1];
        prefix[length - i - 1] = temp;
    }
}

int evaluatePrefix(char *prefix) {
    Stack stack;
    initialize(&stack);
    int i, result;
    int length = strlen(prefix);
    
    // Evaluate prefix expression from right to left
    for (i = length - 1; i >= 0; i--) {
        if (isdigit(prefix[i])) {
            push(&stack, prefix[i] - '0');
        } else {
            int operand1 = pop(&stack);
            int operand2 = pop(&stack);
            switch(prefix[i]) {
                case '+':
                    result = operand1 + operand2;
                    break;
                case '-':
                    result = operand1 - operand2;
                    break;
                case '*':
                    result = operand1 * operand2;
                    break;
                case '/':
                    result = operand1 / operand2;
                    break;
                case '%':
                    result = operand1 % operand2;
                    break;
                case '^':
                    result = pow(operand1, operand2);
                    break;
                default:
                    printf("Invalid operator\n");
                    exit(1);
            }
            push(&stack, result);
        }
    }
    return pop(&stack);
}


int main() {
    char infix[MAX_SIZE], prefix[MAX_SIZE];
    int choice, result;
    do {
        printf("\nMenu:\n");
        printf("1. Convert infix to prefix\n");
        printf("2. Evaluate prefix expression\n");
        printf("3. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        switch(choice) {
            case 1:
                printf("Enter the infix expression: ");
                scanf("%s", infix);
                infixToPrefix(infix, prefix);
                printf("Prefix expression: %s\n", prefix);
                break;
            case 2:
                printf("Enter the prefix expression: ");
                scanf("%s", prefix);
                result = evaluatePrefix(prefix);
                printf("Result of evaluation: %d\n", result);
                break;
            case 3:
                printf("Exiting...\n");
                break;
            default:
                printf("Invalid choice\n");
        }
    } while (choice != 3);
    return 0;
}
