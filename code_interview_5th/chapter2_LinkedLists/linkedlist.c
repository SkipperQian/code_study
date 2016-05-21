#include <stdio.h>
#include <stdlib.h>
#include "linkedlists.h"

struct list_node * creat_list(int num[], int size)
{
    int i = 0;
    struct list_node *list = NULL;
    struct list_node *lastnode = NULL;

    for (i = 0; i < size; i++) {
        struct list_node *newnode = NULL;
        newnode = (struct list_node *)malloc(sizeof(struct list_node));

        newnode->item = num[i];
        newnode->next = NULL;
        if (i == 0) {
            list = newnode;
        }
        else {
            lastnode->next = newnode;
        }
        lastnode = newnode;
    }

    return list;
}

void display_list(struct list_node *node)
{
    while (node) {
        printf("%d ", node->item);
        node = node->next;
        if (node == NULL)
            printf("\n");
    }
}
