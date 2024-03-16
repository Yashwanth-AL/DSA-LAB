//Develop a menu driven program to implement binary search tree and traversals techniques

#include <stdio.h>
#include <stdlib.h>

// Define a structure for tree nodes
struct TreeNode {
    int data;
    struct TreeNode *left;
    struct TreeNode *right;
};

// Function to create a new tree node
struct TreeNode* createNode(int value) {
    struct TreeNode* newNode = (struct TreeNode*)malloc(sizeof(struct TreeNode));
    newNode->data = value;
    newNode->left = NULL;
    newNode->right = NULL;
    return newNode;
}

// Function to insert a node into BST
struct TreeNode* insert(struct TreeNode* root, int data) {
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

void inorder(struct TreeNode* root) {
    if (root != NULL) {
        inorder(root->left);
        printf("%d ", root->data);
        inorder(root->right);
    }
}

void preorder(struct TreeNode* root) {
    if (root != NULL) {
        printf("%d ", root->data);
        preorder(root->left);
        preorder(root->right);
    }
}

void postorder(struct TreeNode* root) {
    if (root != NULL){
        postorder(root->left);
        postorder(root->right);
        printf("%d ", root->data);
    }
}

void levelOrder(struct TreeNode* root) {
    if (root == NULL) {
        return;
    }
    struct TreeNode* queue[100];
    int front = 0, rear = -1;
    queue[++rear] = root;

    while (front <= rear) {
        struct TreeNode* current = queue[front++];
        printf("%d ", current->data);

        if (current->left != NULL) {
            queue[++rear] = current->left;
        }
        if (current->right != NULL) {
            queue[++rear] = current->right;
        }
    }
}

// Function to display menu
void displayMenu() {
    printf("\n\nBinary Search Tree Operations:");
    printf("\n1. Insert Element");
    printf("\n2. Inorder Traversal");
    printf("\n3. Preorder Traversal");
    printf("\n4. Postorder Traversal");
    printf("\n5. Level Order Traversal");
    printf("\n6. Exit\n");
    printf("\nEnter your choice: ");
}

int main() {
    struct TreeNode* root = NULL;
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
                break;
            case 3:
                printf("Preorder Traversal: ");
                preorder(root);
                break;
            case 4:
                printf("Postorder Traversal: ");
                postorder(root);
                break;
            case 5:
                printf("Level-order Traversal: ");
                levelOrder(root);
                break;
            case 6:
                printf("\nExiting program...");
                break;
            default:
                printf("\nInvalid choice! Please enter a valid option.\n");
        }
    } while (choice != 6);

    return 0;
}
