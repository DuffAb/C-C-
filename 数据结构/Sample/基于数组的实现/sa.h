/* 基于数组的堆栈 */

#ifndef _SA_H
#define _SA_H

#include <sys/types.h>
#include <stdbool.h>

/* 堆栈 */
typedef struct Stack {
	int*   arr; /* 数组 */
	size_t cap; /* 容量 */
	size_t top; /* 栈顶 */
}	STACK;

/* 分配内存并初始化为空堆栈 */
void stack_init (STACK* stack, size_t cap);

/* 释放内存并恢复到初始状态 */
void stack_deinit (STACK* stack);

/* 判断是否满 */
bool stack_full (STACK* stack);

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

#endif /* _SA_H */
