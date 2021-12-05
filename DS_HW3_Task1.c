#include<stdio.h>
#include<stdlib.h>
#include<string.h>

typedef struct huffman_tree_node {
    char letter;
    int frequency;
    struct binary_search_tree_node *left;
    struct binary_search_tree_node *right;
} node;

void swap(char *s1, char *s2);
void sortString(char source[], char dest[]);
node *countFrequency(char source[], node *frequencyQueue);
node *newNode(char letter, int letterFrequency);
void clear(node *root);

int main(void) {
    char src[] = "aadjjcllsl", dest[strlen(src)];
    node *froot = NULL, *cur;

    froot = countFrequency(src, froot);
    cur = froot;
    /*while (cur != NULL) {
        print("(%c, %d)\n", cur->letter, cur->frequency);
        cur = cur->right;
    }*/

    return 0;
}

void swap(char *s1, char *s2){
    char temp;
    temp = *s1;
    *s1 = *s2;
    *s2 = temp;
}

void sortString(char source[], char dest[]) {
    int length = strlen(source);

    strcpy(dest, source);
    for (int i = length; i > 1; i--){
        for (int j = 0; j < i-1; j++){
            if (strcmp(&dest[j+1], &dest[j]) < 0){
                swap(&dest[j+1], &dest[j]);
            }
        }
    }
}

node *countFrequency(char source[], node *frequencyQueue) {
    int length = strlen(source), count = 0;
    char target, dest[length];
    node *cur = frequencyQueue, *input;

    sortString(source, dest);
    target = dest[0];
    for(int i = 0; i < length; i++) {
        if (strcmp(&dest[i], &target) == 0) {
            ++count;
        } else {
            input = newNode(target, count);
            if (frequencyQueue == NULL) {
                frequencyQueue = input;
            } else {

            }
            count = 1;
            target = dest[i];
        }
    }*/

    return frequencyQueue;
}

node *newNode(char letter, int letterFrequency) {
    node *new_node;

    new_node = (node *) malloc(sizeof(node));
    new_node->letter = letter;
    new_node->frequency = letterFrequency;
    new_node->left = NULL;
    new_node->right = NULL;

    return new_node;
}

/*void clear(node *root) {
    if (root != NULL) {
        clear(root->left);
        clear(root->right);
        free(root);
    }
}*/