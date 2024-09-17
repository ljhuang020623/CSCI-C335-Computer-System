#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 100

// Stack structure
typedef struct{
    int data[MAX];
    int top;
} Stack;

// Function prototypes
void initStack(Stack *stack);
void push(Stack *stack, int num);
int pop(Stack *stack);
int parseBinary(const char *str);
int parseHex(const char *str);
int parseDecimal(const char *str);


int main(int argc, char *argv[]){
    Stack stack;
    initStack(&stack);

    for(int i = 1; i < argc; i++){

        int num = 0;
        // Compare the first two charecters to check if it is base 2
        if(strncmp(argv[i], "0b", 2) == 0){
            num = parseBinary(argv[i]);
        } else if(strncmp(argv[i], "0x", 2) == 0){
            num = parseHex(argv[i]);
        } else {
            num = parseDecimal(argv[i]);
        }

        if(num != -1){
            push(&stack, num);
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

// Stack operations
void initStack(Stack *stack){
    stack -> top = -1;
}

void push(Stack *stack, int num){
    if(stack -> top < MAX - 1){
        stack -> data[++(stack -> top)] = num;
    } else {
        printf("Stack Overflow\n");
    }
}

int pop(Stack *stack){
    if(stack -> top >= 0){
         return stack -> data[(stack -> top)--];
    } else {
        printf("Stack Underflow\n");
        return -1;
    }
}

// Parse strings
int parseBinary(const char *str){
    int result = 0;

    for(int i = 2; str[i] != '\0'; i++){
        if(str[i] != '0' && str[i] != '1'){
            return -1;
        } 
        result = result * 2 + (str[i] - '0');
    }
    return result;
}

int parseHex(const char *str){
    int result = 0;

    for(int i = 2; str[i] != '\0'; i++){
        char c = str[i];
        int value = 0;
        if(c >= '0' && c <= '9'){
            value = c - '0';
        } else if (c >= 'a' && c <= 'f'){
            value = c - 'a' + 10;
        } else {
            return -1;
        }
        result = result * 16 + value;
    }
    return result;
}

int parseDecimal(const char *str){
    int result = 0;

    for(int i = 0; str[i] != '\0'; i ++){
        if(!(str[i] >= '0' && str[i] <= '9')){
            return -1;
        }
        result = result * 10 + (str[i] - '0');
    }
    return result ;
}

