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
};

BST *createBST() {

}

Node *searchBST(BST *bst, int key) {

    return search(bst->root, key);
}

void insertBST(BST *bst, int key, Node *edge) {
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
};

EERTREE *createEERTREE() {

}

void add(EERTREE *eertree, char *str, int i, int *pal_len) {

    Node *new_max_suf;

    // find the longest suffix palindrome of the current string preceded by str[i]
    while(eertree->max_suf != eertree->root_odd && str[i] != str[i - eertree->max_suf->len - 1]) eertree->max_suf = eertree->max_suf->link;

    // check whether the longest suffix palindrome of the new string exists, and add it if it doesn't
    new_max_suf = searchBST(eertree->max_suf->edges, str[i]);

    if(new_max_suf) {
        eertree->max_suf = new_max_suf;
        return;
    } else {
        eertree->size++;
        new_max_suf = createNode(eertree->max_suf->len + 2);
        insertBST(eertree->max_suf->edges, str[i], new_max_suf);
    }

    // update the suffix link of the new node
    if(new_max_suf->len == 1) {
        new_max_suf->link = eertree->root_even;
    } else {
        eertree->max_suf = eertree->max_suf->link;
        while(eertree->max_suf != eertree->root_odd && str[i] != str[i - eertree->max_suf->len - 1]) eertree->max_suf = eertree->max_suf->link;
        new_max_suf->link = searchBST(eertree->max_suf->edges, str[i]);
    }

    // update diff and series link of the new node
    new_max_suf->diff = new_max_suf->len - new_max_suf->link->len;

    if(new_max_suf->diff == new_max_suf->link->diff) {
        new_max_suf->series_link = new_max_suf->link->series_link;
    } else {
        new_max_suf->series_link = new_max_suf->link;
    }

    // update pal_len
    for(Node *node = new_max_suf; node->len > 0; node = node->series_link) { // iterate through all the leading suffix palindromes
        node->pal_len = pal_len[i - (node->series_link->len + node->diff)] + 1;
        if(node->diff == node->link->diff) node->pal_len = min(node->pal_len, node->link->pal_len);
        pal_len[i] = min(pal_len[i], node->pal_len);
    }

    new_max_suf->pal_len = pal_len[i];

    // update the max_suf of the EERTREE
    eertree->max_suf = new_max_suf;
}

int palindromicLength(char *str) {
}

void main() {

}
