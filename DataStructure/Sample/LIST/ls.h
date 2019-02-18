/* 双向线性链表 */

#ifndef _LS_H
#define _LS_H

#include <sys/types.h>
#include <stdbool.h>

/* 节点 */
typedef struct ListNode {
	int              data; /* 数据 */
	struct ListNode* prev; /* 前指针 */
	struct ListNode* next; /* 后指针 */
}	LIST_NODE;

/* 链表 */
typedef struct List {
	LIST_NODE* head; /* 头指针 */
	LIST_NODE* tail; /* 尾指针 */
	LIST_NODE* frwd; /* 正向迭代指针 */
	LIST_NODE* bkwd; /* 反向迭代指针 */
}	LIST;

/* 初始化为空链表 */
void list_init (LIST* list);

/* 释放剩余节点并恢复到初始状态 */
void list_deinit (LIST* list);

/* 判断是否空 */
bool list_empty (LIST* list);

/* 追加 */
void list_append (LIST* list, int data);

/* 前插 */
bool list_insert (LIST* list, size_t pos, int data);

/* 随机访问 */
int* list_at (LIST* list, size_t pos);

/* 删除 */
bool list_erase (LIST* list, size_t pos);

/* 删除所有匹配数据 */
void list_remove (LIST* list, int data);

/* 清空 */
void list_clear (LIST* list);

/* 大小 */
size_t list_size (LIST* list);

/* 开始正向迭代 */
void list_begin (LIST* list);

/* 向后正向迭代 */
int* list_next (LIST* list);

/* 向前正向迭代 */
int* list_prev (LIST* list);

/* 获取正向迭代 */
int* list_current (LIST* list);

/* 判断正向迭代是否终止 */
bool list_end (LIST* list);

/* 开始反向迭代 */
void list_rbegin (LIST* list);

/* 向后反向迭代 */
int* list_rnext (LIST* list);

/* 向前反向迭代 */
int* list_rprev (LIST* list);

/* 获取反向迭代 */
int* list_rcurrent (LIST* list);

/* 判断反向迭代是否终止 */
bool list_rend (LIST* list);

#endif /* _LS_H */
