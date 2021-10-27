#include<stdio.h>
#include<stdlib.h>

typedef struct node {
    int data;
    struct node *next;
} node;

node *newNode(int val);
node *append(node *head, int *total, int val);
void traversal(node *head, int total, int start);
node *inverse(node *head);
void clear(node *head);

int main(void) {
    int val, total = 0, mid;
    node *head = NULL;

    while (scanf("%d", &val) != EOF) {
        head = append(head, &total, val);
    }

    mid = total / 2;
    printf("> ");
    traversal(head, total, mid);
    printf("\n> ");
    head = inverse(head);
    traversal(head, total, 0);

    clear(head);

    return 0;
}

node *newNode(int val){
    node *_node_;

    _node_ = (node*)malloc(sizeof(node));
    if(_node_ == NULL)
    {
        printf("out of memory\n");
        exit(1);
    }

    _node_->data = val;
    _node_->next = NULL;

    return _node_;
};

node *append(node *head, int *total, int val){
    node *cur = head, *input = newNode(val);

    if (head == NULL) {
        head = input;
    } else {
        while(cur->next != NULL) {
            cur = cur->next;
        }
        cur->next = input;
    }
    ++*total;

    return head;
};

void traversal(node *head, int total, int start){
    node *cur = head;
    int i = 0;

    if (head == NULL) {
        printf("List is empty\n");
    } else {
        while (cur->next != NULL) {
            if (cur->next == NULL) {
                break;
            }
            if (i >= start) {
                printf("%d ", cur->data);
            }
            cur = cur->next;
            i++;
        }
        printf("%d", cur->data);
    }
};

node *inverse(node *head){
    node *cur = head, *tmp, *newHead = NULL;

    if (head == NULL) {
        printf("List is empty\n");
    } else {
        while (cur != NULL) {
            tmp = newNode(cur->data);
            if (newHead == NULL) {
                newHead = tmp;
            } else {
                tmp->next = newHead;
                newHead = tmp;
            }
            cur = cur->next;
        }
    }

    return newHead;
};

void clear(node *head) {
    node *cur = head;

    while (cur != NULL) {
        head = head->next;
        free(cur);
        cur = head;
    }
};