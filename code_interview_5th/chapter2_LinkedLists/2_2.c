/*
 * Implement an algorithm to find the nth to last element of a singly linked list.
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include "linkedlists.h"

struct list_node *find_nth2last(struct list_node *head, int n)
{
    if (head == NULL || n < 1) {
        return NULL;
    }

    struct list_node *p = head;
    struct list_node *q = head;
    int i = 0;

    for (i = 0; i < n; i++) {
        if (q == NULL) {
            return NULL;
        }
        q = q->next;
    }

    while (q) {
        q = q->next;
        p = p->next;
    }

    return p;
}

int main(int argc, char const *argv[])
{
    int array[10] = {7, 4, 1, 2, 3, 0, 6, 9, 8, 5};
    struct list_node *list = NULL;
    struct list_node *node = NULL;

    list = creat_list(array, 10);
    display_list(list);
    
    node = find_nth2last(list, 2);
    if (node != NULL) {
        printf("nth to last item = %d\n", node->item);
    }

    destory_list(list);

    return 0;
}