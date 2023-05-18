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

    // 가장 작은 node 찾기
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
    // 재귀적으로 값 insertion
    if (node == NULL)
        return (newNode(code, name, mk_capitalization, price));

    if (code < node->code)
        node->left = insertNode(node->left, code, name, mk_capitalization, price);
    else if (code > node->code)
        node->right = insertNode(node->right, code, name, mk_capitalization, price);
    else
        return node;

    node->height = 1 + max(height(node->left), height(node->right));

    int BF = getBalance(node);

    // balance 재조정

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
        // child node < 2
        if ((root->left == NULL) || (root->right == NULL))
        {
            Node *temp = root->left ? root->left : root->right;

            if (temp == NULL)
            {
                temp = root;
                root = NULL;
            }
            else
                // node 당겨오기
                *root = *temp;

            free(temp);
        }
        else
        {
            // left right 모두 있는 경우
            Node *temp = minValueNode(root->right);

            root->code = temp->code;
            root->mk_capitalization = temp->mk_capitalization;
            root->price = temp->price;

            // delete the inorder successor
            root->right = deleteNode(root->right, temp->code);
        }
    }

    // 빈트리가 되었는지 확인
    if (root == NULL)
        return root;

    // height 갱신
    root->height = 1 + max(height(root->left), height(root->right));

    int BF = getBalance(root);

    // balance 재조정

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
// 할당되었던 메모리를 반환하는 함수
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
            // 찾은 node를 출력하고 싶을 때 활성화
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
    printf("couldn't find code: %d\n", code);
}