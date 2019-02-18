/* 有序二叉树(二叉搜索树)
 *
 * 50 70 20 60 40 30 10 90 80
 *
 *          50
 *       __/  \__
 *      /        \
 *    20          70
 *   /  \        /  \
 * 10    40    60    90
 *      /           /
 *    30          80
 */
#include <stdio.h>
#include "bt.h"

/* 测试用例 */
int main (void) {
	BSTREE bstree;
	bstree_init (&bstree);

	bstree_insert (&bstree, 50);
	bstree_insert (&bstree, 70);
	bstree_insert (&bstree, 20);
	bstree_insert (&bstree, 60);
	bstree_insert (&bstree, 40);
	bstree_insert (&bstree, 30);
	bstree_insert (&bstree, 10);
	bstree_insert (&bstree, 90);
	bstree_insert (&bstree, 80);
	bstree_travel (&bstree);

	printf ("%u, %u\n", bstree_size (&bstree), bstree_height (&bstree));

	bstree_erase (&bstree, 60);
	bstree_travel (&bstree);

	bstree_insert (&bstree, 50);
	bstree_insert (&bstree, 50);
	bstree_travel (&bstree);
	bstree_remove (&bstree, 50);
	bstree_travel (&bstree);

	bstree_insert (&bstree, 40);
	bstree_insert (&bstree, 40);
	bstree_travel (&bstree);
	bstree_update (&bstree, 40, 85);
	bstree_travel (&bstree);

	printf ("%d, %d\n", bstree_exist (&bstree, 40),
		bstree_exist (&bstree, 85));

	bstree_deinit (&bstree);
	return 0;
}
