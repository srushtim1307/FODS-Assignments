#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

#define SIZE 10

//Stack
int stack[SIZE];  
int top = -1; //stack is empty 

void push(int value) 
{
    if (top == SIZE - 1) 
        printf("Stack is full!Cannot push %d\n", value);  
    else {
        stack[++top] = value;
        printf("%d pushed to stack\n", value);
    }
}


void pop() {
    if (top == -1)
        printf("Nothing to pop\n");
    else
        printf("%d popped from stack\n", stack[top--]);

}


void displayStack() {
    if (top == -1)
        printf("Stack is empty\n");
    else {
        printf("Stack elements: ");
        for (int i = 0; i<=top; i++)
            printf("%d ", stack[i]);
        printf("\n");
    }
}


//Queue
int queue[SIZE];
int front = -1, rear = -1;


void enqueue(int value) {
    if (rear == SIZE - 1) {
        // Check if space is available at front
        if (front > 0) {
            // Shift all elements to the beginning
            int j = 0;
            for (int i = front; i <= rear; i++) {
                queue[j++] = queue[i];
            }
            rear = rear - front;
            front = 0;
        } else {
            printf("Queue Overflow! Cannot enqueue %d\n", value);
            return;
        }
    }


    if (front == -1)
        front = 0;

    queue[++rear] = value;
    printf("%d enqueued to queue\n", value);
}


void dequeue() {
    if (front == -1 || front > rear)
        printf("Queue Underflow! Nothing to dequeue\n");
    else
        printf("%d dequeued from queue\n", queue[front++]);
}


void displayQueue() {
    if (front == -1 || front > rear)
        printf("Queue is empty\n");
    else {
        printf("Queue elements: ");
        for (int i = front; i <= rear; i++)
            printf("%d ", queue[i]);
        printf("\n");
    }
}


//Helper 
int isNumber(char str[]) {
    for (int i = 0; str[i]; i++) {
        if (!isdigit(str[i])) return 0;
    }
    return 1;
}


//Main Menu
int main() {
    int mainChoice, subChoice, value;
    char temp[20];

    while (1) {
        //MAIN MENU
        while (1) {
            printf("\n MAIN MENU \n");
            printf("1. Stack Operations\n");
            printf("2. Queue Operations\n");
            printf("3. Exit\n");
            printf("Enter your choice: ");
            scanf("%s", temp);

            if (!isNumber(temp)) {
                printf("Please enter only numbers!\n");
                continue;
            }

            mainChoice = atoi(temp);
            break;
        }

        switch (mainChoice) {
            case 1:
                while (1) {
                    
                    //STACK MENU
                    while (1) {
                        printf("\n Stack Menu \n");
                        printf("1. Push\n2. Pop\n3. Display\n4. Back to Main Menu\n");
                        printf("Enter choice: ");
                        scanf("%s", temp);

                        if (!isNumber(temp)) {
                            printf("Please enter only numbers!\n");
                            continue;
                        }

                        subChoice = atoi(temp);
                        break;
                    }

                    if (subChoice == 4) break;

                    switch (subChoice) {
                        case 1:
                            while (1) {
                                printf("Enter value to push: ");
                                scanf("%s", temp);
                                if (!isNumber(temp)) {
                                    printf("Enter numbers only!\n");
                                    continue;
                                }
                                value = atoi(temp);
                                push(value);
                                break;
                            }
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
                    // --- QUEUE MENU ---
                    while (1) {
                        printf("\n----- Queue Menu -----\n");
                        printf("1. Enqueue\n2. Dequeue\n3. Display\n4. Back to Main Menu\n");
                        printf("Enter choice: ");
                        scanf("%s", temp);

                        if (!isNumber(temp)) {
                            printf("Please enter only numbers!\n");
                            continue;
                        }

                        subChoice = atoi(temp);
                        break;
                    }

                    if (subChoice == 4) break;

                    switch (subChoice) {
                        case 1:
                            while (1) {
                                printf("Enter value to enqueue: ");
                                scanf("%s", temp);
                                if (!isNumber(temp)) {
                                    printf("Enter numbers only!\n");
                                    continue;
                                }
                                value = atoi(temp);
                                enqueue(value);
                                break;
                            }
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
                printf("Exiting program...\n");
                return 0;

            default:
                printf("Invalid choice! Try again.\n");
        }
    }
}
