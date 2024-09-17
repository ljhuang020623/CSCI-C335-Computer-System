#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define STACK_SIZE 30 // The maximum size fo the stack

//Stack structure
typedef struct {
    int data[STACK_SIZE];
    int top;
} Stack;

void initStack(Stack *stack){
    stack->top = -1;
}

void push(Stack *stack, int num){
    if(stack->top < STACK_SIZE - 1){
        stack->data[++(stack->top)] = num;
    }else{
        printf("Stack overflow\n");
    }
}

int pop(Stack *stack){
    if(stack->top >= 0){
        return stack->data[(stack->top)--];
    }else{
        printf("Stack underflow\n");
        return -1;
    }
}

int main(int argc, char *argv[]) {
    Stack stack;
    initStack(&stack);

    for (int i = 1; i < argc; i++) {
        
        char *endptr;
        long num = strtol(argv[i], &endptr, 10); 

        if (*endptr == '\0') {
            push(&stack, (int)num);
        } else {

            int b = pop(&stack);
            int a = pop(&stack);
            int result;

            if(strcmp(argv[i], "add") == 0){
                result = a + b;
            }else if(strcmp(argv[i], "sub") == 0){
                result = a - b;
            }else if(strcmp(argv[i], "mult") == 0){
                result = a * b;
            }else if(strcmp(argv[i], "div") == 0){
                if(b == 0){
                    printf("Division by Zero error\n");
                    exit(EXIT_FAILURE);
                }
                result = a / b;
            } else {
                printf("Unknown operation: %s\n", argv[i]);
                exit(EXIT_FAILURE);
            }
            push(&stack, result);
        }
    }

    printf("%d\n", pop(&stack));
    return 0;
}
