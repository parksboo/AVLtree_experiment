#ifndef AVL_h
#define AVL_h

#include <stdio.h>

typedef struct Node
{
    int code;
    char name[50];
    int mk_capitalization;
    int price;
    int height;
    struct Node *left;
    struct Node *right;
} Node;

int height(Node *N);
int max(int a, int b);

Node *newNode(int code, char *name, int mk_capitalization, int price);
Node *minValueNode(Node *node);
Node *rightRotate(Node *y);
Node *leftRotate(Node *x);
int getBalance(Node *N);
Node *insertNode(Node *node, int code, char name[50], int mk_capitalization, int price);
Node *deleteNode(Node *root, int code);
void freeNode(Node *node);

void findAndPrintNode(Node *root, int code);
#endif /* AVL_h */