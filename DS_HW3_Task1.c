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
node *newNode(char letter[], int letterFrequency);
node *createFrequencyQueue(node *frequencyQueue, node *input);
node *countFrequency(char source[], node *frequencyQueue);
node *createHuffmanTree(node *frequencyQueue);
//node *huffmanEncode(char letter[], node *huffmanTree);
void clearTree(node *root);
void traversal(node *root) {
    if (root->left) {
        printf("0");
    }
    traversal(root->left);
    if (root->right) {
        printf("1");
    }
    traversal(root->right);
    if (!root->left && !root->right) {
        printf(" %s\n", root->letter);
    }
};

int main(void) {
    char src[128], letter[26] = "";
    node *frequency = NULL, *huffmanTree = NULL, *codeTable = NULL;

    scanf("%s", src);
    frequency = countFrequency(src, frequency);
    huffmanTree = createHuffmanTree(frequency);
    //traversal(huffmanTree);
    /*printf("> ");
    codeTable = huffmanEncode(letter, huffmanTree);
    printf("\n> ");*/

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

node *newNode(char letter[], int letterFrequency) {
    node *new_node;

    new_node = (node *) malloc(sizeof(node));
    strcpy(new_node->letter, letter);
    new_node->frequency = letterFrequency;
    new_node->left = NULL;
    new_node->right = NULL;

    return new_node;
}

node *createFrequencyQueue(node *frequencyQueue, node *input) {
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
        if (dest[i] != target[0]) {
            frequencyQueue = createFrequencyQueue(frequencyQueue, newNode(target, count));
            count = 1;
            strncpy(target, &dest[i], 1);
        }
    }
    if (count != 0) {
        frequencyQueue = createFrequencyQueue(frequencyQueue, newNode(target, count));
    }

    return frequencyQueue;
}

node *huffmanCombination(node *left, node *right) {
    node *combination;
    char newLetter[32];

    strcpy(newLetter, left->letter);
    combination = newNode(strcat(newLetter, right->letter), left->frequency + right->frequency);
    left->queueLink = NULL;
    combination->left = left;
    right->queueLink = NULL;
    combination->right = right;

    return combination;
}

node *createHuffmanTree(node *frequencyQueue) {
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


node *huffmanEncode(char letter[], node *huffmanTree) {
    int length = strlen(letter);
    node *cur, *code = NULL;

    for (int i = 0; i < length; i++) {
        cur = huffmanTree;
        while (strcmp(&letter[i], cur->letter) != 0) {
            if (strstr(cur->left->letter, &letter[i]) != NULL) {
                printf("0");
                cur = cur->left;
            } else {
                printf("1");
                cur = cur->right;
            }
        }
    }

    return code;
}

void clearTree(node *root) {
    if (root != NULL) {
        clearTree(root->left);
        clearTree(root->right);
        free(root);
    }
}