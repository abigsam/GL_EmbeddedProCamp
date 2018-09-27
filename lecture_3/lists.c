#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#define CHECK_ELEMENT   (3)

/* List definition */
typedef struct list {
    int value;
    struct list *next;
} list_t;

//list_t head = {0, NULL};

int list_add(list_t *head, int value);
int list_remove(list_t *head, int value);
int list_is(list_t *head, int val);

void print_list(list_t *head);

int main()
{
    list_t *head = NULL;
    head = malloc(sizeof(list_t));
    head->value = 0;
    if (NULL == head) {
        printf("Memmory allocation error\n");
        return -1;
    }
    /* Add elements to list */
    for (int cnt = 1; cnt < 10; cnt++) {
        if (list_add(head, cnt) != 0) {
            printf("Add list error\n");
            return -2;
        }
    }
    printf("Added 10 elements to the list:\n");
    print_list(head);
    /* Check if element exists */
    if (list_is(head, CHECK_ELEMENT)) {
        printf("Element %d exist\n", CHECK_ELEMENT);
    }
    else {
        printf("Element %d do not exist\n", CHECK_ELEMENT);
    }
    /* Delete element */
    if (list_remove(head, CHECK_ELEMENT) != 0) {
        printf("Element do not exist\n");
        return -3;
    }
    printf("Delete element with value %d :\n", CHECK_ELEMENT);
    print_list(head);
    /* Check if element exists */
    if (list_is(head, CHECK_ELEMENT)) {
        printf("Element %d exist\n", CHECK_ELEMENT);
    }
    else {
        printf("Element %d do not exist\n", CHECK_ELEMENT);
    }
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
    if (ptrnew != NULL) {
        ptr->next = ptrnew;
        ptr->next->value = value;
        ptr->next->next = NULL;
        return 0;
    }
    return -1;
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
    while(ptr->next != NULL) {
        if (ptr->value == value) {
            ptr->value = ptr->next->value;
            ptr_delet = ptr->next;
            ptr->next = ptr_delet->next;
            free(ptr_delet);
            return 0;
        }
        ptr = ptr->next;
    }
    return -1; //List element didn't find
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


