/* 排序算法 */

#ifndef _SORT_H
#define _SORT_H

#include <sys/types.h>

/* 冒泡排序 */
void bubble_sort (int data[], size_t size);

/* 插入排序 */
void insert_sort (int data[], size_t size);

/* 希尔排序 */
void shell_sort (int data[], size_t size);

/* 选择排序 */
void select_sort (int data[], size_t size);

/* 快速排序 */
void quick_sort (int data[], size_t left, size_t right);

/* 归并排序 */
void merge_sort (int data[], size_t left, size_t right);

#endif /* _SORT_H */
