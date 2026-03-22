#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Node {
    int data;
    struct Node *left, *right;
} Node;

Node* createNode(int value){
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->data = value;
    newNode->left = newNode->right = NULL;
    return newNode;
}

int validInput() {
    char input[200]; int x; char c;

    while (1) {
        fgets(input, sizeof(input), stdin);
        if (sscanf(input, "%d %c", &x, &c) == 1) {
            if (x < 0) {
                printf("Invalid Input!.Try again: ");
                continue;
            }
            return x;
        }
        printf("Invalid input! Enter number only: ");
    }
}


typedef struct{
    Node* arr[100];
    int front, rear;
}NodeQueue;

void initQueue(NodeQueue* q){ 
    q->front=q->rear=-1; 
}
int isQueueEmpty(NodeQueue* q){
    if (q->front==-1)
    {
        return 1;
    }
    else{
        return 0;
    } 
}

void enqueue(NodeQueue* q,Node* node){
    if(q->rear==99)return;
    if(q->front==-1) q->front=0;
    q->arr[++q->rear]=node;
}

Node* dequeue(NodeQueue* q){
    if(isQueueEmpty(q)) return NULL;
    Node* temp=q->arr[q->front];
    if(q->front==q->rear) q->front=q->rear=-1;
    else q->front++;
    return temp;
}

typedef struct{
    Node* arr[100];
    int top;
}NodeStack;

void initStack(NodeStack* s){ 
    s->top=-1;
    }
int isStackEmpty(NodeStack* s){
     return s->top==-1; 
    }
void push(NodeStack* s,Node* node){
     if(s->top<99) s->arr[++s->top]=node;
    } 
Node* pop(NodeStack* s){ 
    if(isStackEmpty(s)) return NULL; 
    return s->arr[s->top--]; 
    }


Node *root=NULL;

void insert(int value){
    
    Node* newNode=createNode(value);
    
    if(root==NULL){
        root=newNode;
        printf("Inserted %d as ROOT\n",value);
        return;
    }

    NodeQueue q; 
    initQueue(&q);  
    enqueue(&q,root);

    while(!isQueueEmpty(&q)){
        Node* temp=dequeue(&q);

        if(temp->left==NULL){
            temp->left=newNode;
            printf("Inserted %d LEFT of %d\n",value,temp->data);
            return;
        }
        enqueue(&q,temp->left);
    
        if(temp->right==NULL){
            temp->right=newNode;
            printf("Inserted %d RIGHT of %d\n",value,temp->data);
            return;
        }
        enqueue(&q,temp->right);
    }
}

Node* search(Node* node,int key){

    if(key < 0){ 
    printf("Negative values are not allowed!\n");
    return NULL;
}

    if(node==NULL)
    return NULL;

    NodeQueue q;
    initQueue(&q);
    enqueue(&q,node);

    while(!isQueueEmpty(&q)){
        Node* temp=dequeue(&q);
        if(temp->data==key) return temp;

        if(temp->left) 
        enqueue(&q,temp->left);
        if(temp->right)
        enqueue(&q,temp->right);
    }
    return NULL;
}

void searchValue(int val){
    Node* result = search(root, val);

    if(result == NULL){
        printf("Not Found!\n");
    }
    else{
        printf("Found!\n");
    }
}


void updateNode(int old,int new){
    if(old < 0 || new < 0){ 
    printf("Negative values are not allowed!\n"); 
    return; 
}

    Node* n = search(root, old);
if(n != NULL){
    // if(new != old && search(root, new) != NULL){
    //     printf("Update failed: value already exists!\n");
    //     return;
    // }
    n->data = new;
    printf("Updated %d to %d\n", old, new);
}
else printf("Node Not Found\n");
}


void deleteNode(int key){
    if(key < 0){ 
    printf("Negative values are not allowed!\n"); 
    return; 
}

    if(root==NULL){ printf("Tree Empty!\n"); return; }

    if(root->left==NULL && root->right==NULL){
        if(root->data==key){
            free(root); root=NULL;
            printf("Deleted %d\n",key);
        } else printf("Not Found\n");
        return;
    }

    NodeQueue q; initQueue(&q);
    enqueue(&q,root);

    Node *temp=NULL,*keyNode=NULL,*last=NULL,*parent=NULL;

  while (!isQueueEmpty(&q)) {
    temp = dequeue(&q);

    if (temp->data == key)
        keyNode = temp;

    if (temp->left) {
        enqueue(&q, temp->left);
        parent = temp;
        last = temp->left;
    }
    if (temp->right) {
        enqueue(&q, temp->right);
        parent = temp;
        last = temp->right;
    }
}


    if(keyNode && last){
        keyNode->data=last->data;
        if(parent->right==last) parent->right=NULL;
        else parent->left=NULL;
        free(last);
        printf("Deleted %d SUCCESSFULLY\n",key);
    } else printf("Node Not Found\n");
}

void inorderI(Node* root){
    NodeStack st; initStack(&st);
    Node* curr=root;

    while(curr || !isStackEmpty(&st)){
        while(curr!=NULL){
             push(&st,curr); 
             curr=curr->left;
             }
        curr=pop(&st);
        printf("%d ",curr->data);
        curr=curr->right;
    }
}

void preorderI(Node* root){
    if(!root) return;
    NodeStack st; initStack(&st);
    push(&st,root);

    while(!isStackEmpty(&st)){
        Node* temp=pop(&st);
        printf("%d ",temp->data);
        if(temp->right) push(&st,temp->right);
        if(temp->left)  push(&st,temp->left);
    }
}

void postorderI(Node* root){
    if(!root) return;
    NodeStack s1,s2; initStack(&s1); initStack(&s2);
    push(&s1,root);

    while(!isStackEmpty(&s1)){
        Node* n=pop(&s1);
        push(&s2,n);
        if(n->left) push(&s1,n->left);
        if(n->right) push(&s1,n->right);
    }
    while(!isStackEmpty(&s2))
        printf("%d ", pop(&s2)->data);
}

void displayAll(){
    if(root==NULL){ printf("\nTree Empty\n"); return;}

    printf("\nInorder   : ");  inorderI(root);
    printf("\nPreorder  : ");  preorderI(root);
    printf("\nPostorder : ");  postorderI(root);

    printf("\nLEVELORDER: ");
    NodeQueue q; initQueue(&q); enqueue(&q,root);
    while(!isQueueEmpty(&q)){
        Node* n=dequeue(&q);
        printf("%d ",n->data);
        if(n->left) enqueue(&q,n->left);
        if(n->right)enqueue(&q,n->right);
    }
    printf("\n");
}

void freeTree(Node* root) {
    if (!root) return;
    freeTree(root->left);
    freeTree(root->right);
    free(root);
}


int main(){
    while(1){
        printf("\nBINARY TREE MENU\n");
        printf("1.Insert\n2.Delete\n3.Search\n4.Update\n5.Display\n6.Exit\nChoice: ");
        int ch=validInput();

        if(ch==1){
            printf("Enter value: "); insert(validInput());
        }
        else if(ch==2){
            printf("Delete value: "); deleteNode(validInput());
        }
        else if(ch==3){
            printf("Search value: "); searchValue(validInput());
        }
        else if(ch==4){
            printf("Old value: "); int o=validInput();
            printf("New value: "); int n=validInput();
            updateNode(o,n);
        }
        else if(ch==5) displayAll();

        else if(ch==6){ 
            freeTree(root);     
        printf("Exit...\n");
        break;
     }
        else printf("Invalid!\n");
    }
}
