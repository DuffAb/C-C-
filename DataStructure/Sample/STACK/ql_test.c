/* 基于链表的队列 */

#include <stdio.h>
#include "ql.h"

/* 测试用例 */
int main (void) {
	QUEUE queue;
	queue_init (&queue);

	int i;
	for (i = 0; i < 10; i++)
		queue_push (&queue, i);

	while (! queue_empty (&queue))
		printf ("%d\n", queue_pop (&queue));

	queue_deinit (&queue);
	return 0;
}
