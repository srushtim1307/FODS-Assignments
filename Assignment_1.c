#include<stdio.h>
#include<stdlib.h>
#include<time.h>

#define SIZE 1000
#define NUMBERS 10

int main(){
    int arr[SIZE];
    int max=0, current=0, maxIndex=0;

srand(time(NULL));

    for (int i = 0; i < SIZE; i++)
    {
        arr[i]=rand();
    }
    
    for (int i = 0; i <NUMBERS; i++)
    {
        current+=arr[i];
    }
    max=current;

    for (int i = 1; i <= SIZE-NUMBERS; i++){
    current=current-arr[i-1]+arr[i+NUMBERS-1];
        if(current>max){
            max=current;
            maxIndex = i;
        }
        
    }

    printf("The maximum sum is %d \n", max);
    printf("The 10 numbers are: ");
    for (int i = maxIndex; i < maxIndex+NUMBERS; i++)
    {
        printf("%d ",arr[i]);
    }
    printf("\n");
    printf("The index of first element is %d",maxIndex);
    
    return 0;
    
}