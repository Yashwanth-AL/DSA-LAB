#include <stdio.h>
#include <stdlib.h>

// Define a structure for tree nodes
struct TreeNode {
    int val;
    struct TreeNode *left;
    struct TreeNode *right;
};

// Function to create a new tree node
struct TreeNode* createNode(int value) {
    struct TreeNode* newNode = (struct TreeNode*)malloc(sizeof(struct TreeNode));
    newNode->val = value;
    newNode->left = NULL;
    newNode->right = NULL;
    return newNode;
}

void inorderTraversal(struct TreeNode* root) {
    if (root == NULL) {
        return;
    }
    inorderTraversal(root->left);
    printf("%d ", root->val);
    inorderTraversal(root->right);
}

void preorderTraversal(struct TreeNode* root) {
    if (root == NULL) {
        return;
    }
    printf("%d ", root->val);
    preorderTraversal(root->left);
    preorderTraversal(root->right);
}

void postorderTraversal(struct TreeNode* root) {
    if (root == NULL) {
        return;
    }
    postorderTraversal(root->left);
    postorderTraversal(root->right);
    printf("%d ", root->val);
}

void levelOrderTraversal(struct TreeNode* root) {
    if (root == NULL) {
        return;
    }
    struct TreeNode* queue[100];
    int front = 0, rear = -1;
    queue[++rear] = root;

    while (front <= rear) {
        struct TreeNode* current = queue[front++];
        printf("%d ", current->val);

        if (current->left != NULL) {
            queue[++rear] = current->left;
        }
        if (current->right != NULL) {
            queue[++rear] = current->right;
        }
    }
}

// Function to build a sample binary tree
struct TreeNode* buildSampleTree() {
    struct TreeNode* root = createNode(1);
    root->left = createNode(2);
    root->right = createNode(3);
    root->left->left = createNode(4);
    root->left->right = createNode(5);
    return root;
}

int main() {
    struct TreeNode* root = NULL;
    int choice;

    do {
        printf("\nBinary Tree Traversal Menu:");
        printf("\n1. Build Sample Tree");
        printf("\n2. Inorder Traversal");
        printf("\n3. Preorder Traversal");
        printf("\n4. Postorder Traversal");
        printf("\n5. Level-order Traversal");
        printf("\n6. Exit");
        printf("\nEnter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                root = buildSampleTree();
                printf("\nSample tree built successfully.");
                break;
            case 2:
                printf("\nInorder Traversal: ");
                inorderTraversal(root);
                break;
            case 3:
                printf("\nPreorder Traversal: ");
                preorderTraversal(root);
                break;
            case 4:
                printf("\nPostorder Traversal: ");
                postorderTraversal(root);
                break;
            case 5:
                printf("\nLevel-order Traversal: ");
                levelOrderTraversal(root);
                break;
            case 6:
                printf("\nExiting program...");
                break;
            default:
                printf("\nInvalid choice! Please enter a valid option.");
        }
    } while (choice != 6);

    return 0;
}
