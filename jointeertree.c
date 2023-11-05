// Notation
// s: Size of Alphabet
// n: Size of JointEERTREE
// The following code is an implementation of joint EERTREE, a modificiation of EERTREE
#include<stdlib.h>
#include<stdio.h>
typedef struct AVLNode AVLNode;
typedef struct BST BST;
typedef struct Node Node;
typedef struct JointEERTREE JointEERTREE;
int max(int a, int b) {
    return a > b ? a : b;
}
struct AVLNode { 
char key;
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
    BST *new_bst = (BST *) malloc(sizeof(BST));

    new_bst->root = NULL;

    return new_bst;
}
Node *searchBST(BST *bst, int key) {
}
void insertBST(BST *bst, int key, Node *edge) {

    insert(&bst->root, createAVLNode(key, edge));
}
struct Node { 
// single node of an JointEERTREE, represents a palindrome

    int len; // length of the palindrome represented by this node
    BST *edges; // a (balanced) bst of all the edges from this node, lookup is O(log s)
    Node *link; // pointer to the longest proper suffix palindrome of this palindrome
    BST *flag; // flag to check whether is palindrome exists in a given string
};
Node *createNode(int len) {

}
struct JointEERTREE { 

    Node *root_even, *root_odd; // Nodes representing empty string and imaginary string respectively
    Node *max_suf; // Node representing the longest suffix palindrome of the current string
    int size; // Number of non-trivial nodes in the JointEERTREE, i.e., number of palindromes in the current string
    int string_count; // Number of strings in the JointEERTREE 
};
JointEERTREE *createEERTREE() {
    JointEERTREE *new_eertree = (JointEERTREE *) malloc(sizeof(JointEERTREE));

    new_eertree->root_even = createNode(0);
    new_eertree->root_odd = createNode(-1);
    new_eertree->root_even->link = new_eertree->root_odd->link = new_eertree->root_odd; // suffix link of root_even and root_odd is root_odd
    new_eertree->max_suf = new_eertree->root_even;
    new_eertree->size = 0;
    new_eertree->string_count = 0;

    return new_eertree;
}
void add(JointEERTREE *eertree, char *str, int i) {
}
void addString(JointEERTREE *eertree, char *str) {

    eertree->max_suf = eertree->root_even;

    for(int i = 0; str[i] != '\0'; i++) add(eertree, str, i);

    eertree->string_count++;
}
void main() {
    printf("You can test the working of a Joint EERTREE by entering strings below.\n");
    printf("Enter as many strings as you want. Press Q when you are done.\n");
    printf("After entering each string, the program prints the new distinct subpalindromes in the string.\n");
    printf("If you press Q without entering any strings, the program will quit.\n");

    char str[1000000];

    JointEERTREE *eertree = createEERTREE();

    while(1) {
        printf("Enter a string: ");
        scanf("%s", str);
        if(str[0] == 'Q') break;
        addString(eertree, str);
    }
}
