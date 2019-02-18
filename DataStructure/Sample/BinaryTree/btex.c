/* 练习：重建二叉树
 *
 * 1. 实现tree_reconstruct()函数，根据从参数传入的前序和中序遍历结果(其
 *    中不含重复数据)，重建二叉树；
 * 2. 实现tree_pretravel()和tree_intravel()函数，分别用于前序和中序遍历
 *    二叉树，已验证重建的正确性。
 */
#include <stdio.h>
#include <stdlib.h>

/* 节点 */
typedef struct TreeNode {
	int              data;  /* 数据 */
	struct TreeNode* left;  /* 左子树 */
	struct TreeNode* right; /* 右子树 */
}	TREE_NODE;

/* 创建节点 */
TREE_NODE* create_node (int data) {
	TREE_NODE* node = malloc (sizeof (TREE_NODE));
	node->data = data;
	node->left = NULL;
	node->right = NULL;
	return node;
}

/* 销毁节点 */
void destroy_node (TREE_NODE* node) {
	free (node);
}

/* 二叉树 */
typedef struct Tree {
	TREE_NODE* root; /* 树根 */
}	TREE;

/* 初始化为空树 */
void tree_init (TREE* tree) {
	tree->root = NULL;
}

/* 删除以参数tree的目标所指向的节点为根的子树 */
void clear (TREE_NODE** root) {
	if (*root) {
		clear (&(*root)->left);
		clear (&(*root)->right);

		destroy_node (*root);
		*root = NULL;
	}
}

/* 释放剩余节点并恢复到初始状态 */
void tree_deinit (TREE* tree) {
	clear (&tree->root);
}

/* 根据前序和中序遍历结果，重建子树，返回其根节点的地址
 *
 * 前序遍历：1   2   4   7   3   5   6   8
 *           ^   ^^^^^^^^^   ^^^^^^^^^^^^^
 *           根    左子树        右子树
 *
 * 中序遍历：4   7   2   1   5   3   8   6
 *           ^^^^^^^^^   ^   ^^^^^^^^^^^^^
 *             左子树    根      右子树
 */
TREE_NODE* reconstruct (int preorder[], int inorder[], size_t size) {
	if (! preorder || ! inorder || ! size)
		return NULL;

	TREE_NODE* root = create_node (preorder[0]);

	size_t len; /* 左子树长度 */
	for (len = 0; len < size && inorder[len] != preorder[0]; ++len);
	if (len >= size)
		return NULL;

	root->left = reconstruct (preorder + 1, inorder, len);
	root->right = reconstruct (preorder + 1 + len, inorder + len + 1,
		size - len - 1);

	return root;
}

/* 根据前序和中序遍历结果，重建二叉树 */
void tree_reconstruct (TREE* tree, int preorder[], int inorder[],
	size_t size) {
	tree->root = reconstruct (preorder, inorder, size);
}

/* 前序遍历以参数tree的目标为根的子树 */
void pretravel (TREE_NODE* root) {
	if (root) {
		printf ("%d ", root->data);
		pretravel (root->left);
		pretravel (root->right);
	}
}

/* 前序遍历 */
void tree_pretravel (TREE* tree) {
	pretravel (tree->root);
	printf ("\n");
}

/* 中序遍历以参数tree的目标为根的子树 */
void intravel (TREE_NODE* root) {
	if (root) {
		intravel (root->left);
		printf ("%d ", root->data);
		intravel (root->right);
	}
}

/* 中序遍历 */
void tree_intravel (TREE* tree) {
	intravel (tree->root);
	printf ("\n");
}

/* 测试用例
 *
 *     1
 *    / \
 *   2   3
 *  /   / \
 * 4   5   6
 *  \     /
 *   7   8
 */
int main (void) {
	TREE tree;
	tree_init (&tree);

	int preorder[] = {1,2,4,7,3,5,6,8};
	int inorder[] = {4,7,2,1,5,3,8,6};
	size_t size = sizeof (preorder) / sizeof (preorder[0]);
	tree_reconstruct (&tree, preorder, inorder, size);

	tree_pretravel (&tree);
	tree_intravel (&tree);

	tree_deinit (&tree);
	return 0;
}
