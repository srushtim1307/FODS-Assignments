#include<stdio.h>
#include<string.h>
#include<ctype.h>
#include<stdlib.h>

struct Student {
    int roll_no;
    char name[50];
    char EmailID[50];
    char mobile[12];
};

int isValidRoll(char str[]) {
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
    int len = strlen(email);
    int atCount = 0;
    int dotCountAfterAt = 0;
    // 5 characters 
    if (len < 5) return 0;

    // First and last character
    if (email[0] == '_' || email[0] == '.' || email[0] == '@') return 0;
    if (email[len - 1] == '.' || email[len - 1] == '@' || email[len - 1] == '_') return 0;
    //allowed characters alnum, _, @, .)

    for (int i = 0; i < len; i++) {
        char ch = email[i];
        if (!(isalnum(ch) || ch == '_' || ch == '@' || ch == '.')) return 0;
        // No two dots together 
        if (ch == '.' && i > 0 && email[i + 1] == '.') return 0;
        // Count @ 
        if (ch == '@') {
            atCount++;
            if (atCount > 1) return 0;
            if (i == 0 || i == len - 1) return 0;
        }
    }
    if (atCount != 1) return 0;
    char *atPos = strchr(email, '@');
    // one underscore before @
    
    int underscoreCount = 0;
    for (char *p = email; p < atPos; p++) {
        if (*p == '_') underscoreCount++;
        if (underscoreCount > 1) return 0;

        // _. or ._ before @
        if (*p == '_' && *(p + 1) == '.') return 0;
        if (*p == '.' && *(p + 1) == '_') return 0;
    }

    // dot before @
    if (*(atPos - 1) == '.') return 0;

    //After @, no underscore only one dot 
    for (char *p= atPos-1; *p != '\0'; p++)
    {
        if (*p=='_')
        {
            return 0;
        }
        
    }
    
    for (char *p = atPos + 1; *p != '\0'; p++) {
        if (*p == '_') return 0;
        if (*p == '.') {
            dotCountAfterAt++;
            if (*(p + 1) == '\0' || *(p - 1) == '@') return 0; 
            // dot can't be first/last after @
        }
    }
    if (dotCountAfterAt != 1) return 0;
    return 1;
}

int isValidMobile(char str[]) {
    if (strlen(str) != 10) return 0;
    for (int i = 0; str[i]; i++) {
        if (!isdigit(str[i])) return 0;
    }
    return 1;
}

int isRollDuplicate(struct Student students[], int count, int roll_no) {
    for (int i = 0; i < count; i++) {
        if (students[i].roll_no == roll_no) {
            return 1; //duplicate found
        }
    }
    return 0;
}

int main() {
    struct Student students[10];
    char temp[50];

    for (int i = 0; i < 10; i++) {
        printf("Enter details for student no. %d:\n", i + 1);

        while (1) {
            printf("Enter Roll Number: ");
            scanf("%s", temp);

            if (isValidRoll(temp)) {
                int roll = atoi(temp);
                if (roll == 0) {
                    printf("Roll number cannot be 0. Try again.\n");
                    continue;
                }
            
            if (isRollDuplicate(students, i, roll)) {
                printf("Roll number already exists! Enter a unique roll number.\n");
                continue;
                }
                students[i].roll_no = roll;
                break;
            } 
            else 
            {
                printf("Invalid input. Enter only Numbers.\n");
            }
        }
        // Name
        while (1) {
            printf("Name of the Student : ");
            scanf(" %[^\n]", students[i].name);
            if (isValidName(students[i].name)) {
                break;
            } else {
                printf("Invalid name. Name should contain only letters and spaces.\n");
            }
        }
        
        while (1) {
            printf("Email: ");
            scanf("%s", students[i].EmailID);
            if (isValidEmail(students[i].EmailID)) {
                break;
            } else {
                printf("Invalid EmailID!\n");
            }
        }
        // Mobile Number
        while (1) {
            printf("Mobile Number: ");
            scanf("%s", students[i].mobile);
            if (isValidMobile(students[i].mobile)) {
                break;
            } else {
                printf("Invalid mobile number. Enter 10 digits.\n");
            }
        }

        printf("\n");
    }

    // Displaying all student details
    printf("\nStudent Details:\n");
    for (int i = 0; i < 10; i++) {
        printf("Student %d:\n", i + 1);
        printf("Roll Number: %d\n", students[i].roll_no);
        printf("Name: %s\n", students[i].name);
        printf("Email: %s\n", students[i].EmailID);
        printf("Mobile: %s\n\n", students[i].mobile);
    }
    return 0;
}
