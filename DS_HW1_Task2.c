#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>

void toPostfix(char* infix, char* postfix);
int calPostfix(char* postfix);
int priority(char op);

int main(void) {
    char infix[20000], postfix[40000];
    int sum;

    scanf("%s", infix);
    toPostfix(infix, postfix);
    printf(">");
    for (int i = 0; i < strlen(postfix); i++) {
        printf(" %c", postfix[i]);
    }
    sum = calPostfix(postfix);

    printf("\n> %d\n", sum);

    return 0;
}

void toPostfix(char* infix, char* postfix) {
    int length = strlen(infix), top = 0, cnt = 0;
    char operator[length];

    for(int i = 0; i < length; i++) {
        switch (infix[i]) {
            case '(' :
                operator[++top] = infix[i];
                break;
            case ')' :
                while(operator[top] != '(') {
                    postfix[cnt++] = operator[top--];
                }
                top--;
                break;
            case '+' :
            case '-' :
            case '*' :
            case '/' :
                while(priority(operator[top]) >= priority(infix[i])) {
                    postfix[cnt++] = operator[top--];
                }
                operator[++top] = infix[i]; // 存入堆疊
                break;
            default :
                postfix[cnt++] = infix[i];
        }
    }
    while(top > 0) {
        postfix[cnt++] = operator[top--];
    }
};

int calPostfix(char* postfix) {
    int length = strlen(postfix), top = 0;
    double operand[length];

    for (int i = 0; i < length; i++) {
        switch (postfix[i]) {
            case '+' :
                operand[top-2] += operand[top-1];
                top--;
                break;
            case '-' :
                operand[top-2] -= operand[top-1];
                top--;
                break;
            case '*' :
                operand[top-2] *= operand[top-1];
                top--;
                break;
            case '/' :
                operand[top-2] /= operand[top-1];
                top--;
                break;
            default :
                operand[top++] = ((int)postfix[i] - 48) / 1.0;
        }
    }

    return (int)round(operand[0]);
};

int priority(char op) {
    switch(op) {
        case '+':
        case '-':
            return 1;
        case '*':
        case '/':
            return 2;
        default:
            return 0;
    }
}