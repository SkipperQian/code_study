/*
 * Write code to remove duplicates from an unsorted linked list.
 * FOLLOW UP
 * How would you solve this problem if a temporary buffer is not allowed?
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include "linkedlists.h"

void remove_duplicate_node(struct list_node *list)
{
    struct list_node *p, *q, *last;
    if (list == NULL) {
        return;
    }
    p = list;

    while (p) {
        q = p->next;
        last = p;
        while (q) {
            if (q->item == p->item) {
                last->next = q->next;
                free(q);
                q = last->next;
            } else {
                last = q;
                q = q->next;
            }
        }
        p = p->next;
    }
}

 int main(int argc, char *argv[])
 {
    int array[10] = {1, 1, 1, 1, 1, 5, 1, 1, 1, 1};
    struct list_node *list_head = NULL;

    list_head = creat_list(array, 10);
    display_list(list_head);

    remove_duplicate_node(list_head);
    display_list(list_head);

    return 0;
 }