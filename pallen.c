// Notation
// s: Size of Alphabet
// n: Size of EERTREE
// The following code uses EERTREE to solve the palindromic length problem
#include<stdlib.h>
#include<stdio.h>
#include<string.h>
typedef struct AVLNode AVLNode;
typedef struct BST BST;
typedef struct Node Node;
typedef struct EERTREE EERTREE;
int max(int a, int b) {

    return a > b ? a : b;
}
int min(int a, int b) {
    return a < b ? a : b;
}
struct AVLNode { 

};
AVLNode *createAVLNode(char key, Node *edge) {

    AVLNode *new_avlnode = (AVLNode *) malloc(sizeof(AVLNode)); 

    new_avlnode->key = key;
    new_avlnode->edge = edge;
    new_avlnode->height = 0;
    new_avlnode->left = new_avlnode->right = NULL;

    return new_avlnode;
}
int height(AVLNode *node) {
    return node ? node->height : -1;
}
int balance(AVLNode *node) {
}
void leftRotate(AVLNode **node) {

    if(*node == NULL) return;

    AVLNode *new_root = (*node)->right;

    // perform rotation
    (*node)->right = new_root->left;
    new_root->left = *node;
    *node = new_root;

    // update heights
    (*node)->left->height = max(height((*node)->left->left), height((*node)->left->right)) + 1;
    (*node)->height = max(height((*node)->left), height((*node)->right)) + 1;
}
void rightRotate(AVLNode **node) {
    if(*node == NULL) return;

    AVLNode *new_root = (*node)->left;

    // perform rotation
    (*node)->left = new_root->right;
    new_root->right = *node;
    *node = new_root;

    // update heights
    (*node)->right->height = max(height((*node)->right->left), height((*node)->right->right)) + 1;
    (*node)->height = max(height((*node)->left), height((*node)->right)) + 1;
}
Node *search(AVLNode *root, char key) {
}
void insert(AVLNode **root, AVLNode *node) {

    if(*root == NULL) {
        *root = node;
        return;
    }

    int bf, lbf, rbf;

    // insert recursively into left or right subtree
    if(node->key < (*root)->key) {
        insert(&(*root)->left, node);
    } else if(node->key > (*root)->key) {
        insert(&(*root)->right, node);
    }

    // update height of root
    (*root)->height = max(height((*root)->left), height((*root)->right)) + 1;

    // balance the tree
    bf = balance(*root);
    lbf = balance((*root)->left);
    rbf = balance((*root)->right);

    if(bf > 1 && lbf >= 0) {
        rightRotate(root);
    } else if(bf > 1 && lbf < 0) {
        leftRotate(&(*root)->left);
        rightRotate(root);
    } else if(bf < -1 && rbf <= 0) {
        leftRotate(root);
    } else if(bf < -1 && rbf > 0) {
        rightRotate(&(*root)->right);
        leftRotate(root);
    }
}
struct BST {
 AVLNode *root;
};
BST *createBST() {
}
Node *searchBST(BST *bst, int key) {

    return search(bst->root, key);
}
void insertBST(BST *bst, int key, Node *edge) {
    insert(&bst->root, createAVLNode(key, edge));
}
struct Node { // single node of an EERTREE, represents a palindrome
};
Node *createNode(int len) {

    Node *new_node = (Node *) malloc(sizeof(Node));

    new_node->len = len;
    new_node->edges = createBST();
    new_node->link = NULL;

    return new_node;
}
struct EERTREE { 
Node *root_even, *root_odd; // Nodes representing empty string and imaginary string respectively
    Node *max_suf; // Node representing the longest suffix palindrome of the current string
    int size; // Number of non-trivial nodes in the EERTREE, i.e., number of palindromes in the current string
};
EERTREE *createEERTREE() {
}
void add(EERTREE *eertree, char *str, int i, int *pal_len) {
}
int palindromicLength(char *str) {
    int n = strlen(str);
    int *pal_len = (int *) malloc(sizeof(int) * n);
    EERTREE *eertree = createEERTREE();

    for(int i = 0; i < n; i++) {
        pal_len[i] = n + 1;
        add(eertree, str, i, pal_len);
    }

    return pal_len[n - 1];
}
void main() {
}
