// Notation
// s: Size of Alphabet
// n: Size of EERTREE
#include<stdlib.h>
#include<stdio.h>
typedef struct AVLNode AVLNode;
typedef struct BST BST;
typedef struct Node Node;
typedef struct EERTREE EERTREE;
int max(int a, int b) {

    return a > b ? a : b;
}
struct AVLNode { 
};
AVLNode *createAVLNode(char key, Node *edge) {
}
int height(AVLNode *node) {

    return node ? node->height : -1;
}
int balance(AVLNode *node) {
}
void leftRotate(AVLNode **node) {
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
}
struct BST {

    AVLNode *root;
};
BST *createBST() {
}
Node *searchBST(BST *bst, int key) {
}
void insertBST(BST *bst, int key, Node *edge) {

    insert(&bst->root, createAVLNode(key, edge));
}
struct Node { // single node of an EERTREE, represents a palindrome
};
Node *createNode(int len) {
}
struct EERTREE { 

    Node *root_even, *root_odd; // Nodes representing empty string and imaginary string respectively
    Node *max_suf; // Node representing the longest suffix palindrome of the current string
    int size; // Number of non-trivial nodes in the EERTREE, i.e., number of palindromes in the current string
};
EERTREE *createEERTREE() {
}
void add(EERTREE *eertree, char *str, int i) {
}
EERTREE *buildEERTREE(char *str) {
}
void main() {  
}
