#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

struct Node {
    int data;
    struct Node *next;
};

struct Node *top = NULL;             
struct Node *front = NULL, *rear = NULL; 

void push(int value) {
    struct Node *newNode = (struct Node*)malloc(sizeof(struct Node));

    if (!newNode) {
        printf("Memory allocation failed!\n");
        return;
    }
    
    newNode->data = value;
    newNode->next = top;
    top = newNode;

    printf("%d pushed to stack\n", value);
}

void pop() {
    if (top == NULL) {
        printf("Stack Underflow! Nothing to pop\n");
        return;
    }

    struct Node *temp = top;
    printf("%d popped from stack\n", top->data);
    top = top->next;
    free(temp);
}

void displayStack() {
    if (top == NULL) {
        printf("Stack is empty\n");
        return;
    }

    struct Node *temp = top;
    printf("Stack elements: ");

    while (temp != NULL) {
        printf("%d ", temp->data);
        temp = temp->next;
    }

    printf("\n");
}

void enqueue(int value) {
    struct Node *newNode = (struct Node*)malloc(sizeof(struct Node));
    if (!newNode) {
        printf("Memory allocation failed!\n");
        return;
    }

    newNode->data = value;
    newNode->next = NULL;

    if (rear == NULL) { 
        front = rear = newNode;
    } else {
        rear->next = newNode;
        rear = newNode;
    }

    printf("%d enqueued to queue\n", value);
}

void dequeue() {
    if (front == NULL) {
        printf("Queue Underflow! Nothing to dequeue\n");
        return;
    }

    struct Node *temp = front;
    printf("%d dequeued from queue\n", temp->data);

    front = front->next;
    if (front == NULL)
        rear = NULL;

    free(temp);
}

void displayQueue() {
    if (front == NULL) {
        printf("Queue is empty\n");
        return;
    }

    struct Node *temp = front;
    printf("Queue elements: ");

    while (temp != NULL) {
        printf("%d ", temp->data);
        temp = temp->next;
    }

    printf("\n");
}

int getIntInput(const char *message) {
    char buffer[100];
    int num;
    char extra;

    while (1) {
        printf("%s", message);
        fgets(buffer, sizeof(buffer), stdin);

        if (sscanf(buffer, " %d %c", &num, &extra) == 1) {
            return num;
        }

        printf("Invalid input! Please enter ONLY a single integer.\n");
    }
}

int main() {
    int mainChoice, subChoice, value;

    while (1) {
        printf("\nMAIN MENU\n");
        printf("1. Stack\n");
        printf("2. Queue\n");
        printf("3. Exit\n");

        mainChoice = getIntInput("Enter your choice: ");

        switch (mainChoice) {

            case 1:
                while (1) {
                    printf("\nStack Menu\n");
                    printf("1. Push\n");
                    printf("2. Pop\n");
                    printf("3. Display\n");
                    printf("4. Main Menu\n");

                    subChoice = getIntInput("Enter your choice: ");

                    if (subChoice == 4) break;

                    switch (subChoice) {
                        case 1:
                            value = getIntInput("Enter value to push: ");
                            push(value);
                            break;

                        case 2:
                            pop();
                            break;

                        case 3:
                            displayStack();
                            break;

                        default:
                            printf("Invalid choice!\n");
                    }
                }
                break;

            case 2:
                while (1) {
                    printf("\nQueue Menu\n");
                    printf("1. Enqueue\n");
                    printf("2. Dequeue\n");
                    printf("3. Display\n");
                    printf("4. Main Menu\n");

                    subChoice = getIntInput("Enter your choice: ");

                    if (subChoice == 4) break;

                    switch (subChoice) {

                        case 1:
                            value = getIntInput("Enter value to enqueue: ");
                            enqueue(value);
                            break;

                        case 2:
                            dequeue();
                            break;

                        case 3:
                            displayQueue();
                            break;

                        default:
                            printf("Invalid choice!\n");
                    }
                }
                break;

            case 3:
                printf("Exiting...\n");
                return 0;

            default:
                printf("Invalid choice!\n");
        }
    }
}
