/* 双向线性链表 */

#include <stdio.h>
#include "dlist.h"

/* 测试用例 */
int main (void) {
	LIST list;
	list_init (&list);

	list_append (&list, 10);
	list_append (&list, 30);
	list_append (&list, 50);
	list_insert (&list, 1, 20);
	list_insert (&list, 3, 40);

	for (list_begin (&list); ! list_end (&list); list_next (&list))
		printf ("%d ", ++*list_current (&list));
	printf ("\n");

	list_append (&list, 41);
	list_append (&list, 41);
	list_begin (&list);
	while (! list_end (&list))
		printf ("%d ", *list_next (&list));
	printf ("\n");
	list_erase (&list, 1);
	list_remove (&list, 41);
	list_rbegin (&list);
	while ( ! list_rend (&list))
		printf ("%d ", *list_rnext (&list));
	printf ("\n");

	size_t pos, size = list_size (&list);
	for (pos = 0; pos < size; ++pos)
		printf ("%d ", --*list_at (&list, pos));
	printf ("\n");

	list_clear (&list);
	printf ("%d, %d\n", list_empty (&list), list_size (&list));

	list_deinit (&list);
	return 0;
}
