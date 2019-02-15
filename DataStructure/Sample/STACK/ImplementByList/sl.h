/* 基于链表的堆栈 */

#ifndef _SL_H
#define _SL_H

#include <sys/types.h>
#include <stdbool.h>

/* 节点 */
typedef struct StackNode {
	int               data; /* 数据 */
	struct StackNode* next; /* 后指针 */
}	STACK_NODE;

/* 堆栈 */
typedef struct Stack {
	STACK_NODE* top; /* 栈顶 */
}	STACK;

/* 初始化为空堆栈 */
void stack_init (STACK* stack);

/* 释放剩余节点并恢复到初始状态 */
void stack_deinit (STACK* stack);

/* 判断是否空 */
bool stack_empty (STACK* stack);

/* 压入 */
void stack_push (STACK* stack, int data);

/* 弹出 */
int stack_pop (STACK* stack);

/* 栈顶 */
int stack_top (STACK* stack);

/* 大小 */
size_t stack_size (STACK* stack);

#endif /* _SL_H */
