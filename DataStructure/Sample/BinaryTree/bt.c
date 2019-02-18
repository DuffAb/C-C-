/* 有序二叉树(二叉搜索树)
 *
 *                    BSTREE
 *                   +------+
 *                   | root |
 *                   +------+
 *                      |
 *                      V
 *                 BSTREE_NODE
 *              +--------------+
 *              |     data     |
 *              +------+-------+
 *        +---- | left | right | ----+
 *        |     +------+-------+     |
 *        V                          V
 * +--------------+          +--------------+
 * |     data     |          |     data     |
 * +------+-------+          +------+-------+
 * | left | right |          | left | right |
 * +------+-------+          +------+-------+
 */
#include <stdio.h>
#include <stdlib.h>
#include "bt.h"

/* 创建节点 */
static BSTREE_NODE* create_node (int data) {
	BSTREE_NODE* node = malloc (sizeof (BSTREE_NODE));
	node->data = data;
	node->left = NULL;
	node->right = NULL;
	return node;
}

/* 销毁节点 */
static void destroy_node (BSTREE_NODE* node) {
	free (node);
}

/* ----------------------- 递归形式的内部接口 ----------------------- */

static void insert (BSTREE_NODE* node, BSTREE_NODE** root) {
	if (! *root)
		*root = node;
	else if (node)
		if (node->data < (*root)->data)
			insert (node, &(*root)->left);
		else
			insert (node, &(*root)->right);
}

/* 返回以参数root的目标所指向的节点为根的子树中，数值与参数data
   相匹配的节点的父节点中，指向该节点的指针型成员变量的地址 */
static BSTREE_NODE** find (int data, BSTREE_NODE** root) {
	if (! *root)
		return root;

	if (data < (*root)->data)
		return find (data, &(*root)->left);

	if ((*root)->data < data)
		return find (data, &(*root)->right);

	return root;
}

static void clear (BSTREE_NODE** root) {
	if (*root) {
		clear (&(*root)->left);
		clear (&(*root)->right);

		destroy_node (*root);
		*root = NULL;
	}
}

static void travel (BSTREE_NODE* root) {
	if (root) {
		travel (root->left);
		printf ("%d ", root->data);
		travel (root->right);
	}
}

static size_t height (BSTREE_NODE* root) {
	if (root) {
		size_t lh = height (root->left);
		size_t rh = height (root->right);

		return (lh > rh ? lh : rh) + 1;
	}

	return 0;
}

/* ------------------------------------------------------------------ */

/* 初始化为空树 */
void bstree_init (BSTREE* bstree) {
	bstree->root = NULL;
	bstree->size = 0;
}

/* 释放剩余节点并恢复到初始状态 */
void bstree_deinit (BSTREE* bstree) {
	clear (&bstree->root);
	bstree->size = 0;
}

/* 插入 */
void bstree_insert (BSTREE* bstree, int data) {
	insert (create_node (data), &bstree->root);
	++bstree->size;
}

/* 删除 */
bool bstree_erase (BSTREE* bstree, int data) {
	BSTREE_NODE** node = find (data, &bstree->root);

	if (*node) {
		/* 将匹配节点的左子树插入其右子树 */
		insert ((*node)->left, &(*node)->right);

		BSTREE_NODE* temp = *node;
		/* 用匹配节点的右子树的根节点取代匹配节点 */
		*node = (*node)->right;
		/* 删除匹配节点 */
		destroy_node (temp);

		--bstree->size;
		return true;
	}

	return false;
}

/* 删除所有匹配数据 */
void bstree_remove (BSTREE* bstree, int data) {
	while (bstree_erase (bstree, data));
}

/* 清空 */
void bstree_clear (BSTREE* bstree) {
	bstree_deinit (bstree);
}

/* 更新 */
void bstree_update (BSTREE* bstree, int old, int new) {
	while (bstree_erase (bstree, old))
		bstree_insert (bstree, new);
}

/* 判断是否存在 */
bool bstree_exist (BSTREE* bstree, int data) {
	return *find (data, &bstree->root) != NULL;
}

/* 中序遍历 */
void bstree_travel (BSTREE* bstree) {
	travel (bstree->root);
	printf ("\n");
}

/* 大小 */
size_t bstree_size (BSTREE* bstree) {
	return bstree->size;
}

/* 高度 */
size_t bstree_height (BSTREE* bstree) {
	return height (bstree->root);
}
