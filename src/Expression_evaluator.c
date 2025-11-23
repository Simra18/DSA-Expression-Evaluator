#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>
#include <stdbool.h>

#define MAX_SIZE 100

// ------- Generic Stack for Integers -------
typedef struct {
    int data[MAX_SIZE];
    int top;
} Stack;

void initStack(Stack *s) { s->top = -1; }
bool isEmpty(Stack *s) { return s->top == -1; }
bool isFull(Stack *s) { return s->top == MAX_SIZE - 1; }
void push(Stack *s, int val) {
    if (isFull(s)) { printf("Stack Overflow\n"); return; }
    s->data[++s->top] = val;
}
int pop(Stack *s) {
    if (isEmpty(s)) { printf("Stack Underflow\n"); exit(EXIT_FAILURE); }
    return s->data[s->top--];
}
int peek(Stack *s) { return s->data[s->top]; }

// ------- Stack for Operators (Strings) for Infix -------
typedef struct {
    char ops[MAX_SIZE][MAX_SIZE];
    int top;
} OpStack;

void initOpStack(OpStack *s) { s->top = -1; }
bool isEmptyOp(OpStack *s) { return s->top == -1; }
void pushOp(OpStack *s, const char *op) {
    strcpy(s->ops[++s->top], op);
}
char* popOp(OpStack *s) {
    if (isEmptyOp(s)) { printf("Op Stack Underflow\n"); exit(EXIT_FAILURE); }
    return s->ops[s->top--];
}
char* peekOp(OpStack *s) {
    if (isEmptyOp(s)) return NULL;
    return s->ops[s->top];
}

// -------- Operator Utilities --------
int precedence(const char *op) {
    if (!op) return 0;
    if (strcmp(op, "+") == 0 || strcmp(op, "-") == 0)
        return 1;
    if (strcmp(op, "*") == 0 || strcmp(op, "/") == 0)
        return 2;
    if (strcmp(op, "^") == 0)
        return 3;
    return 0;
}
bool isRightAssociative(const char *op) {
    return strcmp(op, "^") == 0;
}
bool isNumber(const char *str) {
    int i = (str[0] == '-') ? 1 : 0;
    if (i == 1 && strlen(str) == 1) return false;
    for (; str[i]; ++i)
        if (!isdigit((unsigned char)str[i])) return false;
    return *str;
}
// Utility for floor division
int floorDiv(int a, int b) {
    if (a * b < 0 && a % b != 0) return (a / b) - 1;
    return a / b;
}

// -------- Infix Evaluator --------
int applyOp(int a, int b, const char *op) {
    if (strcmp(op, "+") == 0) return a + b;
    if (strcmp(op, "-") == 0) return a - b;
    if (strcmp(op, "*") == 0) return a * b;
    if (strcmp(op, "/") == 0) return floorDiv(a, b);
    if (strcmp(op, "^") == 0) return (int)pow(a, b);
    return 0;
}
int evaluateInfix(char *expr[], int n) {
    Stack values;
    OpStack ops;
    initStack(&values);
    initOpStack(&ops);
    for (int i = 0; i < n; i++) {
        if (isNumber(expr[i])) {
            push(&values, atoi(expr[i]));
        } else {
            while (!isEmptyOp(&ops) &&
                (precedence(peekOp(&ops)) > precedence(expr[i]) ||
                (precedence(peekOp(&ops)) == precedence(expr[i]) && !isRightAssociative(expr[i])))) {
                int b = pop(&values);
                int a = pop(&values);
                char* op = popOp(&ops);
                push(&values, applyOp(a, b, op));
            }
            pushOp(&ops, expr[i]);
        }
    }
    while (!isEmptyOp(&ops)) {
        int b = pop(&values);
        int a = pop(&values);
        char* op = popOp(&ops);
        push(&values, applyOp(a, b, op));
    }
    return peek(&values);
}

// -------- Postfix Evaluator --------
int evaluatePostfix(const char *exp) {
    Stack s;
    initStack(&s);
    char token[MAX_SIZE], *ptr;
    int i = 0;
    while (exp[i]) {
        if (isspace(exp[i])) { i++; continue; }
        if (isdigit(exp[i]) || (exp[i] == '-' && isdigit(exp[i+1]))) {
            int j = 0;
            if (exp[i] == '-') token[j++] = exp[i++];
            while (isdigit(exp[i])) token[j++] = exp[i++];
            token[j] = '\0';
            push(&s, atoi(token));
        } else {
            int val2 = pop(&s), val1 = pop(&s), result = 0;
            switch (exp[i]) {
                case '+': result = val1 + val2; break;
                case '-': result = val1 - val2; break;
                case '*': result = val1 * val2; break;
                case '/': result = floorDiv(val1, val2); break;
                case '^': result = (int)pow(val1, val2); break;
            }
            push(&s, result);
            i++;
        }
    }
    return pop(&s);
}

// -------- Prefix Evaluator --------
int evaluatePrefix(char *arr[], int n) {
    Stack st;
    initStack(&st);
    for (int i = n - 1; i >= 0; i--) {
        if (isNumber(arr[i])) {
            push(&st, atoi(arr[i]));
        } else {
            int val1 = pop(&st), val2 = pop(&st), result = 0;
            if (strcmp(arr[i], "+") == 0) result = val1 + val2;
            else if (strcmp(arr[i], "-") == 0) result = val1 - val2;
            else if (strcmp(arr[i], "*") == 0) result = val1 * val2;
            else if (strcmp(arr[i], "/") == 0) result = floorDiv(val1, val2);
            else if (strcmp(arr[i], "^") == 0) result = (int)pow(val1, val2);
            push(&st, result);
        }
    }
    return pop(&st);
}

int main() {
    // Infix expression
    char* infixArr[] = {"100", "+", "200", "/", "2", "*", "5", "+", "7"};
    int infixLen = sizeof(infixArr) / sizeof(infixArr[0]);
    printf("Infix Result: %d\n", evaluateInfix(infixArr, infixLen));

    // Postfix expression: "100 200 2 / 5 * + 7 +"
    char postfixExp[] = "100 200 2 / 5 * + 7 +";
    printf("Postfix Result: %d\n", evaluatePostfix(postfixExp));

    // Prefix expression: "+ * / + 100 200 2 5 7"
    // Equivalent array: {"+", "*", "/", "+", "100", "200", "2", "5", "7"}
    char* prefixArr[] = {"+", "*", "/", "+", "100", "200", "2", "5", "7"};
    int prefixLen = sizeof(prefixArr) / sizeof(prefixArr[0]);
    printf("Prefix Result: %d\n", evaluatePrefix(prefixArr, prefixLen));
    
    return 0;
}
