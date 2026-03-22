#include <stdio.h>

int validInput()
{
    char input[100];
    int x;
    char extra;
    while (1)
    {
        fgets(input, sizeof(input), stdin);
     if (sscanf(input, "%d %c", &x, &extra) == 1)
        {
            return x;
        }
        printf("Invalid input! Enter a number: ");
    }
}

int binarysearch(int arr[], int n, int key)
{
    int left = 0, right = n - 1;
    while (left <= right)
    {
        int mid = (left + right) / 2;
        if (arr[mid] == key)
            return mid;
        else if (arr[mid] < key)
            left = mid + 1;
        else
            right = mid - 1;
    }
    return -1;
}

void bubblesort(int arr[], int n)
{
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n - i - 1; j++)
        {
            if (arr[j] > arr[j + 1])
            {
                int temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
                }
        }
    }
}

void selectionsort(int arr[], int n){
    for (int i = 0; i < n-1; i++)
    {
        int minindex = i;
        for (int j = i+1; j < n; j++)
        {
            if(arr[j]<arr[minindex])
            minindex=j;
        }

        if(minindex!=i){
            int temp = arr[i];
            arr[i]=arr[minindex];
            arr[minindex]=temp;
        }
    }
}

void insertionsort(int arr[], int n){
    for (int i = 1; i < n; i++)
    {
        int key = arr[i];
        int j=i-1;

        while(j>=0 && arr[j]>key){
            arr[j+1]=arr[j];
            j--;
        }

        arr[j+1]=key;
    }
    
}


void displaySorted(int arr[], int n)
{
    printf("Sorted Array: ");
    for (int i = 0; i < n; i++)
        printf("%d ", arr[i]);
    printf("\n");
}

int main()
{
    int arr[100], n, choice, key, result;
    int isSorted = 0;
    printf("Enter number of elements (1 to 100): ");
    n = validInput();
    while (n <= 0 || n > 100)
    {
        printf("Invalid size! Enter between 1 to 100: ");
        n = validInput();
    }
    printf("Enter %d elements:\n", n);
    for (int i = 0; i < n; i++)
    {
        printf("Element %d: ", i + 1);
        arr[i] = validInput();
    }
    while (1)
    {
        printf("\nMENU\n");
        printf("1. Bubble Sort\n");
        printf("2. Binary Search\n");
        printf("3. Selection Sort\n");
        printf("4. Insertion Sort\n");
        printf("5. Exit\n");
        printf("Enter your choice: ");

        choice = validInput();
        while (choice < 1 || choice > 5)
        {
            printf("Invalid choice! Enter from 1 to 3: ");
            choice = validInput();
        }

        switch (choice)
        {
        case 1:
            bubblesort(arr, n);
            isSorted = 1;
            printf("Array sorted using Bubble Sort\n");
            displaySorted(arr, n);
            break;
        case 2:
            if (!isSorted)
            {
                printf("Array should be sorted!\n");
                break;
            }
            printf("Enter element to search: ");
            key = validInput();
            result = binarysearch(arr, n, key);
            if (result == -1)
                printf("Element not found\n");
            else
                printf("Element found at index %d\n", result);
            break;
        case 3:
            selectionsort(arr, n);
            printf("Array sorted using selection sort");
            displaySorted(arr, n);
            break;

        case 4: 
            insertionsort(arr, n);
            printf("Array sorted using insertion sort");
            displaySorted(arr, n);
            break;


        case 5:
            printf("Exiting program...\n");
            return 0;   
        }
    }
}
