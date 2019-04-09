/* 双向线性链表
 *
 *                   LIST
 *             +------+------+
 *    +------  | head | tail | ------+
 *    |        +------+------+       |
 *    |                              |
 *    V           LIST_NODE          V
 * +------+    +------+           +------+
 * | data |    | data |           | data |
 * +------+    +------+           +------+
 * | NULL | <- | prev | <- ... <- | prev |
 * +------+    +------+           +------+
 * | next | -> | next | -> ... -> | NULL |
 * +------+    +------+           +------+
 */
#include <stdlib.h>
#include "dlist.h"

/* 创建节点 */
static LIST_NODE* create_node (int data, LIST_NODE* prev,	LIST_NODE* next) {
	LIST_NODE* node = malloc (sizeof (LIST_NODE));
	node->data = data;
	node->prev = prev;
	node->next = next;
	return node;
}

/* 销毁节点 */
static LIST_NODE* destroy_node (LIST_NODE* node, LIST_NODE** prev) {
	LIST_NODE* next = node->next;
	if (prev)
		*prev = node->prev; // 保存前节点的地址
	free (node);
	return next;
}

/* 初始化为空链表 */
void list_init (LIST* list) {
	list->head = NULL;
	list->tail = NULL;
}

/* 释放剩余节点并恢复到初始状态 */
void list_deinit (LIST* list) {
	while (list->head)
		list->head = destroy_node (list->head, NULL);

	list->tail = NULL;
}

/* 判断是否空 */
bool list_empty (LIST* list) {
	return ! list->head && ! list->tail;
}

/* 追加 */
void list_append (LIST* list, int data) {
	list->tail = create_node (data, list->tail, NULL);

	if (list->tail->prev)
		list->tail->prev->next = list->tail;
	else
		list->head = list->tail;
}

/* 前插 */
bool list_insert (LIST* list, size_t pos, int data) {
	LIST_NODE* find = NULL;
	for (find = list->head; find; find = find->next)
		if (! pos--) {
			LIST_NODE* node = create_node (data, find->prev, find);

			if (node->prev)
				node->prev->next = node;
			else
				list->head = node;

			node->next->prev = node;
			return true;
		}

	return false;
}

/* 随机访问 */
int* list_at (LIST* list, size_t pos) {
	LIST_NODE* find = NULL;
	for (find = list->head; find; find = find->next)
		if (! pos--)
			return &find->data;

	return NULL;
}

/* 删除 */
bool list_erase (LIST* list, size_t pos) {
	LIST_NODE* find = NULL;
	for (find = list->head; find; find = find->next)
		if (! pos--) {
			LIST_NODE* prev = NULL;
			LIST_NODE* next = destroy_node (find, &prev);

			if (prev)
				prev->next = next;
			else
				list->head = next;

			if (next)
				next->prev = prev;
			else
				list->tail = prev;

			return true;
		}

	return false;
}

/* 删除所有匹配数据 */
void list_remove (LIST* list, int data) {
	LIST_NODE* find = NULL, *next = NULL;
	for (find = list->head; find; find = next) {
		next = find->next;

		if (find->data == data) {
			LIST_NODE* prev = NULL;
			LIST_NODE* next = destroy_node (find, &prev);

			if (prev)
				prev->next = next;
			else
				list->head = next;

			if (next)
				next->prev = prev;
			else
				list->tail = prev;
		}
	}
}

/* 清空 */
void list_clear (LIST* list) {
	list_deinit (list);
}

/* 大小 */
size_t list_size (LIST* list) {
	size_t size = 0;

	LIST_NODE* node = NULL;
	for (node = list->head; node; node = node->next)
		++size;

	return size;
}

/* 开始正向迭代 */
void list_begin (LIST* list) {
	list->frwd = list->head;
}

/* 向后正向迭代 */
int* list_next (LIST* list) {
	int* data = &list->frwd->data;
	list->frwd = list->frwd->next;
	return data;
}

/* 向前正向迭代 */
int* list_prev (LIST* list) {
	int* data = &list->frwd->data;
	list->frwd = list->frwd->prev;
	return data;
}

/* 获取正向迭代 */
int* list_current (LIST* list) {
	return &list->frwd->data;
}

/* 判断正向迭代是否终止 */
bool list_end (LIST* list) {
	return ! list->frwd;
}

/* 开始反向迭代 */
void list_rbegin (LIST* list) {
	list->bkwd = list->tail;
};

/* 向后反向迭代 */
int* list_rnext (LIST* list) {
	int* data = &list->bkwd->data;
	list->bkwd = list->bkwd->prev;
	return data;
}

/* 向前反向迭代 */
int* list_rprev (LIST* list) {
	int* data = &list->bkwd->data;
	list->bkwd = list->bkwd->next;
	return data;
}

/* 获取反向迭代 */
int* list_rcurrent (LIST* list) {
	return &list->bkwd->data;
}

/* 判断反向迭代是否终止 */
bool list_rend (LIST* list) {
	return ! list->bkwd;
}
