#include<stdio.h>
#include<stdlib.h>

typedef struct node{
    int data;
    struct node *next;
} node;

node *newNode();
node *enqueue(node *front, int *total, int val);
node *dequeue(node *front, int *total);
void show(node *front, int total, int index);
void clear(node *front);

int main(void) {
    int opt, val, total = 0, flag = 0;
    node *front = NULL;

    while (opt != -1) {
        scanf("%d", &opt);
        if (opt == -1) {
            break;
        }
        switch (opt) {
            case 1 :
                scanf("%d", &val);
                if (0 < val && val <= 10) {
                    front = enqueue(front, &total, val);
                } else {
                    printf("invalid input\n");
                }
                break;
            case 2 :
                if (flag == 0) {
                    printf(">");
                    flag = 1;
                }
                show(front, total, 0);
                break;
            case 3 :
                if (flag == 0) {
                    printf(">");
                    flag = 1;
                }
                front = dequeue(front, &total);
        }
    }
    if (flag == 0) {
        printf(">");
        flag = 1;
    }
    clear(front);

    return 0;
}

node *newNode(){
    node *_node_;

    _node_ = (node*)malloc(sizeof(node));
    if(_node_ == NULL)
    {
        printf("out of memory\n");
        exit(1);
    }

    _node_->next = NULL;

    return _node_;
};

node *enqueue(node *front, int *total, int val){
    node *cur = front, *input = newNode();

    input->data = val;
    if (front == NULL) {
        front = input;
    } else {
        while(cur->next != NULL) {
            cur = cur->next;
        }
        cur->next = input;
    }
    ++*total;

    return front;
};

node *dequeue(node *front, int *total){
    node *cur = front;

    if (front == NULL) {
        printf(" -3");
    } else {
        front = front->next;
        free(cur);
        --*total;
    }

    return front;
};

void show(node *front, int total, int index){
    node *cur = front;
    int i = 0;

    if (front == NULL || (0 > index || index >= total)) {
        printf(" -2");
    } else {
        while (cur != NULL) {
            if (i == index) {
                printf(" %d", cur->data);
                break;
            }
            cur = cur->next;
            i++;
        }
    }
};

void clear(node *front) {
    node *cur = front;

    while (cur != NULL) {
        front = front->next;
        free(cur);
        cur = front;
    }
};