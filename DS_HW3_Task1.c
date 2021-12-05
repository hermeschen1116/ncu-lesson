#include<stdio.h>
#include<stdlib.h>
#include<string.h>

typedef struct huffman_tree_node {
    char letter[32];
    int frequency;
    struct huffman_tree_node *left;
    struct huffman_tree_node *queueLink;
    struct huffman_tree_node *right;
} node;

void swap(char *s1, char *s2);
void sortString(char source[], char dest[]);
node *createFrequencyQueue(node *frequencyQueue, node *input);
node *countFrequency(char source[], node *frequencyQueue);
node *extractNode(node *ptr);
node *createHuffmanTree(node *frequencyQueue);
node *newNode(char letter[], int letterFrequency);
void clear(node *root);
void inorderTraversal(node *ptr) {
    if (ptr != NULL) {
        inorderTraversal(ptr->left);
        inorderTraversal(ptr->right);
        printf("(%s, %d)\n", ptr->letter, ptr->frequency);
    }
}
void traversal(node *root) {
    node *cur = root;

    while (cur != NULL) {
        printf("(%s, %d)\n", cur->letter, cur->frequency);
        cur = cur->queueLink;
    }
}

int main(void) {
    char src[] = "jggkuhklhlggs", dest[strlen(src)];
    node *froot = NULL, *cur, *htree = NULL;

    froot = countFrequency(src, froot);
    cur = froot;
    htree = createHuffmanTree(froot);
    inorderTraversal(htree);

    return 0;
}

void swap(char *s1, char *s2) {
    char temp;
    temp = *s1;
    *s1 = *s2;
    *s2 = temp;
}

void sortString(char source[], char dest[]) {
    int length = strlen(source);

    strcpy(dest, source);
    for (int i = length; i > 1; i--) {
        for (int j = 0; j < i - 1; j++) {
            if (dest[j + 1] < dest[j]) {
                swap(&dest[j + 1], &dest[j]);
            }
        }
    }
}

node *createFrequencyQueue(node *frequencyQueue, node *input){
    node *cur, *prev;

    if (frequencyQueue == NULL) {
        frequencyQueue = input;
    } else {
        prev = frequencyQueue;
        cur = prev;
        while (cur != NULL) {
            if (cur->frequency > input->frequency) {
                break;
            }
            if (cur->frequency == input->frequency && strcmp(cur->letter, input->letter) > 0) {
                break;
            }
            prev = cur;
            cur = cur->queueLink;
        }
        if (cur == prev) {
            input->queueLink = cur;
            frequencyQueue = input;
        } else if (cur == prev->queueLink) {
            prev->queueLink = input;
            input->queueLink = cur;
        } else {
            prev->queueLink = input;
        }
    }

    return frequencyQueue;
}

node *countFrequency(char source[], node *frequencyQueue) {
    int length = strlen(source), count = 0;
    char target[32], dest[length];

    sortString(source, dest);
    target[0] = dest[0];
    for (int i = 0; i < length; i++) {
        if (dest[i] == target[0]) {
            ++count;
        }
        if (dest[i] != target[0] || i == length-1) {
            frequencyQueue = createFrequencyQueue(frequencyQueue, newNode(target, count));
            count = 1;
            strncpy(target, &dest[i], 1);
        }
    }

    return frequencyQueue;
}

node *extractNode(node *ptr) {
    ptr->queueLink = NULL;

    return ptr;
}

node *huffmanCombination(node *left, node *right) {
    node *combination;
    char newLetter[32];

    strcpy(newLetter, left->letter);
    combination = newNode(strcat(newLetter, right->letter), left->frequency+right->frequency);
    combination->left = extractNode(left);
    combination->right = extractNode(right);

    return combination;
}

node *createHuffmanTree(node *frequencyQueue){
    node *comb, *cur, *next;

    while (frequencyQueue->queueLink != NULL) {
        cur = frequencyQueue;
        next = frequencyQueue->queueLink;
        frequencyQueue = next->queueLink;
        comb = huffmanCombination(cur, next);
        frequencyQueue = createFrequencyQueue(frequencyQueue, comb);
    }

    return frequencyQueue;
}

node *newNode(char letter[], int letterFrequency) {
    node *new_node;

    new_node = (node *) malloc(sizeof(node));
    strcpy(new_node->letter, letter);
    new_node->frequency = letterFrequency;
    new_node->left = NULL;
    new_node->right = NULL;

    return new_node;
}

void clear(node *root) {
    if (root != NULL) {
        clear(root->left);
        clear(root->right);
        free(root);
    }
}