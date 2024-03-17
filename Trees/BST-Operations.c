#include <stdio.h>
#include <stdlib.h>

struct Node {
    int data;
    struct Node *left;
    struct Node *right;
};

struct Node *createNode(int x);
void display(struct Node *root, int level);
struct Node *search(struct Node *root, int x);
struct Node *insertNode(struct Node *root, int x);
struct Node *deleteNode(struct Node *root, int x);
struct Node *Min(struct Node *root);
struct Node *Max(struct Node *root);
int height(struct Node *root);
int countNodes(struct Node *root);
int countLeafNodes(struct Node *root);
void inorder(struct Node *root);
void preorder(struct Node *root);
void postorder(struct Node *root);
void levelOrder(struct Node *root);

struct Node *createNode(int data) {
    struct Node *newNode = (struct Node *)malloc(sizeof(struct Node));
    newNode->data = data;
    newNode->left = NULL;
    newNode->right = NULL;
    return newNode;
}

struct Node *insertNode(struct Node *root, int data) {
    if (root == NULL)
        return createNode(data);
    else if (data < root->data)
        root->left = insertNode(root->left, data);
    else if (data > root->data)
        root->right = insertNode(root->right, data);
    else
        printf("%d already present in tree\n", data);
    return root;
}

struct Node *search(struct Node *root, int data) {
    if (root == NULL || root->data == data)
        return root;
    if (data < root->data)
        return search(root->left, data);
	else
    	return search(root->right, data);
}

struct Node *deleteNode(struct Node *root, int x) {
    if (root == NULL) {
        printf("%d not found\n", x);
        return root;
    }
    struct Node *parent = NULL;
    struct Node *current = root;

    while (current != NULL && current->data != x) {
        parent = current;
        if (x < current->data)
            current = current->left;
        else
            current = current->right;
    }

    if (current == NULL) {
        printf("%d not found\n", x);
        return root;
    }

    if (current->left != NULL && current->right != NULL) {
        struct Node *parentSuccessor = current;
        struct Node *successor = current->right;

        while (successor->left != NULL) {
            parentSuccessor = successor;
            successor = successor->left;
        }

        current->data = successor->data;
        current = successor;
        parent = parentSuccessor;
    }

    struct Node *child;
    if (current->left != NULL)
        child = current->left;
    else
        child = current->right;

    if (parent == NULL)
        root = child;
    else if (current == parent->left)
        parent->left = child;
    else
        parent->right = child;

    free(current);
    return root;
}


struct Node *Min(struct Node *root) {
    if (root == NULL || root->left == NULL)
        return root;
    return Min(root->left);
}

struct Node *Max(struct Node *root) {
    if (root == NULL || root->right == NULL)
        return root;
    return Max(root->right);
}

int height(struct Node *root) {
    if (root == NULL)
        return 0;
    int leftHeight = height(root->left);
    int rightHeight = height(root->right);
    return 1 + (leftHeight > rightHeight ? leftHeight : rightHeight);
}

int countNodes(struct Node *root) {
    if (root == NULL)
        return 0;
    return 1 + countNodes(root->left) + countNodes(root->right);
}

int countLeafNodes(struct Node *root) {
    if (root == NULL)
        return 0;
    if (root->left == NULL && root->right == NULL)
        return 1;
    return countLeafNodes(root->left) + countLeafNodes(root->right);
}

void inorder(struct Node *root) {
    if (root != NULL) {
        inorder(root->left);
        printf("%d ", root->data);
        inorder(root->right);
    }
}

// Function to perform pre-order traversal of the tree
void preorder(struct Node *root) {
    if (root != NULL) {
        printf("%d ", root->data);
        preorder(root->left);
        preorder(root->right);
    }
}

void postorder(struct Node *root) {
    if (root != NULL){
        postorder(root->left);
        postorder(root->right);
        printf("%d ", root->data);
    }
}

void levelOrder(struct Node *root) {
    if (root == NULL) {
        return;
    }
    struct Node *queue[100];
    int front = 0, rear = -1;
    queue[++rear] = root;

    while (front <= rear) {
        struct Node *current = queue[front++];
        printf("%d ", current->data);

        if (current->left != NULL) {
            queue[++rear] = current->left;
        }
        if (current->right != NULL) {
            queue[++rear] = current->right;
        }
    }
}

void display(struct Node *root, int level) {
    if (root == NULL)
        return;

    display(root->right, level + 1);
    printf("\n");

    for (int i = 0; i < level; i++)
        printf("    ");
    printf("%d", root->data);

    display(root->left, level + 1);
}

int main() {
    struct Node *root = NULL;
    int choice, x;
    
    do {
        printf("\n\n1. Insert a new Node\n");
        printf("2. Display Tree\n");
        printf("3. Search for a Node\n");
        printf("4. Delete a Node\n");
        printf("5. Height of tree\n");
        printf("6. Find Minimum key\n");
        printf("7. Find Maximum key\n");
        printf("8. Count Nodes\n");
        printf("9. Count Leaf Nodes\n");
        printf("10. In-order Traversal\n");
        printf("11. Pre-order Traversal\n");
        printf("12. Post-order Traversal\n");
        printf("13. Level-order Traversal\n");
        printf("14. Quit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Enter value to insert: ");
                scanf("%d", &x);
                root = insertNode(root, x);
                break;
            case 2:
                printf("\nTree:\n");
                display(root, 0);
                break;
            case 3:
                printf("Enter value to search: ");
                scanf("%d", &x);
                if (search(root, x))
                    printf("%d found in the tree.\n", x);
                else
                    printf("%d not found in the tree.\n", x);
                break;
            case 4:
                printf("Enter value to delete: ");
                scanf("%d", &x);
                root = deleteNode(root, x);
                break;
            case 5:
                printf("Height of the tree is: %d\n", height(root));
                break;
            case 6:
                printf("Minimum key in the tree: %d\n", Min(root)->data);
                break;
            case 7:
                printf("Maximum key in the tree: %d\n", Max(root)->data);
                break;
            case 8:
                printf("Number of nodes in the tree: %d\n", countNodes(root));
                break;
            case 9:
                printf("Number of leaf nodes in the tree: %d\n", countLeafNodes(root));
                break;
            case 10:
                printf("In-order traversal: ");
                inorder(root);
                printf("\n");
                break;
            case 11:
                printf("Pre-order traversal: ");
                preorder(root);
                printf("\n");
                break;
            case 12:
                printf("Post-order traversal: ");
                postorder(root);
                printf("\n");
                break;
            case 13:
                printf("Level-order traversal: ");
                levelOrder(root);
                printf("\n");
                break;
            case 14:
                printf("Exiting...\n");
                break;
            default:
                printf("Invalid choice. Please try again.\n");
        }
    } while (choice != 14);

    return 0;
}
