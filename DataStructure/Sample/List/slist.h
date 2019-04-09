/* 基于链表的堆栈 */

#ifndef _SLIST_H
#define _SLIST_H

#include <sys/types.h>
#include <stdbool.h>

/* 节点 */
typedef struct SList {
	int           data; /* 数据 */
	struct SList* next; /* 后指针 */
} SLIST;

/* 判断是否空 */
bool slist_empty (SLIST* list);

/* 追加 */
void slist_append (SLIST** list, int data);

/* 插入 */
bool slist_insert (SLIST** list, int pos, int data);

/* 随机访问 */
int* slist_at (SLIST* list, int pos);

/* 删除 */
bool slist_erase (SLIST** list, int pos);

/* 删除链表中另一链表的元素 */
bool slist_erase_list(SLIST** list_omitted, SLIST* list_refer);

/* 删除所有匹配数据 */
void slist_remove (SLIST** list, int data);

/* 清空 */
void slist_clear (SLIST** list);

/* 大小 */
int slist_size (SLIST* list);

/* 反转  while循环算法*/
SLIST* slist_reverse(SLIST* list);

/* 反转 递归算法 */
SLIST* slist_reverse_recursion(SLIST* list);

/* 链表是否有循环 */
bool slist_is_loop(SLIST* list);

#endif /* _SLIST_H */
