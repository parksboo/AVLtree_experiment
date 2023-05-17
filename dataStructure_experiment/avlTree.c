#include <stdlib.h>
#include <string.h>
#include "avlTree.h"

int height(Node *N)
{
    if (N == NULL)
        return 0;
    return N->height;
}

int max(int a, int b)
{
    return (a > b) ? a : b;
}

Node *newNode(int code, char *name, int mk_capitalization, int price)
{
    Node *node = (Node *)malloc(sizeof(Node));
    node->code = code;
    strncpy(node->name, name, sizeof(node->name) - 1);
    node->name[sizeof(node->name) - 1] = '\0';
    node->mk_capitalization = mk_capitalization;
    node->price = price;
    node->left = NULL;
    node->right = NULL;
    node->height = 1;
    return (node);
}
Node *minValueNode(Node *node)
{
    Node *current = node;

    /* loop down to find the leftmost leaf */
    while (current->left != NULL)
        current = current->left;

    return current;
}

Node *rightRotate(Node *y)
{
    Node *x = y->left;
    Node *T2 = x->right;
    x->right = y;
    y->left = T2;
    y->height = max(height(y->left), height(y->right)) + 1;
    x->height = max(height(x->left), height(x->right)) + 1;
    return x;
}

Node *leftRotate(Node *x)
{
    Node *y = x->right;
    Node *T2 = y->left;
    y->left = x;
    x->right = T2;
    x->height = max(height(x->left), height(x->right)) + 1;
    y->height = max(height(y->left), height(y->right)) + 1;
    return y;
}

int getBalance(Node *N)
{
    if (N == NULL)
        return 0;
    return height(N->left) - height(N->right);
}

Node *insertNode(Node *node, int code, char name[50], int mk_capitalization, int price)
{
    /* 1. Perform the normal BST rotation */
    if (node == NULL)
        return (newNode(code, name, mk_capitalization, price));

    if (code < node->code)
        node->left = insertNode(node->left, code, name, mk_capitalization, price);
    else if (code > node->code)
        node->right = insertNode(node->right, code, name, mk_capitalization, price);
    else // Equal codes are not allowed in BST
        return node;

    /* 2. Update height of this ancestor node */
    node->height = 1 + max(height(node->left), height(node->right));

    /* 3. Get the balance factor of this ancestor node to check whether
       this node became unbalanced */
    int BF = getBalance(node);

    // If this node becomes unbalanced, then there are 4 cases

    // Left Left Case
    if (BF > 1 && code < node->left->code)
        return rightRotate(node);

    // Left Right Case
    if (BF > 1 && code > node->left->code)
    {
        node->left = leftRotate(node->left);
        return rightRotate(node);
    }

    // Right Right Case
    if (BF < -1 && code > node->right->code)
        return leftRotate(node);

    // Right Left Case
    if (BF < -1 && code < node->right->code)
    {
        node->right = rightRotate(node->right);
        return leftRotate(node);
    }

    /* return the (unchanged) node pointer */
    return node;
}

Node *deleteNode(Node *root, int code)
{
    // Standard BST deletion
    if (root == NULL)
        printf("invalid code : %d\n", code);
    return root;

    if (code < root->code)
        root->left = deleteNode(root->left, code);

    else if (code > root->code)
        root->right = deleteNode(root->right, code);

    else
    {
        // node with only one child or no child
        if ((root->left == NULL) || (root->right == NULL))
        {
            Node *temp = root->left ? root->left : root->right;

            // No child case
            if (temp == NULL)
            {
                temp = root;
                root = NULL;
            }
            else               // One child case
                *root = *temp; // Copy the contents of the non-empty child

            free(temp);
        }
        else
        {
            // node with two children: get the inorder successor (smallest
            // in the right subtree)
            Node *temp = minValueNode(root->right);

            // copy the inorder successor's data to this node
            root->code = temp->code;

            // delete the inorder successor
            root->right = deleteNode(root->right, temp->code);
        }
    }

    // if the tree had only one node then return
    if (root == NULL)
        return root;

    // Update height of the current node
    root->height = 1 + max(height(root->left), height(root->right));

    // Get the balance factor of this node to check whether
    // this node became unbalanced
    int BF = getBalance(root);

    // If this node becomes unbalanced, then there are 4 cases

    // Left Left Case
    if (BF > 1 && getBalance(root->left) >= 0)
        return rightRotate(root);

    // Left Right Case
    if (BF > 1 && getBalance(root->left) < 0)
    {
        root->left = leftRotate(root->left);
        return rightRotate(root);
    }

    // Right Right Case
    if (BF < -1 && getBalance(root->right) <= 0)
        return leftRotate(root);

    // Right Left Case
    if (BF < -1 && getBalance(root->right) > 0)
    {
        root->right = rightRotate(root->right);
        return leftRotate(root);
    }

    return root;
}
void freeNode(Node *node)
{
    if (node != NULL)
    {
        freeNode(node->left);
        freeNode(node->right);
        free(node);
    }
}

void findAndPrintNode(Node *root, int code)
{
    // 노드 검색
    while (root != NULL)
    {
        // 현재 노드의 code가 찾는 code와 일치하면 노드 출력
        if (code == root->code)
        {
            // printf("Code: %d\n", root->code);
            // printf("Name: %s\n", root->name);
            // printf("Market capitalization: %d\n", root->mk_capitalization);
            // printf("Price: %d\n", root->price);
            return; // 일치하는 노드를 찾았으므로 함수 종료
        }

        // 찾는 code가 현재 노드의 code보다 크면 오른쪽 자식으로 이동
        if (code > root->code)
            root = root->right;
        else
            // 그렇지 않으면 왼쪽 자식으로 이동
            root = root->left;
    }

    // 노드를 찾지 못하면 메시지 출력
    printf("No node with code: %d\n", code);
}