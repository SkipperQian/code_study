#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/queue.h>

struct item {
	int val;
	TAILQ_ENTRY(item) entries;
};

TAILQ_HEAD(tqueue, item) queue_head;

int main(int argc, char *argv[])
{
	struct item *node;
	int i;

	TAILQ_INIT(&queue_head);
	for (i = 0; i < 10; i++) {
		node = (struct item *)malloc(sizeof(struct item));
		node->val = i;
		TAILQ_INSERT_TAIL(&queue_head, node, entries);
	}

	TAILQ_FOREACH(node, &queue_head, entries) {
		printf("%d\n", node->val);
	}

	node = TAILQ_FIRST(&queue_head);
	printf("head elem, val = %d\n", node->val);

	node = TAILQ_NEXT(node, entries);
	printf("next elem, val = %d\n", node->val);
	
	node = TAILQ_NEXT(node, entries);
	printf("next elem, val = %d\n", node->val);

	while ((node = TAILQ_FIRST(&queue_head)) != NULL) {
		TAILQ_REMOVE(&queue_head, node, entries);
		free(node);
	}

	if (TAILQ_EMPTY(&queue_head))
		printf("queue is empty\n");
	else
		printf("queue is not empty\n");

	return 0;
}
