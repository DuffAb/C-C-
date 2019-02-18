/* 查找算法 */

#include "find.h"

/* 线性查找 */
size_t line_find (int data[], size_t size, int key) {
	size_t i;
	for (i = 0; i < size; ++i)
		if (data[i] == key)
			return i;

	return -1;
}

/* 递归二分查找 */
static size_t recu_find (int data[], int left, int right, int key) {
	if (left <= right) {
		int mid = (left + right) / 2;

		if (key < data[mid])
			return recu_find (data, left, mid - 1, key);
		else
		if (data[mid] < key)
			return recu_find (data, mid + 1, right, key);
		else
			return mid;
	}

	return -1;
}

/* 二分查找 */
size_t half_find (int data[], size_t size, int key) {
	/*
	return recu_find (data, 0, size - 1, key);
	*/
	int left = 0;
	int right = size - 1;

	while (left <= right) {
		int mid = (left + right) / 2;

		if (key < data[mid])
			right = mid - 1;
		else
		if (data[mid] < key)
			left = mid + 1;
		else
			return mid;
	}

	return -1;
}
