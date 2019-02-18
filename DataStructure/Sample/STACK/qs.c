/* 基于堆栈的队列 */

#include "qs.h"

/* 初始化为空队列 */
void queue_init (QUEUE* queue) {
	stack_init (&queue->is);
	stack_init (&queue->os);
}

/* 释放剩余节点并恢复到初始状态 */
void queue_deinit (QUEUE* queue) {
	stack_deinit (&queue->is);
	stack_deinit (&queue->os);
}

/* 判断是否为空 */
bool queue_empty (QUEUE* queue) {
	return stack_empty (&queue->is) && stack_empty (&queue->os);
}

/* 压入 */
void queue_push (QUEUE* queue, int data) {
	stack_push (&queue->is, data);
}

/* 弹出 */
int queue_pop (QUEUE* queue) {
	if (stack_empty (&queue->os))
		while (! stack_empty (&queue->is))
			stack_push (&queue->os, stack_pop (&queue->is));

	return stack_pop (&queue->os);
}

/* 队首 */
int queue_front (QUEUE* queue) {
	if (stack_empty (&queue->os))
		while (! stack_empty (&queue->is))
			stack_push (&queue->os, stack_pop (&queue->is));

	return stack_top (&queue->os);
}

/* 大小 */
size_t queue_size (QUEUE* queue) {
	return stack_size (&queue->is) + stack_size (&queue->os);
}
