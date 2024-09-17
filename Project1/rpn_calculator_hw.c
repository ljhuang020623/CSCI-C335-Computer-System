#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define STACK_SIZE 10

// Stack structure
typedef struct {
    int data[STACK_SIZE];  // Array to store numbers
    int top;               // Tracks the top of the stack
} Stack;

// Function to initialize the stack
void initStack(Stack *stack) {
    stack->top = -1;  // Start with an empty stack
}

// Function to push a number onto the stack
void push(Stack *stack, int num) {
    if (stack->top < STACK_SIZE - 1) {
        stack->data[++(stack->top)] = num;  // Increase top and add the number
    } else {
        printf("Stack overflow\n");
    }
}

// Function to pop a number from the stack
int pop(Stack *stack) {
    if (stack->top >= 0) {
        return stack->data[(stack->top)--];  // Return the top number and decrease top
    } else {
        printf("Stack underflow\n");
        return -1;  // Return an error value
    }
}

// Main function to handle Reverse Polish Notation operations
int main(int argc, char *argv[]) {
    Stack stack;
    initStack(&stack);  // Initialize the stack

    // Loop through all command-line arguments
    for (int i = 1; i < argc; i++) {
        char *endptr;

        //strtol(string to long) converts the string at argv[i] to a long integer 
        //strtol takes 3 arguments:
        //argv[i]: The string to convert
        //&endptr: Pointer to the first character after the number(Used to check if the conversion succeeded)
        //10: The base of the number (decimal)
        long num = strtol(argv[i], &endptr, 10); 

        if (*endptr == '\0') {
            // If successfully converted, it's a number, push it onto the stack
            push(&stack, (int)num);
        } else {
            // If not a number, it must be an operation
            int b = pop(&stack);  // Pop the top two numbers
            int a = pop(&stack);
            int result;

            
            // Perform the appropriate operation
            if (strcmp(argv[i], "add") == 0) {
                result = a + b;
            } else if (strcmp(argv[i], "sub") == 0) {
                result = a - b;
            } else if (strcmp(argv[i], "mult") == 0) {
                result = a * b;
            } else if (strcmp(argv[i], "div") == 0) {
                if (b == 0) {
                    printf("Division by zero error\n");
                    exit(EXIT_FAILURE);
                }
                result = a / b;
            } else {
                printf("Unknown operation: %s\n", argv[i]);
                exit(EXIT_FAILURE);
            }

            // Push the result of the operation back onto the stack
            push(&stack, result);
        }
    }

    // Print the final result from the top of the stack
    printf("Result: %d\n", pop(&stack));

    return 0;
}
