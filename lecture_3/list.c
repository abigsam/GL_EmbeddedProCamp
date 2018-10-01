

#include "list.h"


/**
 * Ini list with first value
 * @param   head: pointer to the list header
 * @param   value: value of new element
 * @retval  0 if success, if -1 memory allocation error
 */
int list_init(list_t *head, int value)
{
    list_t *ptr = malloc(sizeof(list_t));
    if (NULL == ptr) {
        return -1;
    }
    ptr->value = value;
    ptr->next = NULL;
    return 0;
}

/**
 * Add element to list
 * @param   head: pointer to the list header
 * @param   value: value of new element
 * @retval  0 if success, if -1 memory allocation error
 */
int list_add(list_t *head, int value)
{
    list_t *ptr = head;
    list_t *ptrnew;
    while(ptr->next != NULL) {
        ptr = ptr->next;
    }
    ptrnew = malloc(sizeof(list_t));
    if (NULL == ptrnew) {
        return -1;
    }
    ptr->next = ptrnew;
    ptr->next->value = value;
    ptr->next->next = NULL;
    return 0;
}

/**
 * Remove element to list
 * @param   head: pointer to the list header
 * @param   value: element value
 * @retval  0 if success; -1 if element didn't find
 */
int list_remove(list_t *head, int value)
{
    list_t *ptr = head;
    list_t *ptr_delet;
    //while(ptr->next != NULL) {
    for(;;) {
        if (ptr->value == value) {
            ptr->value = ptr->next->value;
            ptr_delet = ptr->next;
            ptr->next = ptr_delet->next;
            free(ptr_delet);
            return 0;
        }
        if (ptr->next != NULL) {
            ptr = ptr->next;
        }
        else {
            return -1; //Reached last element, element didn't find
        }
    }
}

/**
 * Checking list for specified value
 * @param   head: pointer to the list header
 * @param   value: element value
 * @retval  1 if element exists, else return 0
 */
int list_is(list_t *head, int val)
{
    list_t *ptr = head;
    while(ptr->next != NULL) {
        if (ptr->value == val) {
            return 1; //Is list with specified value
        }
        ptr = ptr->next;
    }
    return 0; //List didn't find
}

void print_list(list_t *head)
{
    list_t *ptr = head;
    printf("head(");
    while(ptr->next != NULL) {
        printf("%d)->(", ptr->value);
        ptr = ptr->next;
    }
    printf("%d)\n", ptr->value);
}
