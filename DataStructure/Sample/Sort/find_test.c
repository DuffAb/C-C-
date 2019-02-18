/* 查找算法 */

#include <stdio.h>
#include "find.h"
#include "sort.h"

/* 测试用例 */
int main (void) {
	int data[] = {9, 0, 7, 2, 5, 4, 3, 6, 1, 8};
	size_t size = sizeof (data) / sizeof (data[0]);

	size_t i;
	for (i = 0; i < size; ++i)
		printf ("%d ", data[i]);
	printf ("\n");

	int key = 7/*77*/;
	if ((i = line_find (data, size, key)) == -1)
		printf ("找不到%d！\n", key);
	else
		printf ("data[%u] = %d\n", i, data[i]);

	quick_sort (data, 0, size - 1);

	for (i = 0; i < size; i++)
		printf ("%d ", data[i]);
	printf ("\n");

	key = 7/*77*/;
	if ((i = half_find (data, size, key)) == -1)
		printf ("找不到%d！\n", key);
	else
		printf ("data[%u] = %d\n", i, data[i]);

	return 0;
}
