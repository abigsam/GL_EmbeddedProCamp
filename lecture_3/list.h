

#ifndef __LIST_H
#define __LIST_H

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>


/* List definition */
typedef struct list {
    int value;
    struct list *next;
} list_t;

int list_add(list_t *head, int value);
int list_remove(list_t *head, int value);
int list_is(list_t *head, int val);

void print_list(list_t *head);


#endif