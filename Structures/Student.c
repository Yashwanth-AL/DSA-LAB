#include <stdio.h>
#include <stdlib.h>

int i, j;

struct Student {
    char name[50];
    int regno;
    int marks[3];
    float avgmarks;
};

void read(struct Student *ptr, int n) {
    for (i = 0; i < n; i++) {
        printf("\nEnter details of student %d\n", i + 1);
        printf("Name : \t");
        scanf("%49s", &(ptr + i)->name);
        printf("Register number : \t");
        scanf("%d", &(ptr + i)->regno);
        for (int j = 0; j < 3; j++) {
            printf("Marks in test %d :\t", j + 1);
            scanf("%d", &(ptr + i)->marks[j]);
        }
    }
}

void calculateAverage(struct Student *ptr, int n) {
    int a, b, c;
    for (i = 0; i < n; i++) {
        a = (ptr + i)->marks[0];
        b = (ptr + i)->marks[1];
        c = (ptr + i)->marks[2];
        float avg;
        if (a >= b && a >= c) {
            avg = a + (b > c ? b : c);
        } else if (b >= a && b >= c) {
            avg = b + (a > c ? a : c);
        } else {
            avg = c + (a > b ? a : b);
        }
        (ptr + i)->avgmarks = avg/2.0;
    }
}

void display(struct Student *ptr, int n) {
    calculateAverage(ptr, n);
    for (i = 0; i < n; i++) {
        printf("\nDetails of Student %d\n", (i + 1));
        printf("Name : %s\n", (ptr + i)->name);
        printf("Registration number : %d\n", (ptr + i)->regno);
        for (j = 0; j < 3; j++) {
            printf("Marks in test %d is %d\n", j + 1, (ptr + i)->marks[j]);
        }
        printf("Average best two test marks of %s is %.2f :\n", (ptr + i)->name, (ptr + i)->avgmarks);
    }
}

int main() {
    int n, choice;
    printf("Enter the number of students :\t");
    scanf("%d", &n);
    struct Student *p;
    p = (struct Student *)malloc(n * (sizeof(struct Student)));
    if (p == NULL) {
        printf("Memory allocation failed\n");
        return 1;
    }
    do {
        printf("\nMenu :\n");
        printf("1. Read student Information \n");
        printf("2. Display student Information \n");
        printf("3. Calculate Average Marks of best 2 tests\n");
        printf("4. Exit \n\n");
        printf("Enter your choice\n");
        scanf("%d", &choice);
        switch (choice) {
            case 1:
                read(p, n);
                break;
            case 2:
                display(p, n);
                break;
            case 3:
                calculateAverage(p, n);
                for(i = 0; i < n; i++){
                    printf("Average best two test marks of %s is %.2f :\n", (p+i)->name, (p+i)->avgmarks);
                }
                break;
            case 4:
                printf("Exiting the program\n");
                free(p);
                return 0;
            default:
                printf("Please enter a correct choice\n");
                break;
        }
    } while (choice != 4);
}