#include<stdio.h>
#include<stdlib.h>
#include<string.h>

typedef struct huffman_tree_node {
    char letters[32];
    int frequency;
    char huffmanCode[16];
    struct huffman_tree_node *left;
    struct huffman_tree_node *right;
    struct huffman_tree_node *next;
} node;

void swap(char *character_1, char *character_2);
void sortString(char destination[], char source[]);
node *newNode(char letters[], int frequency);
node *insertNodeAndSort(node *head, node *new_node);
node *buildLetterFrequencyList(char source[]);
node *combineNode(node *left, node *right);
node *copyList2Tree(node *source);
node *buildHuffmanTree(node *head);
void getHuffmanCode(node *huffmanTree, char temp[], int depth, node *head, int *sum);
void encodeString(char source[], char destination[], node *head);
void clearList(node *head);
void clearTree(node *root);

int main(void) {
    char src[256], dst[256] = "", temp[256] = "";
    int depth = 0, sum = 0;
    node *frequency_list = NULL, *huffman_tree = NULL;

    scanf("%s", src);
    frequency_list = buildLetterFrequencyList(src);
    huffman_tree = buildHuffmanTree(frequency_list);
    getHuffmanCode(huffman_tree, temp, depth, frequency_list, &sum);
    encodeString(src, dst, frequency_list);
    printf("> %s\n", dst);
    printf("> %d\n", sum);

    clearList(frequency_list);
    clearTree(huffman_tree);

    return 0;
}

void swap(char *character_1, char *character_2) {
    char temp;
    temp = *character_1;
    *character_1 = *character_2;
    *character_2 = temp;
}

void sortString(char destination[], char source[]) {
    int length = strlen(source);

    strcpy(destination, source);
    for (int i = length; i > 1; i--) {
        for (int j = 0; j < i - 1; j++) {
            if (destination[j + 1] < destination[j]) {
                swap(&destination[j + 1], &destination[j]);
            }
        }
    }
}

node *newNode(char letters[], int frequency) {
    node *new_node;

    new_node = (node *) malloc(sizeof(node));
    strcpy(new_node->letters, letters);
    new_node->frequency = frequency;
    strcpy(new_node->huffmanCode, "");
    new_node->left = NULL;
    new_node->right = NULL;
    new_node->next = NULL;

    return new_node;
}

node *insertNodeAndSort(node *head, node *new_node) {
    node *cur, *prev;

    if (head == NULL) {
        head = new_node;
    } else {
        prev = head;
        cur = prev;
        while (cur != NULL) {
            if (cur->frequency > new_node->frequency) {
                break;
            }
            if (cur->frequency == new_node->frequency && strcmp(cur->letters, new_node->letters) > 0) {
                break;
            }
            prev = cur;
            cur = cur->next;
        }
        if (cur == prev) {
            new_node->next = cur;
            head = new_node;
        } else if (cur == prev->next) {
            prev->next = new_node;
            new_node->next = cur;
        } else {
            prev->next = new_node;
        }
    }

    return head;
}

node *buildLetterFrequencyList(char source[]) {
    int length = strlen(source), count = 0;
    char destination[length], target_letter;
    node *letter_frequency_list = NULL;

    sortString(destination, source);
    target_letter = destination[0];
    for (int i = 0; i < length; i++) {
        if (destination[i] == target_letter) {
            ++count;
        } else {
            letter_frequency_list = insertNodeAndSort(letter_frequency_list, newNode(&target_letter, count));
            count = 1;
            target_letter = destination[i];
        }
    }
    if (count != 0) {
        letter_frequency_list = insertNodeAndSort(letter_frequency_list, newNode(&target_letter, count));
    }

    return letter_frequency_list;
}

node *copyList2Tree(node *source) {
    node *curList = source->next, *cur, *destination = newNode(source->letters, source->frequency);

    cur = destination;
    while (curList != NULL) {
        cur->next = newNode(curList->letters, curList->frequency);
        cur = cur->next;
        curList = curList->next;
    }

    return destination;
}

node *combineNode(node *left, node *right) {
    node *combination;
    char newLetter[32];

    strcpy(newLetter, left->letters);
    strcat(newLetter, right->letters);\
    combination = newNode(newLetter, left->frequency + right->frequency);
    left->next = NULL;
    right->next = NULL;
    combination->left = left;
    combination->right = right;

    return combination;
}

node *buildHuffmanTree(node *head) {
    node *huffmanTree = copyList2Tree(head);
    node *combination, *cur, *next;

    while (huffmanTree->next != NULL) {
        cur = huffmanTree;
        next = huffmanTree->next;
        huffmanTree = next->next;
        combination = combineNode(cur, next);
        huffmanTree = insertNodeAndSort(huffmanTree, combination);
    }

    return huffmanTree;
}

void getHuffmanCode(node *huffmanTree, char temp[], int depth, node *head, int *sum) {
    if (huffmanTree->left) {
        temp[depth] = '0';
        getHuffmanCode(huffmanTree->left, temp, depth+1, head, sum);
    }
    if (huffmanTree->right) {
        temp[depth] = '1';
        getHuffmanCode(huffmanTree->right, temp, depth+1, head, sum);
    }
    if (!(huffmanTree->left) && !(huffmanTree->right)) {
        node *cur = head;
        while (cur != NULL) {
            if (strcmp(cur->letters, huffmanTree->letters) == 0) {
                strcpy(cur->huffmanCode, temp);
            }
            cur = cur->next;
        }
        *sum += depth * huffmanTree->frequency;
        --depth;
    }
}

void encodeString(char source[], char destination[], node *head) {
    int length = strlen(source);
    node *cur;

    for (int i = 0; i < length; i++) {
        cur = head;
        while (cur != NULL) {
            if (cur->letters[0] == source[i]) {
                strcat(destination, cur->huffmanCode);
                break;
            }
            cur = cur->next;
        }
    }
}

void clearList(node *head) {
    node *cur = head->next;

    while (cur != NULL) {
        free(head);
        head = cur;
        cur = cur->next;
    }
}

void clearTree(node *root) {
    if (root != NULL) {
        clearTree(root->left);
        clearTree(root->right);
        free(root);
    }
}