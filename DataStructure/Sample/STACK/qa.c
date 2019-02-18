/* 基于数组的队列 */

#include <stdlib.h>
#include "qa.h"

/* 分配内存并初始化为空队列 */
void queue_init (QUEUE* queue, size_t cap) {
	queue->arr   = malloc (cap * sizeof (queue->arr[0]));
	queue->cap   = cap;
	queue->front = 0;
	queue->rear  = 0;
	queue->size  = 0;
}

/* 释放内存并恢复到初始状态 */
void queue_deinit (QUEUE* queue) {
	free (queue->arr);

	queue->arr   = NULL;
	queue->cap   = 0;
	queue->front = 0;
	queue->rear  = 0;
	queue->size  = 0;
}

/* 判断是否满 */
bool queue_full (QUEUE* queue) {
	return queue->size >= queue->cap;
}

/* 判断是否空 */
bool queue_empty (QUEUE* queue) {
	return ! queue->size;
}

/* 压入 */
void queue_push (QUEUE* queue, int data) {
	if (queue->rear >= queue->cap)
		queue->rear = 0;

	++queue->size;

	queue->arr[queue->rear++] = data;
}

/* 弹出 */
int queue_pop (QUEUE* queue) {
	if (queue->front >= queue->cap)
		queue->front = 0;

	--queue->size;

	return queue->arr[queue->front++];
}

/* 队首 */
int queue_front (QUEUE* queue) {
	if (queue->front >= queue->cap)
		queue->front = 0;

	return queue->arr[queue->front];
}

/* 大小 */
size_t queue_size (QUEUE* queue) {
	return queue->size;
}
