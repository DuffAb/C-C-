/* 基于数组的堆栈 */

#include <stdio.h>
#include "sa.h"

/* 测试用例 */
int main (void) {
	STACK stack;
	stack_init (&stack, 10);

	int i = 0;
	while (! stack_full (&stack))
		stack_push (&stack, i++);

	while (! stack_empty (&stack))
		printf ("%d\n", stack_pop (&stack));

	stack_deinit (&stack);
	return 0;
}
