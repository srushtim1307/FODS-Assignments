#include <stdio.h>
#include <stdlib.h>

#define SIZE 10  // Size of Hash Table

// Node structure for chaining
struct Node {
    int data;
    struct Node* next;
};

struct Node* hashTable[SIZE]; // Hash table (array of linked lists)

// Hash Function
int hash(int key) {
    return key % SIZE;
}

// Insert a value in hash table
void insert(int value) {
    int index = hash(value);

    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode->data = value;
    newNode->next = hashTable[index];   // Insert at beginning
    hashTable[index] = newNode;

    printf("%d Inserted at index %d\n", value, index);
}

// Search a value inside hash table
void search(int value) {
    int index = hash(value);
    struct Node* temp = hashTable[index];

    while (temp != NULL) {
        if (temp->data == value) {
            printf("Element %d found at index %d\n", value, index);
            return;
        }
        temp = temp->next;
    }

    printf("Element %d not found!\n", value);
}

// Display hash table
void display() {
    for (int i = 0; i < SIZE; i++) {
        struct Node* temp = hashTable[i];
        printf("Index %d -> ", i);

        while (temp != NULL) {
            printf("%d -> ", temp->data);
            temp = temp->next;
        }
        printf("NULL\n");
    }
}

int main() {
    int choice, value;

    while (1) {
        printf("\n----- Hash Table Menu -----\n");
        printf("1. Insert\n");
        printf("2. Search\n");
        printf("3. Display\n");
        printf("4. Exit\n");
        printf("Enter choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Enter value to insert: ");
                scanf("%d", &value);
                insert(value);
                break;

            case 2:
                printf("Enter value to search: ");
                scanf("%d", &value);
                search(value);
                break;

            case 3:
                display();
                break;

            case 4:
                exit(0);

            default:
                printf("Invalid choice! Try again.\n");
        }
    }
    return 0;
}
