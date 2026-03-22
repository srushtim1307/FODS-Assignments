#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// ---------------- NODE STRUCT ----------------
typedef struct Node {
    int data;
    struct Node *left, *right;
} Node;

// --------- VALID INTEGER INPUT ----------
int validInput(){
    char input[100];
    int x; char extra;
    while(1){
        fgets(input,sizeof(input),stdin);
        if(sscanf(input,"%d %c",&x,&extra)==1) return x;
        printf("Invalid Input! Enter numeric only: ");
    }
}

// ---------------- GLOBAL ROOT --------------
Node *root=NULL;

// ============== CREATE NODE =================
Node* createNode(int value){
    Node* newNode=(Node*)malloc(sizeof(Node));
    newNode->data=value;
    newNode->left=newNode->right=NULL;
    return newNode;
}

// ============== INSERT NODE (BST) ============
void insert(int value){
    Node* newNode=createNode(value);

    if(root==NULL){
        root=newNode;
        printf("Inserted %d as ROOT\n",value);
        return;
    }

    Node *curr=root,*parent=NULL;    /* curr → moves through tree 
                                     parent → remembers previous node (so we know where to insert)*/

    while(curr!=NULL){
        parent=curr;

        if(value < curr->data)
            curr = curr->left;
        else if(value > curr->data)
            curr = curr->right;
        else {
            printf("Duplicate values not allowed!\n");
            free(newNode);
            return;
        }
    }

    if(value < parent->data)
        parent->left=newNode;
    else
        parent->right=newNode;

    printf("Inserted %d successfully.\n",value);
}


// ============== SEARCH NODE (BST ITERATIVE) ==========
Node* searchNode(int key){
    Node *temp=root;
    while(temp!=NULL){
        if(key==temp->data) return temp;
        else if(key<temp->data) temp=temp->left;
        else temp=temp->right;
    }
    return NULL;
}

void searchValue(int val){
    printf(searchNode(val)? "\nFound!\n":"\nNot Found!\n");
}

// ==============UPDATE NODE=================
void updateNode(int old,int new){
    Node* n=searchNode(old);
    if(n){
        n->data=new;
        printf("Updated %d -> %d\n",old,new);
    }else printf("Node Not Found\n");
}


// ==============DELETE NODE(BST, ITERATIVE)==========
void deleteNode(int key){
    Node *parent=NULL,*curr=root;

    while(curr && curr->data!=key){
        parent=curr;
        if(key<curr->data) curr=curr->left;
        else curr=curr->right;
    }

    if(!curr){ printf("Node Not Found\n"); return; }

    // Case 1: One or Zero child
    if(curr->left==NULL || curr->right==NULL){
        Node *child = NULL;

        if(curr->left != NULL)
        child = curr->left;
        else
        child = curr->right;
        
        if(parent==NULL) root=child;         // deleting root case
        else if(parent->left==curr) parent->left=child;
        else parent->right=child;

        free(curr);
        printf("Deleted %d successfully.\n",key);
        return;
    }

    // Case 2: Two-child → find inorder successor
    Node *succParent=curr,*succ=curr->right;
    while(succ->left){
        succParent=succ;
        succ=succ->left;
    }

    curr->data=succ->data; // replace
    if(succParent->left==succ) succParent->left=succ->right;
    else succParent->right=succ->right;

    free(succ);
    printf("Deleted %d successfully.\n",key);
}


// ---------------- STACK FOR TRAVERSALS ----------------
typedef struct{
    Node* arr[100];
    int top;
}Stack;

void push(Stack*s,Node*n){ s->arr[++s->top]=n; }
Node* pop(Stack*s){ return s->arr[s->top--]; }
int empty(Stack*s){ return s->top==-1; }


// ================= INORDER ITERATIVE =================
void inorderI(Node* root){
    Stack st; st.top=-1;
    Node* curr=root;

    while(curr || !empty(&st)){
        while(curr){ push(&st,curr); curr=curr->left; }
        curr=pop(&st);
        printf("%d ",curr->data);
        curr=curr->right;
    }
}

// ================= PREORDER ITERATIVE =================
void preorderI(Node* root){
    if(!root) return;
    Stack st; st.top=-1;
    push(&st,root);

    while(!empty(&st)){
        Node* temp=pop(&st);
        printf("%d ",temp->data);

        if(temp->right) push(&st,temp->right);
        if(temp->left)  push(&st,temp->left);
    }
}

// ================= POSTORDER ITERATIVE =================
void postorderI(Node* root){
    if(!root) return;
    Stack s1={.top=-1}, s2={.top=-1};
    push(&s1,root);

    while(!empty(&s1)){
        Node* temp=pop(&s1);
        push(&s2,temp);
        if(temp->left) push(&s1,temp->left);
        if(temp->right) push(&s1,temp->right);
    }
    while(!empty(&s2)) printf("%d ",pop(&s2)->data);
}


// ----------- LEVEL ORDER USING QUEUE ----------------
typedef struct{
    Node *arr[100];
    int front,rear;
}Queue;

void qPush(Queue*q,Node*n){
    if(q->rear<99){
        if(q->front==-1) q->front=0;
        q->arr[++q->rear]=n;
    }
}
Node* qPop(Queue*q){
    if(q->front==-1) return NULL;
    Node*n=q->arr[q->front];
    if(q->front==q->rear) q->front=q->rear=-1;
    else q->front++;
    return n;
}
int qEmpty(Queue*q){ return q->front==-1; }


// ---------------- DISPLAY ALL TRAVERSALS ----------------
void displayAll(){
    if(!root){ printf("Tree Empty!\n"); return; }

    printf("\nINORDER   : ");  inorderI(root);
    printf("\nPREORDER  : ");  preorderI(root);
    printf("\nPOSTORDER : ");  postorderI(root);

    printf("\nLEVELORDER: ");
    Queue q={.front=-1,.rear=-1};
    qPush(&q,root);
    while(!qEmpty(&q)){
        Node*n=qPop(&q);
        printf("%d ",n->data);
        if(n->left) qPush(&q,n->left);
        if(n->right)qPush(&q,n->right);
    }
    printf("\n");
}


// ================= MAIN MENU =================
int main(){
    while(1){
        printf("\n==== BINARY SEARCH TREE MENU ====\n");
        printf("1.Insert\n2.Delete\n3.Search\n4.Update\n5.Display\n6.Exit\nChoice: ");
        int ch=validInput();

        if(ch==1){ printf("Enter value: "); insert(validInput()); }
        else if(ch==2){ printf("Delete value: "); deleteNode(validInput()); }
        else if(ch==3){ printf("Search value: "); searchValue(validInput()); }
        else if(ch==4){ printf("Old value: "); int o=validInput();
                        printf("New value: "); int n=validInput();
                        updateNode(o,n); }
        else if(ch==5) displayAll();
        else if(ch==6){ printf("Exit...\n"); break; }
        else printf("Invalid!\n");
    }
}
