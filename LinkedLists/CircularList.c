#include <stdio.h>
#include <stdlib.h>

struct Node {
    int data;
    struct Node *link;
};

struct CircularList {
    struct Node *head;
};

typedef struct Node Node;
typedef struct CircularList List;

Node *createNode(int data) {
    Node *newNode = (Node *)malloc(sizeof(Node));
    if(newNode == NULL){
        printf("Memory allocation failed\n");
        return NULL;
    }
    newNode->data = data;
    newNode->link = NULL;
    return newNode;
}

void displayList(List *list) {
    if(list->head->link == NULL){
        printf("Empty\n");
        return;
    }
    Node *current = list->head->link;
    while (current->link != list->head->link) {
        printf("%d -> ", current->data);
        current = current->link;
    }
    printf("%d\n", current->data);
}

void freeList(List *list) {
    if(list->head->link == NULL)
        return;
    Node *current = list->head->link;
    while (current->link != list->head->link) {
        Node *temp = current;
        current = current->link;
        free(temp);
    }
    free(current); 
    free(list->head);
    free(list);
}

List *insertAtBeginning(List *list, int data) {
    Node *newNode = createNode(data);
    Node *current = list->head->link;
    if (list->head->link == NULL) {
        list->head->link = newNode;
        newNode->link = newNode;
        list->head->data++;
        return list;
    }
    while(current->link != list->head->link){
        current = current->link;
    }
    current->link = newNode;
    newNode->link = list->head->link;
    list->head->link = newNode;
    list->head->data++;
    return list;
}

List *insertAtEnd(List *list, int data) {
    Node *newNode = createNode(data);
    Node *current = list->head->link;
    if (list->head->link == NULL) {
        list->head->link = newNode;
        newNode->link = newNode;
        list->head->data++;
        return list;
    }
    while (current->link != list->head->link) {
        current = current->link;
    }
    current->link = newNode;
    newNode->link = list->head->link;
    list->head->data++;
    return list;
}

List *insertAtPosition(List *list, int pos, int data) {
    if (pos == 1) {
        list = insertAtBeginning(list, data);
        return list;
    }
    else if (pos == list->head->data + 1){
        list = insertAtEnd(list, data);
        return list;
    }
    Node *current = list->head->link;
    for (int i = 1; i < pos - 1 && current->link != list->head->link; i++) {
        current = current->link;
    }
    if (current->link == list->head->link) {
        printf("Invalid position\n");
        return list;
    }
    Node *newNode = createNode(data);
    newNode->link = current->link;
    current->link = newNode;
    list->head->data++;
    return list;
}

List *deleteAtBeginning(List *list) {
    if (list->head->link == NULL) {
        printf("List is empty. Nothing to delete.\n");
        return list;
    }
    Node *current = list->head->link;
    Node *tail = current->link;
    while (tail->link != list->head->link) {
        tail = tail->link;
    }
    if (tail == current) {
        list->head->link = NULL;
    } else {
        tail->link = current->link;
        list->head->link = current->link;
    }
    list->head->data--;
    free(current);
    return list;
}

List *deleteAtEnd(List *list) {
    if (list->head->link == NULL) {
        printf("List is empty. Nothing to delete.\n");
        return list;
    }
    Node *current = list->head->link;
    Node *previous = NULL;
    while (current->link != list->head->link) {
        previous = current;
        current = current->link;
    }
    if (previous == NULL) {
        list->head->link = NULL;
    } else {
        previous->link = list->head->link;
    }
    list->head->data--;
    free(current);
    return list;
}

List *deleteAtPosition(List *list, int pos) {
    if (pos == 1) {
        list = deleteAtBeginning(list);
        return list;
    }
    if (pos == list->head->data) {
        list = deleteAtEnd(list);
        return list;
    }
    Node *current = list->head->link;
    Node *previous = NULL;
    for (int i = 1; i < pos && current->link != list->head->link; i++) {
        previous = current;
        current = current->link;
    }
    if (current->link == list->head->link) {
        printf("Invalid position\n");
    }   
    else {
        previous->link = current->link;
        free(current);
    }
    list->head->data--;
    return list;
}

int searchByKey(List *list, int key) {
    if(list->head->link == NULL){
        return -1;
    }
    Node *current = list->head->link;
    int position = 1;

    while (current->link != list->head->link && current->data != key) {
        current = current->link;
        position++;
    }

    if (current->data == key) {
        return position; 
    } else {
        return -1; 
    }
}

List *deleteByKey(List *list, int key) {
    int pos = searchByKey(list, key);
    if(pos == -1)
        printf("key not found\n");
    else 
        list = deleteAtPosition(list, pos);
    return list;
}

List *createOrderedList(List *list, int key){
    if(list->head->link == NULL || key < list->head->link->data){
        list = insertAtBeginning(list, key);
        return list;
    }
    int pos = 1;
    Node *current = list->head->link;
    while(key > current->link->data && current->link != list->head->link){
        current = current->link;
        pos++;
    }
    list = insertAtPosition(list,pos + 1,key);
    return list;
}

List *copyList(List *list) {
    if(list->head->link == NULL){
        return list;
    }
    List *coList = (List *)malloc(sizeof(List));
    coList->head = createNode(0); 

    Node *current = list->head->link;
    while (current->link != list->head->link) {
        coList = insertAtEnd(coList, current->data);
        current = current->link;
    }
    coList = insertAtEnd(coList, current->data);
    return coList;
}

void reverseList(List *list){
    if(list->head->link == NULL){
        printf("List is empty. Cannot reverse.\n");
        return;
    }
    Node *current = list->head->link;
    Node *previous = NULL;
    Node *next = NULL;
    Node *start = list->head->link;
    do {
        next = current->link;
        current->link = previous;
        previous = current;
        current = next;
    } while (current != list->head->link);
    list->head->link = previous;
    start->link = previous;
}

void printMenu() {
    printf("\nMenu:\n");
    printf("1. Insert at the beginning\n");
    printf("2. Insert at the end\n");
    printf("3. Insert at a specific position\n");
    printf("4. Delete at the beginning\n");
    printf("5. Delete at the end\n");
    printf("6. Delete at a specific position\n");
    printf("7. Delete by key\n");
    printf("8. Search by key\n");
    printf("9. Create an ordered list\n");
    printf("10. Copy the list\n");
    printf("11. Reverse the list\n");
    printf("0. Exit\n\n");
}

int main() {
    List *list = (List *)malloc(sizeof(List));
    list->head = createNode(0);

    int choice;
    int data, pos, key;

    printMenu();
    
    do {
        
       // printMenu();
        printf("\nEnter your choice: ");
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
                printf("Enter key to delete the node with that key: ");
                scanf("%d", &key);
                list = deleteByKey(list, key);
                break;

            case 8:
                printf("Enter key to search for: ");
                scanf("%d", &key);
                pos = searchByKey(list, key);
                if (pos == -1) 
                    printf("Key not found\n");
                else 
                    printf("Key %d found at position: %d\n", key, pos);
                break;

            case 9:
                printf("Enter data to create an ordered list: ");
                scanf("%d", &data);
                list = createOrderedList(list, data);
                break;

            case 10:
                printf("Copying the list...\n");
                List *copy = copyList(list);
                printf("Original List: ");
                displayList(list);
                printf("Copied List: ");
                displayList(copy);
                freeList(copy);
                goto end;
                break;

            case 11:
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
