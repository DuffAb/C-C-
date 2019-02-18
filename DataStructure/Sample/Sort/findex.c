/* 练习：设有整数矩阵，行自左向右递增，列自上向下递增。编写matrix_find()
 *       函数，获取指定数据在该矩阵中的索引。找不到返回-1。
 *
 * 1  2  8  9
 * 2  4  9 12
 * 4  7 10 13
 * 6  8 11 15
 */
#include <stdio.h>

int matrix_find (int matrix[], int rows, int cols, int key) {
	if (! matrix || rows <= 0 || cols <= 0)
		return -1;

	int row = 0, col = cols - 1;

	while (row < rows && col >= 0) {
		int i = row * cols + col;

		if (key < matrix[i])
			--col;
		else
		if (matrix[i] < key)
			++row;
		else
			return i;
	}

	return -1;
}

int main (void) {
	int matrix[] = {
		1, 2,  8,  9,
		2, 4,  9, 12,
		4, 7, 10, 13,
		6, 8, 11, 15};

	printf ("%d\n", matrix_find (matrix, 4, 4, 7));
	printf ("%d\n", matrix_find (matrix, 4, 4, 1));
	printf ("%d\n", matrix_find (matrix, 4, 4, 15));
	printf ("%d\n", matrix_find (matrix, 4, 4, 5));
	printf ("%d\n", matrix_find (NULL, 4, 4, 7));

	return 0;
}
