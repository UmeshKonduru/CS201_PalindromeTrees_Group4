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

    return node ? height(node->left) - height(node->right) : 0;
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

    if(root == NULL) return NULL;

    if(root->key == key) return root->edge;

    if(key < root->key) return search(root->left, key);

    if(key > root->key) return search(root->right, key);
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
    } else {
        return;
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

    BST *new_bst = (BST *) malloc(sizeof(BST));

    new_bst->root = NULL;

    return new_bst;
}

Node *searchBST(BST *bst, int key) {

    return search(bst->root, key);
}

void insertBST(BST *bst, int key, Node *edge) {

    insert(&bst->root, createAVLNode(key, edge));
}

struct Node { // single node of an JointEERTREE, represents a palindrome

    int len; // length of the palindrome represented by this node
    BST *edges; // a (balanced) bst of all the edges from this node, lookup is O(log s)
    Node *link; // pointer to the longest proper suffix palindrome of this palindrome
    BST *flag; // flag to check whether is palindrome exists in a given string
};

Node *createNode(int len) {

    Node *new_node = (Node *) malloc(sizeof(Node));

    new_node->len = len;
    new_node->edges = createBST();
    new_node->link = NULL;
    new_node->flag = createBST();

    return new_node;
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

    Node *new_max_suf;

    // find the longest suffix palindrome of the current string preceded by str[i]
    while(eertree->max_suf != eertree->root_odd && str[i] != str[i - eertree->max_suf->len - 1]) eertree->max_suf = eertree->max_suf->link;

    // check whether the longest suffix palindrome of the new string exists, and add it if it doesn't
    new_max_suf = searchBST(eertree->max_suf->edges, str[i]);

    if(new_max_suf) {
        eertree->max_suf = new_max_suf;
        insertBST(new_max_suf->flag, eertree->string_count, NULL);
        return;
    } else {
        eertree->size++;
        new_max_suf = createNode(eertree->max_suf->len + 2);
        insertBST(eertree->max_suf->edges, str[i], new_max_suf);
        printf("%.*s\n", new_max_suf->len, str + i - new_max_suf->len + 1);
    }

    // update the suffix link of the new node
    if(new_max_suf->len == 1) {
        new_max_suf->link = eertree->root_even;
    } else {
        eertree->max_suf = eertree->max_suf->link;
        while(eertree->max_suf != eertree->root_odd && str[i] != str[i - eertree->max_suf->len - 1]) eertree->max_suf = eertree->max_suf->link;
        new_max_suf->link = searchBST(eertree->max_suf->edges, str[i]);
    }

    // update the flag of the new node
    insertBST(new_max_suf->flag, eertree->string_count, NULL);

    // update the max_suf of the JointEERTREE
    eertree->max_suf = new_max_suf;
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
