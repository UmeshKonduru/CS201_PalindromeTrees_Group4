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
struct AVLNode { char key;
    Node *edge;
    int height;
    AVLNode *left, *right;
};
AVLNode *createAVLNode(char key, Node *edge) {
}
int height(AVLNode *node) {

    return node ? node->height : -1;
}
int balance(AVLNode *node) {
    return node ? height(node->left) - height(node->right) : 0;
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
    if(root == NULL) return NULL;

    if(root->key == key) return root->edge;

    if(key < root->key) return search(root->left, key);

    if(key > root->key) return search(root->right, key);
}
void insert(AVLNode **root, AVLNode *node) {
}
struct BST {

    AVLNode *root;
};
BST *createBST() {
}
Node *searchBST(BST *bst, int key) {
    AVLNode *root;
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
    EERTREE *new_eertree = (EERTREE *) malloc(sizeof(EERTREE));

    new_eertree->root_even = createNode(0);
    new_eertree->root_odd = createNode(-1);
    new_eertree->root_even->link = new_eertree->root_odd; // suffix link of root_even is root_odd
    new_eertree->root_odd->link = new_eertree->root_odd; // suffix link of root_odd is root_odd
    new_eertree->max_suf = new_eertree->root_even;
    new_eertree->size = 0;

    return new_eertree;
}
void add(EERTREE *eertree, char *str, int i) {
}
EERTREE *buildEERTREE(char *str) {
}
void main() {  
    char *str = (char*) malloc(100 * sizeof(char));
    EERTREE *eertree; 

    while(1) {

        printf("Enter the string: ");
        scanf("%s", str);
        printf("\n");

        eertree = buildEERTREE(str);

        free(str);
        free(eertree);
        printf("\n");
}
