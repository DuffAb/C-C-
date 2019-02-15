/* 基于链表的堆栈 */

#include <stdio.h>
#include "sl.h"

/* 测试用例 */
int main (void) {
	printf ("整数：");
	unsigned int numb;
	scanf ("%d", &numb);
	printf ("进制：");
	int base;
	scanf ("%d", &base);

	STACK stack;
	stack_init (&stack);

	do {
		stack_push (&stack, numb % base);
	}	while (numb /= base);

	printf ("结果：");
	while (! stack_empty (&stack)) {
		int digit = stack_pop (&stack);
		if (digit < 10)
			printf ("%d", digit);
		else
			printf ("%c", digit - 10 + 'A');
	}
	printf ("\n");

	stack_deinit (&stack);
	return 0;
}
