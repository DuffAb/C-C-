/* 基于链表的队列 */

#ifndef _L_QUEUE_H
#define _L_QUEUE_H

#include <sys/types.h>
#include <stdbool.h>

/* 节点 */
typedef struct QueueNode {
	int               data; /* 数据 */
	struct QueueNode* next; /* 后指针 */
}	QUEUE_NODE;

/* 队列 */
typedef struct Queue {
	QUEUE_NODE* front; /* 前端(弹出) */
	QUEUE_NODE* rear;  /* 后端(压入) */
}	QUEUE;

/* 初始化为空队列 */
void queue_init (QUEUE* queue);

/* 释放剩余节点并恢复到初始状态 */
void queue_deinit (QUEUE* queue);

/* 判断是否空 */
bool queue_empty (QUEUE* queue);

/* 压入 */
void queue_push (QUEUE* queue, int data);

/* 弹出 */
int queue_pop (QUEUE* queue);

/* 队首 */
int queue_front (QUEUE* queue);

/* 大小 */
size_t queue_size (QUEUE* queue);

#endif /* _L_QUEUE_H */
