/*
 * Implement an algorithm to delete a node in the middle of a single linked list, 
 * given only access to that node.
 * EXAMPLE:
 * Input: the node ‘c’ from the linked list a->b->c->d->e 
 * Result: nothing is returned, but the new linked list looks like a->b->d->e
 */

#include <stdio.h>
#include <stdlib.h>
#include "linkedlists.h"

int delete_node(struct list_node *node)
{
    if (node == NULL || node->next == NULL)
        return -1;

    struct list_node *p = node->next;

    node->item = p->item;
    node->next = p->next;
    free(p);

    return 0;
}

int main(int argc, char const *argv[])
{
    int array[10] = {7, 4, 1, 2, 3, 0, 6, 9, 8, 5};
    int num = 5; 
    struct list_node *list = NULL;
    struct list_node *p = NULL;

    list = creat_list(array, 10);
    display_list(list);

    p = list;
    for (int i = 0; i < num; i++) {
        p = p->next;
    }
    printf("delete node is %dh, item is %d\n", num, p->item);

    delete_node(p);
    display_list(list);

    destory_list(list);

    return 0;
} 