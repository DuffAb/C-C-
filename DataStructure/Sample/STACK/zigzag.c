/*
 * 编写程序，根据输入的n生成nxn的zigzag矩阵。
 *
 *  0  1  5  6 14
 *  2  4  7 13 15
 *  3  8 12 16 21
 *  9 11 17 20 22
 * 10 18 19 23 24
 */
#include <stdio.h>

int main (void) {
	printf ("n = ");
	int n;
	scanf ("%d", &n);
	if (n < 2) {
		printf ("n不能小于2！\n");
		return -1;
	}

	int m[n][n], i = 0, j = 0, k = 0, d;
	m[i][j] = k++;

	for (d = 2; d <= n; d++)
		if (d % 2) {
			for (i++; j < d; i--, j++)
				m[i][j] = k++;
			j--;
			i++;
		}
		else {
			for (j++; i < d; i++, j--)
				m[i][j] = k++;
			i--;
			j++;
		}

	for (d = n - 1; d >= 2; d--)
		if (d % 2) {
			for (j++; j < n; i--, j++)
				m[i][j] = k++;
			j--;
			i++;
		}
		else {
			for (i++; i < n; i++, j--)
				m[i][j] = k++;
			i--;
			j++;
		}

	m[i][++j] = k++;

	for (i = 0; i < n; i++) {
		for (j = 0; j < n; j++)
			printf ("%3d ", m[i][j]);
		printf ("\n");
	}

	return 0;
}
