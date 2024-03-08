//Priority Queue - Design 1 : Enqueue is normal, search done while dequeue.

#include<stdio.h>
#include<stdlib.h>
#define MAX 10

struct Queue{
    int front, rear;
    int arr[MAX];
};

typedef struct Queue Que;

void initQ(Que *q) {
    q->front = -1; 
    q->rear = -1;
}

int isEmpty(Que* q) {
    return (q->front == -1 && q->rear == -1);
}

int isFull(Que* q) {
    return (q->rear == MAX - 1);
}

void enque(Que* q, int value) {
    if (isFull(q)) {
        printf("Queue Overflow!!!\n");
        return;
    }
    if (isEmpty(q)) {
        q->front = 0;
    }
    q->arr[++q->rear] = value;
    printf("%d inserted into the Queue\n", value);
}

int deque(Que* q){
    if(isEmpty(q)){
        printf("Queue Underflow\n");
        return -1;
    }
    int min = q->arr[q->front];
    int index = 0, flag = 0;
    for(int i = q->front + 1; i <= q->rear; i++){
        if(q->arr[i] < min){
            min = q->arr[i];
            index = i; 
        }
        flag = 1;
    }
    printf("Deleted item is: %d\n", min);
    if (flag == 0){
        q->front =  q->rear = -1;
        return min;
    }
    for(int i = index; i <= q->rear-1; i++){
        q->arr[i] = q->arr[i+1];
    }
    q->rear--;
    return min;
}

void display(Que* q) {
    if (isEmpty(q)) {
        printf("Queue is empty\n");
        return;
    }
    printf("Queue elements: ");
    for (int i = q->front; i <= q->rear; i++) {
        printf("%d ", q->arr[i]);
    }
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
                enque(&q,data);
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
