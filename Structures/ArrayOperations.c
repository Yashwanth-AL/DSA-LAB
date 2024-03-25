#include <stdio.h>
#include <stdlib.h>

void insertByPosition(int *arr, int *n, int pos, int key);
void deleteByPosition(int *arr, int *n, int pos);
void insertByKey(int *arr, int *n, int key, int val);
void deleteByKey(int *arr, int *n, int key);
void sort(int *arr, int *n);
void insertByOrder(int *arr, int *n, int key);
void searchByKey(int *arr, int *n, int key);
void searchByPosition(int *arr, int *n, int pos);
void reverse(int *arr, int *n);
void printArray(int *arr, int *n);

int main() {
    int *arr, n, c, choice;
    int pos, key, val;
    printf("Enter the capacity and size of the array\n");
    scanf("%d%d", &c, &n);
    arr = (int *)malloc(c * sizeof(int));
    printf("Enter %d elements of the array:\n", n);
    for(int i = 0; i < n; i++){
        scanf("%d", (arr+i));
    }

    do {
        printf("\nMenu: \n");
        printf("1. Insert by position.\n");
        printf("2. Delete by position.\n");
        printf("3. Insert by Key.\n");
        printf("4. Delete by Key.\n");
        printf("5. Insert by Order.\n");
        printf("6. Search by Key.\n");
        printf("7. Search by Position.\n");
        printf("8. Reverse the content.\n");
        printf("9. Exit\n\n");
        printf("Enter your choice:\t");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Enter the position and element to insert:\t");
                scanf("%d%d", &pos, &key);
                insertByPosition(arr, &n, pos, key);
                break;
            case 2:
                printf("Enter the position to Delete:\t");
                scanf("%d", &pos);
                deleteByPosition(arr, &n, pos);
                break;
            case 3:
                printf("Enter the key element to be replaced and the new value:\t");
                scanf("%d%d", &key, &val);
                insertByKey(arr, &n, key, val);
                break;
            case 4:
                printf("Enter the key element to delete:\t");
                scanf("%d", &key);
                deleteByKey(arr, &n, key);
                break;
            case 5:
                printf("Enter the element to insert by order:\t");
                scanf("%d", &key);
                sort(arr, &n);
                insertByOrder(arr, &n, key);
                break;
            case 6:
                printf("Enter the key to search:\t");
                scanf("%d", &key);
                searchByKey(arr, &n, key);
                break;
            case 7:
                printf("Enter the position to search:\t");
                scanf("%d", &pos);
                searchByPosition(arr, &n, pos);
                break;
            case 8:
                printf("The contents of the array after reversing are:\n");
                reverse(arr, &n);
                goto end;
                break;
            case 9:
                printf("Exiting the program\n");
                free(arr);
                return 0;
            default:
                printf("Invalid choice. Please enter a valid option.\n");
                goto end;
        }

        printArray(arr, &n);
        end:;
    } while (choice != 9);

}

void insertByPosition(int *arr, int *n, int pos, int key) {
    
    if (pos < 1 || pos > *n+1) {
        printf("Invalid position\n");
        return;
    }

    for (int i = *n-1; i >= pos-1; i--) {
        arr[i+1] = arr[i];
    }

    arr[pos-1] = key;
    (*n)++;

    printf("Element %d inserted at position %d\n", key, pos);
}

void deleteByPosition(int *arr, int *n, int pos) {
   
    if (pos < 1 || pos > *n) {
        printf("Invalid position\n");
        return;
    }
    
    for (int i = pos-1; i < *n - 1; i++) {
        arr[i] = arr[i + 1];
    }
    
    (*n)--;

    printf("Element at position %d deleted\n", pos);
}

void insertByKey(int *arr, int *n, int key, int val) {
    int found = 0;
    for (int i = 0; i < *n; i++) {
        if (arr[i] == key) {
            arr[i] = val;
            printf("Element %d replaced with %d\n", key, val);
            found = 1;
            break;
        }
    }

    if (found == 0) {
        printf("Key not found\n");
    }
}

void deleteByKey(int *arr, int *n, int key) {
    int found = 0;
    for (int i = 0; i < *n; i++) {
        if (arr[i] == key) {
            found = 1;
            for (int j = i; j < *n - 1; j++) {
                arr[j] = arr[j + 1];
            }
            (*n)--;
            printf("Element %d deleted\n", key);
            break;
        }
    }

    if (found == 0) {
        printf("Key not found\n");
    }
}

void sort(int *arr, int *n) {

    for (int i = 0; i < *n - 1; i++) {
        for (int j = 0; j < *n - i - 1; j++) {
            if (arr[j] > arr[j + 1]) {
                int temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        }
    }
}

void insertByOrder(int *arr, int *n, int key) {
    int i;
    for (i = *n - 1; i >= 0 && key < arr[i]; i--) {
        arr[i + 1] = arr[i];
    }
    arr[i + 1] = key;
    (*n)++;
    printf("Element %d inserted in order\n", key);
}

void searchByKey(int *arr, int *n, int key) {
    for (int i = 0; i < *n; i++) {
        if (arr[i] == key) {
            printf("Key %d found at position %d\n", key, i+1);
            return;
        }
    }

    printf("Key %d not found\n", key);
}

void searchByPosition(int *arr, int *n, int pos) {
    if (pos >= 1 && pos <= *n) {
        printf("Element at position %d is %d\n", pos, arr[pos-1]);
    } else {
        printf("Invalid position\n");
    }
}

void reverse(int *arr, int *n) {
    for (int i = 0; i < *n / 2; i++) {
        int temp = arr[i];
        arr[i] = arr[*n-i-1];
        arr[*n-i-1] = temp;
    }

    for (int i = 0; i < *n; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");
}

void printArray(int *arr, int *n) {
    printf("Current array: ");
    for (int i = 0; i < *n; i++) {
        printf("%d ", arr[i]);
    }
   printf("\n");
}