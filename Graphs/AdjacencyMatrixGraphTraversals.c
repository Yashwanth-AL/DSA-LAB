//Develop a menu driven program to implement Graph traversals techniques

#include <stdio.h>

int visited[20] = {0}; 

void createGraph(int arr[][20], int num) {
    printf("Enter the adjacency matrix:\n");
    for (int i = 0; i < num; i++) {
        for (int j = 0; j < num; j++) {
            scanf("%d", &arr[i][j]);
        }
    }
}

void displayGraph(int arr[][20], int num) {
    printf("Adjacency Matrix:\n");
    for (int i = 0; i < num; i++) {
        for (int j = 0; j < num; j++) {
            printf("%d ", arr[i][j]);
        }
        printf("\n");
    }
}

void BFS(int arr[][20], int start, int num) {
    printf("BFS Traversal: ");
    printf("%d ", start); 
    visited[start] = 1;
    int q[20];
    int front = 0, rear = 0;
    q[rear] = start;

    while(front <= rear) {
        int r = q[front++];
        for(int c = 0; c < num; c++) {
            if(arr[r][c] == 1 && visited[c] == 0) {
                printf("%d ", c);
                visited[c] = 1;
                q[++rear] = c;
            }
        }
    }
    printf("\n");
} 

void DFS(int arr[][20], int start, int num) {
    if(visited[start] == 0) {
        printf("%d ", start);
        visited[start] = 1;
    }
    for(int j = 0; j < num; j++) {
        if(arr[start][j] == 1 && visited[j] == 0) {
            DFS(arr, j, num);
        }
    }
}

int main() {
    int arr[20][20]; 
    int num, choice, startVertex;

    printf("Enter the number of vertices: ");
    scanf("%d", &num);

    createGraph(arr, num);
    

    printf("\nMenu:\n");
    printf("1. Display Adjacency Matrix\n");
    printf("2. BFS Traversal\n");
    printf("3. DFS Traversal\n");
    printf("4. Exit\n");

    while (1) {
        printf("\nEnter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                displayGraph(arr, num);
                break;
            case 2:
                printf("Enter the starting vertex: ");
                scanf("%d", &startVertex);
                for (int i = 0; i < num; i++)
                    visited[i] = 0;
                BFS(arr, startVertex, num);
                break;
            case 3:
                printf("Enter the starting vertex: ");
                scanf("%d", &startVertex);
                for (int i = 0; i < num; i++)
                    visited[i] = 0;
                printf("DFS Traversal: ");
                DFS(arr, startVertex, num);
                printf("\n");
                break;
            case 4:
                printf("Exiting the program\n");
                return 0;
            default:
                printf("Invalid choice! Please enter again.\n");
        }
    }

    return 0;
}
