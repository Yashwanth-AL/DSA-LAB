#include <stdio.h>
#include <stdlib.h>

#define MAX_NODES 100

struct Node {
    int data;
    struct Node* next;
};

struct Graph {
    int numNodes;
    struct Node* adjList[MAX_NODES];
};

// Function to create a new node
struct Node* createNode(int data) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode->data = data;
    newNode->next = NULL;
    return newNode;
}

// Function to add an edge to the graph
void addEdge(struct Graph* graph, int src, int dest) {
    struct Node* newNode = createNode(dest);
    newNode->next = graph->adjList[src];
    graph->adjList[src] = newNode;

    // For undirected graph, add an edge from dest to src as well
    newNode = createNode(src);
    newNode->next = graph->adjList[dest];
    graph->adjList[dest] = newNode;
}

// Function to perform Depth-First Search traversal
void DFS(struct Graph* graph, int vertex, int visited[]) {
    visited[vertex] = 1;
    printf("%d ", vertex);

    struct Node* temp = graph->adjList[vertex];
    while (temp != NULL) {
        int adjVertex = temp->data;
        if (!visited[adjVertex]) {
            DFS(graph, adjVertex, visited);
        }
        temp = temp->next;
    }
}

// Function to perform Breadth-First Search traversal
void BFS(struct Graph* graph, int start) {
    int visited[MAX_NODES] = {0};
    int queue[MAX_NODES];
    int front = -1, rear = -1;

    visited[start] = 1;
    queue[++rear] = start;

    while (front != rear) {
        int vertex = queue[++front];
        printf("%d ", vertex);

        struct Node* temp = graph->adjList[vertex];
        while (temp != NULL) {
            int adjVertex = temp->data;
            if (!visited[adjVertex]) {
                visited[adjVertex] = 1;
                queue[++rear] = adjVertex;
            }
            temp = temp->next;
        }
    }
}

// Function to initialize the graph with NULL adjacency lists
void initializeGraph(struct Graph* graph) {
    graph->numNodes = 0;
    for (int i = 0; i < MAX_NODES; i++) {
        graph->adjList[i] = NULL;
    }
}

// Function to display menu and get user choice
int getMenuChoice() {
    int choice;
    printf("\nGraph Traversal Menu\n");
    printf("1. Add Edge\n");
    printf("2. Depth-First Search (DFS)\n");
    printf("3. Breadth-First Search (BFS)\n");
    printf("4. Exit\n");
    printf("Enter your choice: ");
    scanf("%d", &choice);
    return choice;
}

int main() {
    struct Graph graph;
    initializeGraph(&graph);

    int choice, src, dest;
    do {
        choice = getMenuChoice();
        switch (choice) {
            case 1:
                printf("Enter source node: ");
                scanf("%d", &src);
                printf("Enter destination node: ");
                scanf("%d", &dest);
                addEdge(&graph, src, dest);
                if (src > graph.numNodes) graph.numNodes = src + 1;
                if (dest > graph.numNodes) graph.numNodes = dest + 1;
                printf("Edge added between %d and %d\n", src, dest);
                break;
            case 2:
                printf("Enter starting node for DFS: ");
                scanf("%d", &src);
                printf("DFS Traversal: ");
                DFS(&graph, src, (int*)calloc(graph.numNodes, sizeof(int)));
                printf("\n");
                break;
            case 3:
                printf("Enter starting node for BFS: ");
                scanf("%d", &src);
                printf("BFS Traversal: ");
                BFS(&graph, src);
                printf("\n");
                break;
            case 4:
                printf("Exiting...\n");
                break;
            default:
                printf("Invalid choice! Please try again.\n");
        }
    } while (choice != 4);

    return 0;
}
