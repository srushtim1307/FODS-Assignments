#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

// Student struct
struct Student {  
    int roll_no; 
    char name[50];
    char EmailID[50];
    char mobile[12];
    struct Student *next;  
};

// VALIDATION 
int isValidRoll(char str[]) { //is valid function
    for (int i = 0; str[i]; i++) {
        if (!isdigit(str[i])) return 0;
    }
    return 1;
}

int isValidName(char str[]) {
    for (int i = 0; str[i]; i++) {
        if (!isalpha(str[i]) && str[i] != ' ') return 0;
    }
    return 1;
}

int isValidEmail(char email[]) {

    int len = strlen(email);//lenght of email 
    int atCount = 0, dotCountAfterAt = 0;

    if (len < 5) return 0;//atleast 5 characters 

    //first and last char 
    if (email[0] == '_' || email[0] == '.' || email[0] == '@') return 0;
    if (email[len - 1] == '.' || email[len - 1] == '@' || email[len - 1] == '_') return 0;

    for (int i = 0; i < len; i++) {
        char ch = email[i];//stores the char in new variable ch 
        if (!(isalnum(ch) || ch == '_' || ch == '@' || ch == '.')) return 0;
        if (ch == '.' && i > 0 && email[i + 1] == '.') return 0;//consecutive dots 
        if (ch == '@') 
        {
            atCount++;
            if (atCount > 1) return 0;
            //if (i == 0 || i == len - 1) return 0;
        }
    }

    if (atCount != 1) return 0;//atleast 1 @  

    char *atPos = strchr(email, '@');
    int underscoreCount = 0;
    for (char *p = email; p < atPos; p++) {
        if (*p == '_') underscoreCount++;
        if (underscoreCount > 1) return 0;
        if (*p == '_' && *(p + 1) == '.') return 0;
        if (*p == '.' && *(p + 1) == '_') return 0;
    }

    if(*(atPos-1)=='_') return 0;

    if (*(atPos - 1) == '.') return 0;

    for (char *p = atPos + 1; *p != '\0'; p++) {
        if (*p == '_') return 0;
        if (*p == '.') {
            dotCountAfterAt++;
            if (*(p + 1) == '\0' || *(p - 1) == '@') return 0;
        }
    }

    if (dotCountAfterAt != 1) return 0;

    return 1;
}

int isValidMobile(char str[]) {
    if (strlen(str) != 10) return 0;
    for (int i = 0; str[i]; i++) 
    {
        if (!isdigit(str[i])) return 0;
    }
    return 1;
}

int isRollDuplicate(struct Student *head, int roll_no) 
{
    struct Student *temp = head; 
    while (temp!=NULL)
    {
        if (temp->roll_no == roll_no) return 1;
        temp = temp->next;
    }
    return 0;
}

// Function to DISPLAY students
void displayStudents(struct Student *head) {
    printf("\n================ Student Details ================\n");
    struct Student *tempPtr = head;
    int count = 1;  
    while (tempPtr != NULL) {
        printf("Student %d:\n", count++);
        printf("Roll Number: %d\n", tempPtr->roll_no);
        printf("Name: %s\n", tempPtr->name);
        printf("Email ID: %s\n", tempPtr->EmailID);
        printf("Mobile number: %s\n\n", tempPtr->mobile);
        tempPtr = tempPtr->next;
    }
}
//DELETE Function
struct Student* deleteStudent(struct Student *head, int roll) {
    struct Student *temp = head, *prev = NULL;

    while (temp != NULL && temp->roll_no != roll) {
        prev = temp; 
    
        temp = temp->next;
    }
//end reached not found 
    if (temp == NULL) {
        printf("Student with Roll %d not found.\n", roll);
        return head;
    }


    //delete head
    if (prev == NULL) {
        head = head->next;
    } else {
        prev->next = temp->next;
    }


    free(temp);
    printf("Student with Roll %d deleted.\n", roll);
    return head;
}
// UPDATE FUNCTION
void updateStudent(struct Student *head, int roll) {
    struct Student *temp = head;
    
    while (temp != NULL && temp->roll_no != roll) {
        temp = temp->next;
    }

    if (temp == NULL) {
        printf("Student with Roll %d not found.\n", roll);
        return;
    }

    printf("Updating details for Roll %d\n", roll);

    // Name
    while (1) {
        printf("Enter New Name: ");
        scanf(" %[^\n]", temp->name);
        if (isValidName(temp->name)) break;
        else printf("Invalid name!\n");
    }


    // Email
    while (1) {
        printf("Enter New Email: ");
        scanf("%s", temp->EmailID);
        if (isValidEmail(temp->EmailID)) break;
        else printf("Invalid email!\n");
    }


    // Mobile
    while (1) {
        printf("Enter New Mobile: ");
        scanf("%s", temp->mobile);
        if (isValidMobile(temp->mobile)) break;
        else printf("Invalid mobile!\n");
    }

    printf("Student details updated successfully!\n");
    }


//MAIN FUNCTION
int main() {
    struct Student *head = NULL, *tail = NULL;
    char temp[50];
    int choice;

    while (1) {
        printf("\nMenu:\n1. Add a Student\n2. Display all Students\n3. Delete a Student\n4. Update a Student\n0. Exit\nEnter your choice: ");
        scanf("%d", &choice);
        
        if (choice == 0) break;

        if (choice == 1) {
            struct Student *newStudent = (struct Student*)malloc(sizeof(struct Student));
            newStudent->next = NULL;

            // Roll Number
            while (1) {
                printf("Enter Roll Number: ");
                scanf("%s", temp);
                if (isValidRoll(temp)) {
                    int roll = atoi(temp);
                    if (roll == 0) {
                        printf("Roll number cannot be 0.\n");
                        continue;
                    }
                    if (isRollDuplicate(head, roll)) {
                        printf("Roll number already exists!\n");
                        continue;
                    }
                    newStudent->roll_no = roll;
                    break;
                } else {
                    printf("Invalid roll.\n");
                }
            }

            // Name
            while (1) {
                printf("Enter Name: ");
                scanf(" %[^\n]", newStudent->name);
                if (isValidName(newStudent->name)) break;
                else printf("Invalid name!\n");
            }

            // Email
            while (1) {
                printf("Enter Email: ");
                scanf("%s", newStudent->EmailID);
                if (isValidEmail(newStudent->EmailID)) break;
                else printf("Invalid email!\n");
            }

            // Mobile
            while (1) {
                printf("Enter Mobile: ");
                scanf("%s", newStudent->mobile);
                if (isValidMobile(newStudent->mobile)) break;
                else printf("Invalid mobile!\n");
            }

            // Insert into Linked List
            if (head == NULL) {
                head = tail = newStudent;
            } else {
                tail->next = newStudent;
                tail = newStudent;
            }
            printf("Student added successfully!\n");

        } else if (choice == 2) {
            displayStudents(head);

        } else if (choice == 3) {
            int roll;
            printf("Enter Roll Number to delete: ");
            scanf("%d", &roll);
            head = deleteStudent(head, roll);

        } else if (choice == 4) {
            int roll;
            printf("Enter Roll Number to update: ");
            scanf("%d", &roll);
            updateStudent(head, roll);
        }
    }
    //Free mem
    struct Student *cur = head;
    while (cur != NULL) {
        struct Student *next = cur->next;
        free(cur);
        cur = next;
    }
    printf("Program exited.\n");
    return 0;
    
}
