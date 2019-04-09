/* 基于链表的堆栈 */

#include <stdio.h>
#include "slist.h"

/* 测试用例 */
int main (void) {
	int lsize = 0;
	unsigned int numb = 10;
	int base = 10;
	SLIST *list = NULL;
	//slist_init(list);

	slist_append(&list, 10);
	slist_append(&list, 30);
	slist_append(&list, 50);
	slist_insert(&list, 1, 20);
	slist_insert(&list, 4, 40);
	lsize = slist_size(list);
	printf("反转前：");
	for (int i = 0; i < lsize; ++i) {
		int digist = *slist_at(list, i);
		printf("%d ", digist);
	}
	printf("\n");

	list = slist_reverse(list);
	printf("反转：");
	for (int i = 0; i < lsize; ++i) {
		int digist = *slist_at(list, i);
		printf("%d ", digist);
	}
	printf("\n");

	list = slist_reverse_recursion(list);
	printf("再反转：");
	for (int i = 0; i < lsize; ++i) {
		int digist = *slist_at(list, i);
		printf("%d ", digist);
	}
	printf("\n");

	slist_append(&list, 41);
	slist_append(&list, 41);
	for (int i = 0; i < slist_size(list); ++i) {
		int digist = *slist_at(list, i);
		printf("%d ", digist);
	}
	printf("\n");

	slist_erase(&list, 0);
	slist_erase(&list, 1);
	slist_remove(&list, 41);
	for (int i = 0; i < slist_size(list); ++i) {
		int digist = *slist_at(list, i);
		printf("%d ", digist);
	}
	printf("\n");

	slist_clear(&list);
	printf("%d, %d\n", slist_empty(list), slist_size(list));

	return 0;
}
