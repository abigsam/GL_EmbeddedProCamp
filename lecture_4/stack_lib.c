
#include <stdio.h>
#include <stdlib.h>

#define STACK_INIT      ((int) -1)

//Create stack library based on linked list

//Stack structure
typedef struct stack {
    int value;
    struct stack *next;
    struct stack *prev;
} stack_t;

int create_stack(int value);
int push(int value);
int pop(int *value);
int read(int *value);
//Auxiliary function
void print_list(stack_t *head);

//Pointer to stack-linked list head
static stack_t *head;


/* Main */
int main()
{
    int temp = 0;
    
    //Init stack
    create_stack(STACK_INIT);
    printf("Push value: %d\n", STACK_INIT);
    //Push some values
    for (int cnt = STACK_INIT+1; cnt <= STACK_INIT+10; cnt++) {
        if (push(cnt) != 0) {
            printf("Push failure\n");
            return -1;
        }
        printf("Push value: %d\n", cnt);
    }
    //Print stack
    print_list(head);
    //Read last value
    read(&temp);
    printf("Read last value of the stak: %d\n", temp);
    //Pop values
    for (int cnt = 0; cnt < 4; cnt++) {
        if (pop(&temp) != 0) {
            printf("Pop failure\n");
            return -2;
        }
        printf("Pop value: %d\n", temp);
    }
    //Print stack after pop operations
    print_list(head);
    //Read last value
    read(&temp);
    printf("Read last value of the stak: %d\n", temp);
    
    
    return 0;
}


/**
 * Init & create first element of stack
 * @param   value: value for initial stack element
 * @retval  '0' if success
 */
int create_stack(int value)
{
    stack_t *ptr = malloc(sizeof(stack_t));
    if (ptr != NULL) {
        head = ptr;
        head->value = value;
        head->next = NULL;
        head->prev = NULL;
        return 0; //If malloc success
    }
    return -1; //If malloc faild
}

/**
 * Push value to the stack
 * @param   value: value to push
 * @retval  '0' if success
 */
int push(int value)
{
    stack_t *ptr_head = head;
    stack_t *ptr_new = malloc(sizeof(stack_t));
    /* Check pointers */
    if (ptr_new != NULL && ptr_head != NULL) {
        /* Search for last value */
        while(ptr_head->next != NULL) {
            ptr_head = ptr_head->next;
        }
        /* Init new list element */
        ptr_new->value = value;
        ptr_new->prev = ptr_head;
        ptr_new->next = NULL;
        /* Add new element to the list */
        ptr_head->next = ptr_new;
        return 0; //Success
    }
    return -1; //Fail malloc or head is not inited
}

/**
 * Return last pushed value from the stack and remove this value
 * @param   value: pointer to copy value from the stack
 * @retval  '0' if success
 */
int pop(int *value)
{
    stack_t *ptr_head = head;
    stack_t *ptr_prev;
    if(ptr_head != NULL) {
        /* Search for last value */
        while(ptr_head->next != NULL) {
            ptr_head = ptr_head->next;
        }
        *value = ptr_head->value; //Return last value
        /* Check if previos not NULL -- othervise it first element of stack */
        if ((ptr_prev = ptr_head->prev) != NULL) {
            free(ptr_head); //Kill last element
            ptr_prev->next = NULL; //Make the second last element as last
        }
        return 0; //Success
    }
    return -1; //Head is not inited
}

/**
 * Return value of the last pushed value from the stack; don't remove this value
 * @param   value: pointer to copy value from the stack
 * @retval  '0' if success
 */
int read(int *value)
{
    stack_t *ptr_head = head;
    if(ptr_head != NULL) {
        /* Search for last value */
        while(ptr_head->next != NULL) {
            ptr_head = ptr_head->next;
        }
        *value = ptr_head->value;
        return 0; //Success
    }
    return -1; //Head is not inited
}

/**
 * Print list
 */
void print_list(stack_t *head)
{
    stack_t *ptr = head;
    printf("head(");
    while(ptr->next != NULL) {
        printf("%d)->(", ptr->value);
        ptr = ptr->next;
    }
    printf("%d)\n", ptr->value);
}
