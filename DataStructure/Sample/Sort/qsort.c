/* 基于快速排序算法实现标准C库函数qsort() */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void quick_sort (void* base, size_t left, size_t right, size_t size,
	int (*compar) (const void*, const void*)) {
	size_t p = (left + right) / 2;
	void* pivot = malloc (size);
	memcpy (pivot, base + p * size, size);

	size_t i = left, j = right;
	while (i < j) {
		for (; ! (i >= p || compar (pivot, base + i * size) < 0); ++i);

		if (i < p) {
			memcpy (base + p * size, base + i * size, size);
			p = i;
		}

		for (; ! (j <= p || compar (base + j * size, pivot) < 0); --j);

		if (j > p) {
			memcpy (base + p * size, base + j * size, size);
			p = j;
		}
	}

	memcpy (base + p * size, pivot, size);
	free (pivot);

	if (p - left > 1)
		quick_sort (base, left, p - 1, size, compar);

	if (right - p > 1)
		quick_sort (base, p + 1, right, size, compar);
}

void my_qsort (void* base, size_t nmemb, size_t size,
	int (*compar) (const void*, const void*)) {
	quick_sort (base, 0, nmemb - 1, size, compar);
}

int compare_int (const void* a, const void* b) {
	return *(const int*)a - *(const int*)b;
}

int compare_str (const void* a, const void* b) {
	return strcmp (*(const char* const*)a, *(const char* const*)b);
}

int main (void) {
	int na[] = {34, 56, 17, 88, 41};
	size_t size = sizeof (na[0]);
	size_t nmemb = sizeof (na) / size;

	my_qsort (na, nmemb, size, compare_int);

	size_t i;
	for (i = 0; i < nmemb; ++i)
		printf ("%d ", na[i]);
	printf ("\n");

	const char* sa[] = {"jinan", "weifang", "heze", "qingdao", "linyi"};
	size = sizeof (sa[0]);
	nmemb = sizeof (sa) / size;

	my_qsort (sa, nmemb, size, compare_str);

	for (i = 0; i < nmemb; ++i)
		printf ("%s ", sa[i]);
	printf ("\n");

	return 0;
}
