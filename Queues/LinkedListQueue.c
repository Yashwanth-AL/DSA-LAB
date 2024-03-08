//implementation of Linear Queue using Dynamic memory allocation using linked list.
#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int data;
    struct Node* link;
}Node;

typedef struct {
    Node* front;
    Node* rear;
} Que;

Que *CreateQue() {
    Que* q = (Que *)malloc(sizeof(Que));
    if (!q) {
        printf("Memory allocation failed.\n");
        exit(1);
    }
    q->front = NULL;
    q->rear = NULL;
    return q;
}

Node *createNode(int data){
    Node *new = (Node *)malloc(sizeof(Node));
    if (!new) {
        printf("Memory allocation failed.\n");
        exit(1);
    }
    new->data = data;
    new->link = NULL;
    return new;
}

int isEmpty(Que* q) {
    return (q->front == NULL);
}

void display(Que* q) {
    if (isEmpty(q)) {
        printf("Queue is empty\n");
        return;
    }
    printf("Queue elements: ");
    Node* current = q->front;
    while (current != NULL) {
        printf("%d ", current->data);
        current = current->link;
    }
    printf("\n");
}

void enque(Que* q, int data) {
    Node *newNode = createNode(data);
    if (isEmpty(q)) {
        q->front = newNode;
        q->rear = newNode;
    } else {
        q->rear->link = newNode;
        q->rear = newNode;
    }
    printf("%d inserted into the Queue\n", data);
}

int deque(Que* q) {
    if (isEmpty(q)) {
        printf("Queue Underflow!!!\n");
        return -1;
    }
    int data = q->front->data;
    Node* temp = q->front;
    q->front = temp->link;
    free(temp);
    if (q->front == NULL) {
        q->rear = NULL;
    }
    return data;
}

void freeQueue(Que* q) {
    while (q->front != NULL) {
        Node* temp = q->front;
        q->front = q->front->link;
        free(temp);
    }
    q->rear = NULL;
}

int main() {
    Que *q = CreateQue();
    int choice, data;
    do {
        printf("\nQueue Operations Menu\n");
        printf("1. Enqueue\n");
        printf("2. Dequeue\n");
        printf("3. Display\n");
        printf("4. Exit\n\n");
        printf("Enter your choice:  ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Enter the data to insert: ");
                scanf("%d", &data);
                enque(q, data);
                break;
            case 2:
                data = deque(q);
                if (data != -1)
                    printf("Dequeued element is : %d\n", data);
                break;
            case 3:
                display(q);
                break;
            case 4:
                printf("Exiting program...\n");
                break;
            default:
                printf("Invalid choice! Please enter a valid option.\n");
        }
    } while (choice != 4);

    freeQueue(q);
    return 0;
}
