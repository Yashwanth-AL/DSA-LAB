//implementation of Circular Queue using static memory allocation.

#include <stdio.h>
#include <stdlib.h>

#define MAX 10

typedef struct{
    int front, rear;
    int arr[MAX];
} Que;

void initQ(Que *q) {
    q->front = -1;
    q->rear = -1;
}

int isEmpty(Que* q) {
    return (q->front == -1 && q->rear == -1);
}

int isFull(Que* q) {
    return ((q->rear + 1) % MAX == q->front);
}

void enque(Que* q, int value) {
    if (isFull(q)) {
        printf("Queue Overflow!!!\n");
        return;
    }
    if (isEmpty(q)) {
        q->front = 0;
        q->rear = 0;
    } else {
        q->rear = (q->rear + 1) % MAX;
    }
    q->arr[q->rear] = value;
    printf("%d inserted into the Queue\n", value);
}

int deque(Que* q) {
    if (isEmpty(q)) {
        printf("Queue Underflow!!!\n");
        return -1;
    }
    int data = q->arr[q->front];
    if (q->front == q->rear) {
        initQ(q);
    } else {
        q->front = (q->front + 1) % MAX;
    }
    return data;
}

void display(Que* q) {
    if (isEmpty(q)) {
        printf("Queue is empty\n");
        return;
    }
    printf("Queue elements: ");
    int temp = q->front;
    do {
        printf("%d ", q->arr[temp]);
        temp = (temp + 1) % MAX;
    } while (temp != (q->rear + 1) % MAX);
    printf("\n");
}

int main() {
    Que q;
    initQ(&q);
    int choice, data;
    do {
        printf("\nQueue Operations Menu\n");
        printf("1. Enqueue\n");
        printf("2. Dequeue\n");
        printf("3. Display\n");
        printf("4. Exit\n");
        printf("Enter your choice:  ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Enter the data to insert: ");
                scanf("%d", &data);
                enque(&q, data);
                break;
            case 2:
                data = deque(&q);
                if(data != -1)
                    printf("Dequeued element is : %d\n", data);
                break;    
            case 3:
                display(&q);
                break;
            case 4:
                printf("Exiting program...\n");
                break;
            default:
                printf("Invalid choice! Please enter a valid option.\n");
        }
    } while (choice != 4);

    return 0;
}
