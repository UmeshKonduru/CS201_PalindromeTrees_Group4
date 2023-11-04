// Notation
// s: Size of Alphabet
// n: Size of EERTREE

// The following code is an implementation of a modification of EERTREE that makes use of quick links to speed up the add() operation

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

struct Node { 
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
    new_eertree->root_even->link = new_eertree->root_odd->link = new_eertree->root_odd; // suffix link of root_even and root_odd is root_odd
    new_eertree->root_even->quick_link = new_eertree->root_odd->quick_link = new_eertree->root_odd;
    new_eertree->max_suf = new_eertree->root_even;
    new_eertree->size = 0;

    return new_eertree;
}

void add(EERTREE *eertree, char *str, int i) {
}

EERTREE *buildEERTREE(char *str) {

}

void main() {   
}
