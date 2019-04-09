/* 有序二叉树(二叉搜索树) */

#ifndef _BT_H
#define _BT_H

#include <sys/types.h>
#include <stdbool.h>

/* 节点 */
typedef struct BsTreeNode {
	int                data;  /* 数据 */
	struct BsTreeNode* left;  /* 左子树 */
	struct BsTreeNode* right; /* 右子树 */
}	BSTREE_NODE;

/* 二叉树 */
typedef struct BsTree {
	BSTREE_NODE* root; /* 树根 */
	size_t       size; /* 大小 */
}	BSTREE;

/* 初始化为空树 */
void bstree_init (BSTREE* bstree);

/* 释放剩余节点并恢复到初始状态 */
void bstree_deinit (BSTREE* bstree);

/* 插入 */
void bstree_insert (BSTREE* bstree, int data);

/* 删除 */
bool bstree_erase (BSTREE* bstree, int data);

/* 删除所有匹配数据 */
void bstree_remove (BSTREE* bstree, int data);

/* 清空 */
void bstree_clear (BSTREE* bstree);

/* 更新 */
void bstree_update (BSTREE* bstree, int old, int new);

/* 判断是否存在 */
bool bstree_exist (BSTREE* bstree, int data);

/* 深度优先遍历 前序遍历 D-L-R */
void bstree_preorder_travel (BSTREE* bstree);

/* 深度优先遍历 中序遍历 L-D-R*/
void bstree_inorder_travel (BSTREE* bstree);

/* 深度优先遍历 后序遍历 L-R-D */
void bstree_postorder_travel (BSTREE* bstree);

/* 广度优先遍历 */
void bstree_breadth_first_travel(BSTREE* bstree);

/* 大小 */
size_t bstree_size (BSTREE* bstree);

/* 高度 */
size_t bstree_height (BSTREE* bstree);

/* 是否平衡 */
bool bstree_is_balance (BSTREE* bstree);

#endif /* _BT_H */
