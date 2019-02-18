/* 基于数组的队列 */

#include <stdio.h>
#include "qa.h"

/* 测试用例 */
int main (void) {
	QUEUE queue;
	queue_init (&queue, 4);

	int i;
	for (i = 10; i <= 40; i += 10)
		if (! queue_full (&queue))
			queue_push (&queue, i);

	for (i = 0; i < 2; i++)
		if (! queue_empty (&queue))
			printf ("%d\n", queue_pop (&queue));

	for (i = 50; i <= 60; i += 10)
		if (! queue_full (&queue))
			queue_push (&queue, i);

	while (! queue_empty (&queue))
		printf ("%d\n", queue_pop (&queue));

	queue_deinit (&queue);
	return 0;
}
