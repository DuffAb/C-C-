/* 基于链表的堆栈
 *
 *                  STACK
 *                 +-----+
 *    +----------- | top |
 *    |            +-----+
 *    |
 *    V           STACK_NODE
 * +------+    +------+           +------+
 * | data |    | data |           | data |
 * +------+    +------+           +------+
 * | next | -> | next | -> ... -> | NULL |
 * +------+    +------+           +------+
 */

#include <stdlib.h>
#include "slist.h"

/* 创建节点 */
SLIST* create_node (int data) {
	SLIST* node = (SLIST*)malloc (sizeof (SLIST));
	node->data = data;
	node->next = NULL;
	return node;
}

/* 销毁节点 */
SLIST* destroy_node (SLIST* node) {
	SLIST* next = node->next;
	free (node);
	return next;
}

/* 判断是否空 */
bool slist_empty (SLIST* list) {
	return ! list;
}

/* 追加 */
void slist_append (SLIST** list, int data) {
	SLIST* node = create_node (data);
	if (!(*list)) {
		*list = node;
		return;
	}

	SLIST* find = NULL;
	for (find = *list; find; find = find->next) {
		if (!find->next){
			find->next = node;
			return;
		}
	}
}

/* 插入 */
bool slist_insert (SLIST** list, int pos, int data) {
	SLIST* find = NULL;
	for (find = *list; find; find = find->next) {
		if (! pos--){
			SLIST* node = create_node (data);
			node->next = find->next;
			find->next = node;
			return true;
		}
	}
	return false;
}

/* 随机访问 */
int* slist_at (SLIST* list, int pos){
	SLIST* find = NULL;
	for (find = list; find; find = find->next)
		if (! pos--)
			return &find->data;

	return NULL;
}

/* 删除 */
bool slist_erase (SLIST** list, int pos){
	// 是否删除第一个节点
	if (!pos)
	{
		*list = destroy_node(*list);
		return true;
	}

	SLIST* find = NULL, *fnext = NULL;
	for (find = *list; find && find->next; find = find->next){
		fnext = find->next;

		if (!--pos) {
			SLIST* next = destroy_node (fnext);

			if (next)
				find->next = next;

			return true;
		}
	}

	return false;
}

/* 删除链表中另一链表的元素 (链表未排序) */
bool slist_erase_list(SLIST** list_omitted, SLIST* list_refer) {
	if (!(*list_omitted) || !list_refer) {
		return false;
	}
	int losize = 0;
	int lrsize = 0;
	losize = slist_size(*list_omitted);
	lrsize = slist_size(list_refer);

	for (int i = 0; i < lrsize; ++i)
	{
		slist_remove(list_omitted, *slist_at(list_refer, i));
	}

	/*SLIST* pre = *list_omitted;
	SLIST* a = *list_omitted;
	SLIST* head = pre;
	while (a && list_refer) {
		if (a->data < list_refer->data) {
			a = a->next;
			pre = pre->next;
		}
		else if (a->data > list_refer->data) {
			list_refer = list_refer->next;
		}
		else {
			a = a->next;
			pre->next = a;
		}
	}
	*list_omitted = head->next;*/
	return true;
}

/* 删除所有匹配数据 */
void slist_remove (SLIST** list, int data){
	SLIST* find = NULL, *fnext = NULL;
	// 查看第一个节点是否匹配
	if (*list)
	{
		find = *list;
		if (find->data == data)
		{
			*list = destroy_node(find);
		}
	}

	find = *list;
	while ((fnext = find->next))
	{
		if (fnext->data == data) {
			find->next = destroy_node(fnext);
		}
		else
		{
			find = fnext;
		}
	}
	return;
}

/* 清空 */
void slist_clear (SLIST** list){
	while (*list) {
		*list = destroy_node(*list);
	}
}

/* 大小 */
int slist_size (SLIST* list){
	int size = 0;

	SLIST* node = NULL;
	for (node = list; node; node = node->next)
		++size;

	return size;
}

/* 反转 */
SLIST* slist_reverse(SLIST* list) {
	//链表为NULL或者只有一个节点
	if (!list || !list->next) {
		return list;
	}

	SLIST* list_node_cur = list->next;
	SLIST* list_node_pre = list;
	SLIST* list_node_tmp = NULL;
	list_node_pre->next = NULL;

	while (list_node_cur)
	{
		list_node_tmp = list_node_cur;
		list_node_cur = list_node_cur->next;

		list_node_tmp->next = list_node_pre;
		list_node_pre = list_node_tmp;
	}

	return list_node_tmp;
}

/* 反转 递归算法 */
SLIST* slist_reverse_recursion(SLIST* list) {
	//链表为NULL或者只有一个节点
	if (!list || !list->next) {
		return list;
	}

	SLIST* list_tmp = slist_reverse_recursion(list->next);
	list->next->next = list;
	list->next = NULL;

	return list_tmp;
}

bool slist_is_loop(SLIST* list) {
	//链表为NULL或者只有一个节点
	if (!list || !list->next) {
		return false;
	}
	SLIST* tmp = list->next;
	while (tmp && tmp != list)
	{
		tmp = tmp->next;
	}

	if (!tmp)
	{
		return false;
	}

	return true;
}
