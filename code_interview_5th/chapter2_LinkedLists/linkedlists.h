#ifndef _LINKEDLISTS_H_
#define _LINKEDLISTS_H_

struct list_node
{
    int item;
    struct list_node *next;
};

struct list_node * creat_list(int num[], int size);
void display_list(struct list_node *node);

#endif