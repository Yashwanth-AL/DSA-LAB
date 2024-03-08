#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
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

void infixToPostfix(char *infix, char *postfix) {
    Stack *stack = (Stack *)malloc(sizeof(Stack));
    initialize(stack);
    int i, j = 0;
    for (i = 0; infix[i] != '\0'; i++) {
        if (isalnum(infix[i])) {
            postfix[j++] = infix[i];
        } else if (infix[i] == '(') {
            push(stack, infix[i]);
        } else if (infix[i] == ')') {
            while (!isEmpty(stack) && peek(stack) != '(') {
                postfix[j++] = pop(stack);
            }
            if (!isEmpty(stack) && peek(stack) == '(') {
                pop(stack); // Discard the '('
            } else {
                printf("Invalid expression\n");
                exit(1);
            }
        } else { // Operator
            while (!isEmpty(stack) && precedence(infix[i]) <= precedence(peek(stack)) && infix[i] != '^') {
                postfix[j++] = pop(stack);
            }
            push(stack, infix[i]);
        }
    } 
    while (!isEmpty(stack)) {
        if (peek(stack) == '(' || peek(stack) == ')') {
            printf("Invalid expression\n");
            exit(1);
        }
        postfix[j++] = pop(stack);
    }
    postfix[j] = '\0';
}


int evaluatePostfix(char *postfix) {
    Stack *stack = (Stack *)malloc(sizeof(Stack));
    initialize(stack);
    int i, operand1, operand2, result;
    for (i = 0; postfix[i] != '\0'; i++) {
        if (isdigit(postfix[i])) {
            push(stack, postfix[i] - '0');
        } else {
            operand2 = pop(stack);
            operand1 = pop(stack);
            switch(postfix[i]) {
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
                    result = pow(operand1,operand2);
                    break;
                default:
                    printf("Invalid operator\n");
                    exit(1);
            }
            push(stack, result);
        }
    }
    return pop(stack);
}

int main() {
    char infix[MAX_SIZE], postfix[MAX_SIZE];
    int choice, result;
    do {
        printf("\nMenu:\n");
        printf("1. Convert infix to postfix\n");
        printf("2. Evaluate postfix expression\n");
        printf("3. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        switch(choice) {
            case 1:
                printf("Enter the infix expression: ");
                scanf("%s", infix);
                infixToPostfix(infix, postfix);
                printf("Postfix expression: %s\n", postfix);
                break;
            case 2:
                printf("Enter the postfix expression: ");
                scanf("%s", postfix);
                result = evaluatePostfix(postfix);
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