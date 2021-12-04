#include<stdio.h>
#include<stdlib.h>

typedef struct binary_search_tree_node {
    int data;
    struct binary_search_tree_node *left;
    struct binary_search_tree_node *right;
} node;

node *newNode(int val);
node *insert(node *root, int val);
void preorderTraversal(node *root);
void postorderTraversal(node *root);
void clear(node *root);

int main(void) {
    int num, value;
    node *root = NULL;

    scanf("%d", &num);
    for (int i = 0; i < num; i++) {
        scanf("%d", &value);
        insert(root, value);
    }
    printf("> Preorder:");
    preorderTraversal(root);
    printf("\n");
    printf("> Postorder:");
    postorderTraversal(root);
    printf("\n");

    clear(root);

    return 0;
}

node *newNode(int val) {
    node *new_node;

    new_node = (node *) malloc(sizeof(node));
    new_node->data = val;
    new_node->left = NULL;
    new_node->right = NULL;

    return new_node;
};

node *insert(node *root, int val) {
    node *input = newNode(val);
    node *cur, *parent;

    if (root == NULL) {
        root = input;
    } else {
        cur = root;
        while (cur != NULL) {
            cur = parent;
            if (val < cur->data) {
                cur = cur->left;
            } else {
                cur = cur->right;
            }
        }
        if (val < parent->data) {
            parent->left = input;
        } else {
            parent->right = input;
        }
    }

    return root;
};

void preorderTraversal(node *root) {
    node *cur = root;
    if (cur != NULL) {
        printf(" %d", cur->data);
        preorderTraversal(cur->left);
        preorderTraversal(cur->right);
    }
};

void postorderTraversal(node *root) {
    node *cur = root;
    if (cur != NULL) {
        postorderTraversal(cur->left);
        postorderTraversal(cur->right);
        printf(" %d", cur->data);
    }
};

void clear(node *root) {
    node *cur = root;
    if (cur != NULL) {
        clear(cur->left);
        free(cur);
        clear(cur->right);
    }
};