#include <stdio.h>
#include <stdlib.h>

struct Node {
    int data;
    struct Node *link;
};

struct List {
    struct Node *head;
};

typedef struct Node Node;
typedef struct List List;

Node *createNode(int data) {
    Node *newNode = (Node *)malloc(sizeof(Node));
    newNode->data = data;
    newNode->link = NULL;
    return newNode;
}

void displayList(List *list) {
    Node *current = list->head->link;
    while (current != NULL) {
        printf("%d -> ", current->data);
        current = current->link;
    }
    printf("NULL\n");
}

void freeList(List *list) {
    Node *current = list->head;
    while (current != NULL) {
        Node *temp = current;
        current = current->link;
        free(temp);
    }
    free(list);
}

List *insertAtBeginning(List *list, int data) {
    Node *newNode = createNode(data);
    newNode->link = list->head->link;
    list->head->link = newNode;
    return list;
}

List *insertAtEnd(List *list, int data) {
    Node *newNode = createNode(data);
    if (list->head->link == NULL) {
        list->head->link = newNode;
        return list;
    }
    Node *current = list->head->link;
    while (current->link != NULL) {
        current = current->link;
    }
    current->link = newNode;
    return list;
}

List *insertAtPosition(List *list, int pos, int data) {
    if (pos == 1) {
        list = insertAtBeginning(list, data);
        return list;
    }
    Node *current = list->head->link;
    for (int i = 1; i < pos - 1 && current != NULL; i++) {
        current = current->link;
    }
    if (current == NULL) {
        printf("Invalid position\n");
        return list;
    }
    Node *newNode = createNode(data);
    newNode->link = current->link;
    current->link = newNode;
    return list;
}

List *deleteAtBeginning(List *list) {
    if (list->head->link == NULL) {
        printf("List is empty. Nothing to delete.\n");
        return list;
    }
    Node *temp = list->head->link;
    list->head->link = temp->link;
    free(temp);
    return list;
}

List *deleteAtEnd(List *list) {
    if (list->head->link == NULL) {
        printf("List is empty. Nothing to delete.\n");
        return list;
    }
    Node *current = list->head->link;
    Node *previous = NULL;
    while (current->link != NULL) {
        previous = current;
        current = current->link;
    }
    if (previous == NULL) {
        list->head->link = NULL;
    } else {
        previous->link = NULL;
    }
    free(current);
    return list;
}

List *deleteAtPosition(List *list, int pos) {
    if (pos == 1) {
        list = deleteAtBeginning(list);
        return list;
    }
    Node *current = list->head->link;
    Node *previous = NULL;
    for (int i = 1; i < pos && current != NULL; i++) {
        previous = current;
        current = current->link;
    }
    if (current == NULL) {
        printf("Invalid position\n");
        return list;
    }
    previous->link = current->link;
    free(current);
    return list;
}

List *insertByKey(List *list, int key, int data) {
    Node *current = list->head->link;
    Node *previous = NULL;

    while (current != NULL && current->data != key) {
        previous = current;
        current = current->link;
    }

    if (current == NULL) {
        printf("Key not found\n");
    } else {
        Node *newNode = createNode(data);
        newNode->link = current->link;
        current->link = newNode;
    }

    return list;
}

List *deleteByKey(List *list, int key) {
    Node *current = list->head->link;
    Node *previous = NULL;

    while (current != NULL && current->data != key) {
        previous = current;
        current = current->link;
    }

    if (current == NULL) {
        printf("Key not found\n");
    } else {
        if (previous == NULL) {
            list->head->link = current->link;
        } else {
            previous->link = current->link;
        }
        free(current);
    }

    return list;
}

void *searchByKey(List *list, int key) {
    Node *current = list->head->link;
    int position = 1;

    while (current != NULL && current->data != key) {
        current = current->link;
        position++;
    }

    if (current == NULL) {
        printf("Key not found\n");
    } else {
        printf("Key %d found at position: %d\n", key, position);
    }
}

List *createOrderedList(List *list, int data){
    Node *current = list->head;
    Node *newNode = createNode(data);
    while(current->link != NULL && current->link->data < data){
        current = current->link;
    }
    newNode->link = current->link;
    current->link = newNode;
    return list;
}

List *copyList(List *list) {
    List *coList = (List *)malloc(sizeof(List));
    coList->head = createNode(0); 

    Node *current = list->head->link;
    while (current != NULL) {
        coList = insertAtEnd(coList, current->data);
        current = current->link;
    }

    return coList;
}

void reverseList(List *list){
    Node *current = list->head->link;
    Node *previous = NULL;
    Node *next = NULL;
    while(current != NULL){
        next = current->link;
        current->link = previous;
        previous = current;
        current = next;
    }
    list->head->link = previous;
}

void printMenu() {
    printf("\nMenu:\n");
    printf("1. Insert at the beginning\n");
    printf("2. Insert at the end\n");
    printf("3. Insert at a specific position\n");
    printf("4. Delete at the beginning\n");
    printf("5. Delete at the end\n");
    printf("6. Delete at a specific position\n");
    printf("7. Insert by key\n");
    printf("8. Delete by key\n");
    printf("9. Search by key\n");
    printf("10. Create an ordered list\n");
    printf("11. Copy the list\n");
    printf("12. Reverse the list\n");
    printf("0. Exit\n\n");
}

int main() {
    List *list = (List *)malloc(sizeof(List));
    list->head = createNode(0);

    int choice;
    int data, pos, key;

    
    do {
        
        printMenu();
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Enter data to insert at the beginning: ");
                scanf("%d", &data);
                list = insertAtBeginning(list, data);
                break;

            case 2:
                printf("Enter data to insert at the end: ");
                scanf("%d", &data);
                list = insertAtEnd(list, data);
                break;

            case 3:
                printf("Enter position and data to insert at that position: ");
                scanf("%d %d", &pos, &data);
                list = insertAtPosition(list, pos, data);
                break;

            case 4:
                list = deleteAtBeginning(list);
                break;

            case 5:
                list = deleteAtEnd(list);
                break;

            case 6:
                printf("Enter position to delete from that position: ");
                scanf("%d", &pos);
                list = deleteAtPosition(list, pos);
                break;

            case 7:
                printf("Enter key and data to insert after the key: ");
                scanf("%d %d", &key, &data);
                list = insertByKey(list, key, data);
                break;

            case 8:
                printf("Enter key to delete the node with that key: ");
                scanf("%d", &key);
                list = deleteByKey(list, key);
                break;

            case 9:
                printf("Enter key to search for: ");
                scanf("%d", &key);
                searchByKey(list, key);
                break;

            case 10:
                printf("Enter data to create an ordered list: ");
                scanf("%d", &data);
                list = createOrderedList(list, data);
                break;

            case 11:
                printf("Copying the list...\n");
                List *copy = copyList(list);
                printf("Original List: ");
                displayList(list);
                printf("Copied List: ");
                displayList(copy);
                freeList(copy);
                goto end;
                break;

            case 12:
                printf("Reversing the list...\n");
                reverseList(list);
                break;

            case 0:
                printf("Exiting the program...\n");
                freeList(list);
                return 0;
               
            default:
                printf("Invalid choice. Please enter a valid option.\n");
                goto end;
        }

        printf("Current List: ");
        displayList(list);
        end:;

    } while (choice != 0);
}
