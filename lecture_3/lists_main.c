#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include "list.h"

#define CHECK_ELEMENT   (3)

int main()
{
    list_t *head;
    
    if (list_init(head, 0) < 0) {
        printf("List init error error\n");
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
