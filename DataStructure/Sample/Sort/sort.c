/* 排序算法 */

#include <stdlib.h>
#include "sort.h"

/* 冒泡排序 */
void bubble_sort (int data[], size_t size) {
	size_t i;
	for (i = 0; i < size - 1; ++i) {
		int ordered = 1;

		size_t j;
		for (j = 0; j < size - 1 - i; ++j)
			if (data[j + 1] < data[j]) {
				int swap = data[j];
				data[j] = data[j + 1];
				data[j + 1] = swap;

				ordered = 0;
			}

		if (ordered)
			break;
	}
}

/* 插入排序 */
void insert_sort (int data[], size_t size) {
	size_t i;
	for (i = 1; i < size; ++i) {
		int inserted = data[i];

		size_t j;
		for (j = i; j > 0 && inserted < data[j - 1]; --j)
			data[j] = data[j - 1];

		if (j != i)
			data[j] = inserted;
	}
}

/* 希尔排序 */
void shell_sort (int data[], size_t size) {
	size_t gap;
	for (gap = 0; gap <= size; gap = gap * 3 + 1);

	while (gap) {
		size_t i;
		for (i = gap; i < size; ++i) {
			int inserted = data[i];

			size_t j;
			for (j = i; j >= gap && inserted < data[j - gap]; j -= gap)
				data[j] = data[j - gap];

			if (j != i)
				data[j] = inserted;
		}

		gap = (gap - 1) / 3;
	}
}

/* 选择排序 */
void select_sort (int data[], size_t size) {
	size_t i;
	for (i = 0; i < size - 1; ++i) {
		size_t min = i;

		size_t j;
		for (j = i + 1; j < size; ++j)
			if (data[j] < data[min])
				min = j;

		if (min != i) {
			int swap = data[i];
			data[i] = data[min];
			data[min] = swap;
		}
	}
}

/* 快速排序 */
void quick_sort (int data[], size_t left, size_t right) {
	size_t p = (left + right) / 2;
	int pivot = data[p];

	size_t i = left, j = right;
	while (i < j) {
		for (; ! (i >= p || pivot < data[i]); ++i);

		if (i < p) {
			data[p] = data[i];
			p = i;
		}

		for (; ! (j <= p || data[j] < pivot); --j);

		if (j > p) {
			data[p] = data[j];
			p = j;
		}
	}

	data[p] = pivot;

	if (p - left > 1)
		quick_sort (data, left, p - 1);

	if (right - p > 1)
		quick_sort (data, p + 1, right);
}

/* 外部合并 */
static void outer_merge (int data1[], size_t size1, int data2[],
	size_t size2, int data3[]) {
	size_t i = 0, j = 0, k = 0;

	for (;;)
		if (i < size1 && j < size2)
			if (data2[j] < data1[i])
				data3[k++] = data2[j++];
			else
				data3[k++] = data1[i++];
		else
		if (i < size1)
			data3[k++] = data1[i++];
		else
		if (j < size2)
			data3[k++] = data2[j++];
		else
			break;
}

/* 内部合并 */
static void inner_merge (int data[], size_t left, size_t mid,
	size_t right) {
	/*
	int*   data1 = data + left;
	size_t size1 = mid - left + 1;
	int*   data2 = data + mid + 1;
	size_t size2 = right - mid;
	size_t size3 = right - left + 1;
	int*   data3 = malloc (size3 * sizeof (int));

	outer_merge (data1, size1, data2, size2, data3);

	size_t i;
	for (i = 0; i < size3; ++i)
		data[left + i] = data3[i];

	free (data3);
	*/
	size_t size = (right - left + 1) * sizeof (int);
	int* merge = malloc (size);
	outer_merge (data + left, mid - left + 1, data + mid + 1, right - mid,
		merge);
	memcpy (data + left, merge, size);
	free (merge);
}

/* 归并排序 */
void merge_sort (int data[], size_t left, size_t right) {
	if (left < right) {
		int mid = (left + right) / 2;

		merge_sort (data, left, mid);
		merge_sort (data, mid + 1, right);

		inner_merge (data, left, mid, right);
	}
}
