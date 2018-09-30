
#include <stdio.h>

#define ASSERT_OPERATION(c)     ( ('*' == c) || ('/' == c) || ('+' == c) || ('-' == c))

//Create function, that receives pointer to other function as a parameter
int arithmetic(int a, int b, int (*func_ptr)(int, int));

/* Make function for tests */
int add(int a, int b) { return (a+b); }
int sub(int a, int b) { return (a-b); }
int mul(int a, int b) { return (a*b); }
int division(int a, int b) { return (a/b); }

/* Main */
int main()
{
    int (*f_ptr)(int, int);
    int op_a = 0, op_b = 0;
    char operation[2] = {' '};
    
    for (;;) {
        /* Input operation char */
        printf("Input operation ('*', '/', '-', '+' or other char for exit): ");
        scanf("%s", operation);
        /* Check for valid operation char, if not -- exit "for" */
        if (!ASSERT_OPERATION(operation[0])) { break; }
        
        /* Input operands */
        printf("Input A (integer): ");
        scanf("%d", &op_a);
        printf("Input B (integer): ");
        scanf("%d", &op_b);
        
        /* Choose operation */
        switch(operation[0]) {
            case '+':
                f_ptr = &add;
            break;
                
            case '-':
                f_ptr = &sub;
            break;
            
            case '/':
                f_ptr = &division;
            break;
            
            case '*':
                f_ptr = &mul;
            break;
            
            default:
                return -1;
        }
        
        /* Perform operation and print it */
        printf("%d %c %d = %d\n", op_a, operation[0], op_b, arithmetic(op_a, op_b, f_ptr));
    }
    printf("\nProgram exit succees");
    return 0;
}


/**
 * Receive two parameters and pointer to function and
 * return result of this function
 * @param   a: integer value
 * @param   b: integre value
 * @param   func_ptr: pointer to function that receiv two
 *          integers and return integer
 * @retval  Integer value
 */
int arithmetic(int a, int b, int (*func_ptr)(int, int))
{
    return ( (*func_ptr)(a, b) ); //Just return result of pointed function
}
