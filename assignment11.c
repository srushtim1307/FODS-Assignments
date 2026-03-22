#include <stdio.h>
#include <stdlib.h>

#define EMPTY -1 
#define DELETED -2 

typedef struct { 
    int *table;   
    int size;
} HashTable;

int HashFunction(int key, int size) {
    return key % size;
}

int validInput() {
    char input[200]; int x; char c;

    while (1) {
        fgets(input, sizeof(input), stdin);
        if (sscanf(input, "%d %c", &x, &c) == 1) {
            if (x < 0) {
                printf("Negative values are not allowed. Enter again: ");
                continue;
            }
            return x;
        }
        printf("Invalid input! Enter number only: ");
    }
}


HashTable* createTable(int size) {
    HashTable* h = (HashTable*)malloc(sizeof(HashTable));
    h->size = size;
    h->table = (int*)malloc(size * sizeof(int));

    for(int i=0; i<size; i++)
        h->table[i] = EMPTY;

    return h;
}

void insertKey(HashTable* h, int key) {

 if (key < 0) {
        printf("Negative values are not allowed!\n");
        return;
    }

    int index = HashFunction(key, h->size);
    int start = index;

    while(h->table[index] != EMPTY && h->table[index] != DELETED) {
        if(h->table[index] == key){
            printf("Duplicate key not allowed!\n");
            return;
        }
        index = (index + 1) % h->size;
        if(index == start){
            printf("Hash Table Full!\n"); 
            return;
        }
    }

    h->table[index] = key;
    printf("Inserted: %d\n", key);
}

void searchKey(HashTable* h, int key) {

    if (key < 0) {
        printf("Negative values are not allowed!\n");
        return;
    }
    int index = HashFunction(key, h->size);
    int start = index;


    while(h->table[index] != EMPTY) {
        if(h->table[index] == key) {
            printf("Found %d at index %d\n", key, index);
            return;
        }
        index = (index + 1) % h->size;
        if(index == start) break;
    }

    printf("The value is not found!\n");
}

void deleteKey(HashTable* h, int key) {
    int index = HashFunction(key, h->size);
    int start = index;

    while(h->table[index] != EMPTY) {
        if(h->table[index] == key) {
            h->table[index] = DELETED;
            printf("Deleted %d \n", key);
            return;
        }
        index = (index + 1) % h->size;
        if(index == start) break;
    }

    printf("Value not found!\n");
}

void updateKey(HashTable* h, int oldKey, int newKey) {

if (oldKey < 0 || newKey < 0) {
        printf("Negative values are not allowed!\n");
        return;
    }

    int index = HashFunction(oldKey, h->size);
    int start = index;

    while(h->table[index] != EMPTY) {
        if(h->table[index] == oldKey) {
            h->table[index] = DELETED;
            insertKey(h, newKey);
            printf("Updated from %d to %d\n", oldKey, newKey);
            return;
        }
        index = (index + 1) % h->size;
        if(index == start) break;
    }
    printf("Old key not found!\n");
}

void displayTable(HashTable* h) {
    for(int i=0; i<h->size; i++){
        if(h->table[i] == EMPTY)
            printf("%d: [Empty]\n", i);
        else if(h->table[i]==DELETED)
        printf("%d: [DELETED]\n",i);
        else
            printf("%d: %d\n", i, h->table[i]);
    }
}

int main() {
    HashTable* h = createTable(10);
    int ch;

    do {
        printf("\n1.Insert\n2.Search\n3.Delete\n4.Update\n5.Display\n6.Exit\nEnter choice: ");
        ch = validInput();
       
        switch(ch){
            case 1: printf("Enter value to insert: "); insertKey(h, validInput()); break;
            case 2: printf("Enter value to search: "); searchKey(h, validInput()); break;
            case 3: printf("Enter value to delete: "); deleteKey(h, validInput()); break;
            case 4:{
                printf("Enter the old value: "); int old = validInput();
                printf("Enter the new value: "); int newv = validInput();
                updateKey(h, old, newv);
            } break;
            case 5: displayTable(h); break;
            case 6: printf("Exiting...\n"); break;
            default: printf("Invalid Choice!\n");
        }

    } while(ch != 6);

free(h->table);
free(h);

    return 0;
}
