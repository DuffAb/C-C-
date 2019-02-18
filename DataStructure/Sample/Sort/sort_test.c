/* 排序算法 */

#include <stdio.h>
#include <stdlib.h>
#include "sort.h"

/* 测试用例 */
int main (void) {
	srand (time (NULL));
	int data[10];
	size_t i, size = sizeof (data) / sizeof (data[0]);
	for (i = 0; i < size; ++i)
		printf ("%2d ", data[i] = rand () % 100);
	printf ("\n");
	/*
	bubble_sort (data, size);
	insert_sort (data, size);
	shell_sort (data, size);
	select_sort (data, size);
	quick_sort (data, 0, size - 1);
	*/
	merge_sort (data, 0, size - 1);

	for (i = 0; i < size; ++i)
		printf ("%2d ", data[i]);
	printf ("\n");

	return 0;
}
