#include<stdio.h>
#include<stdlib.h>
#include<string.h>

void toPostfix(char* infix, char* postfix);
int calPostfix(char* postfix);

int main(void) {
    char infix[10000], postfix[10000];
    int sum;

    scanf("%s", infix);
    toPostfix(infix, postfix);
    sum = calPostfix(postfix);

    printf("> %s\n> %d\n", postfix, sum);

    return 0;
}

void toPostfix(char* infix, char* postfix) {
    int length = strlen(infix), top = 0, cnt = 0;
    char operator[length];

    for(int i = 0; i < length; i++) {
        switch (infix[i]) {
            case '+' :
            case '-' :
            case '*' :
            case '/' :
                operator[top++] = infix[i];
                postfix[cnt++] = ' ';
                break;
            case ')' :
                postfix[cnt++] = ' ';
                for (int j = top-1; j > 0; j--) {
                    if (operator[j] != '(') {
                        top = j;
                        break;
                    }
                }
                postfix[cnt++] = operator[top];
                break;
            case '(' :
                operator[top++] = infix[i];
                break;
            default :
                postfix[cnt++] = infix[i];
        }
    }
};

int calPostfix(char* postfix) {
    int length = strlen(postfix), top = 0;
    int operand[(length+1)/2];

    for (int i = 0; i < length; i++) {
        if (postfix[i] != ' ') {
            switch (postfix[i]) {
                case '+' :
                    operand[top-2] += operand[top-1];
                    top -= 1;
                    break;
                case '-' :
                    operand[top-2] -= operand[top-1];
                    top -= 1;
                    break;
                case '*' :
                    operand[top-2] *= operand[top-1];
                    top -= 1;
                    break;
                case '/' :
                    operand[top-2] /= operand[top-1];
                    top -= 1;
                    break;
                default :
                    operand[top] = (int)postfix[i] - 48;
                    top++;
            }
        }
    }

    return operand[0];
};