#include <stdio.h>
#include <stdlib.h>

// Structure for a node in BST
struct TNode {
    int data;
    struct TNode *left;
    struct TNode *right;
};

// Structure for a node in the queue used for level order traversal
struct QNode {
    struct TNode* node;
    struct QNode* link;
};

// Structure for the queue used for level order traversal
struct Queue {
    struct QNode *front, *rear;
};

// Function to create a new Tree Node
struct TNode* createNode(int data) {
    struct TNode* newNode = (struct TNode*)malloc(sizeof(struct TNode));
    newNode->data = data;
    newNode->left = NULL;
    newNode->right = NULL;
    return newNode;
}

// Function to insert a node into BST
struct TNode* insert(struct TNode* root, int data) {
    if (root == NULL) {
        return createNode(data);
    }
    if (data < root->data) {
        root->left = insert(root->left, data);
    } else if (data > root->data) {
        root->right = insert(root->right, data);
    }
    return root;
}

// Function for inorder traversal
void inorder(struct TNode* root) {
    if (root != NULL) {
        inorder(root->left);
        printf("%d ", root->data);
        inorder(root->right);
    }
}

// Function for preorder traversal
void preorder(struct TNode* root) {
    if (root != NULL) {
        printf("%d ", root->data);
        preorder(root->left);
        preorder(root->right);
    }
}

// Function for postorder traversal
void postorder(struct TNode* root) {
    if (root != NULL) {
        postorder(root->left);
        postorder(root->right);
        printf("%d ", root->data);
    }
}

// Function to create an empty queue
struct Queue* createQueue() {
    struct Queue* queue = (struct Queue*)malloc(sizeof(struct Queue));
    queue->front = queue->rear = NULL;
    return queue;
}

// Function to check if the queue is empty
int isEmpty(struct Queue* queue) {
    return queue->front == NULL;
}
    
// Function to enqueue a tree node
void enqueue(struct Queue* queue, struct TNode* treeNode) {
    struct QNode* newNode = (struct QNode*)malloc(sizeof(struct QNode));
    newNode->node = treeNode;
    newNode->link = NULL;
    if (queue->rear == NULL) {
        queue->front = queue->rear = newNode;
        return;
    }
    queue->rear->link = newNode;
    queue->rear = newNode;
}

// Function to dequeue a tree node
struct TNode* dequeue(struct Queue* queue) {
    if (queue->front == NULL)
        return NULL;
    struct QNode* temp = queue->front;
    struct TNode* treeNode = temp->node;
    queue->front = queue->front->link;
    if (queue->front == NULL)
        queue->rear = NULL;
    free(temp);
    return treeNode;
}

// Function for level order traversal
void levelOrder(struct TNode* root) {
    if (root == NULL)
        return;
    
    struct Queue* queue = createQueue();
    enqueue(queue, root);

    while (!isEmpty(queue)) {
        struct TNode* tempNode = dequeue(queue);
        printf("%d ", tempNode->data);

        if (tempNode->left != NULL)
            enqueue(queue, tempNode->left);
        if (tempNode->right != NULL)
            enqueue(queue, tempNode->right);
    }
    printf("\n");
}

// Function to display menu
void displayMenu() {
    printf("\nBinary Search Tree Operations:");
    printf("\n1. Insert Element");
    printf("\n2. Inorder Traversal");
    printf("\n3. Preorder Traversal");
    printf("\n4. Postorder Traversal");
    printf("\n5. Level Order Traversal");
    printf("\n6. Exit");
    printf("\nEnter your choice: ");
}

int main() {
    struct TNode* root = NULL;
    int choice, data;

    do {
        displayMenu();
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Enter data to insert: ");
                scanf("%d", &data);
                root = insert(root, data);
                break;
            case 2:
                printf("Inorder Traversal: ");
                inorder(root);
                printf("\n");
                break;
            case 3:
                printf("Preorder Traversal: ");
                preorder(root);
                printf("\n");
                break;
            case 4:
                printf("Postorder Traversal: ");
                postorder(root);
                printf("\n");
                break;
            case 5:
                printf("Level Order Traversal: ");
                levelOrder(root);
                break;
            case 6:
                printf("Exiting...\n");
                break;
            default:
                printf("Invalid choice!\n");
        }
    } while (choice != 6);

    return 0;
}
