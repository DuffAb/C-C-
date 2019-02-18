/* 逆波兰法求解四则运算表达式 */

#include <stdio.h>
#include "rpn.h"

/* 测试用例 */
int main (void) {
	/*
	printf ("%g, %g\n",
		rpn_calculate ("(1+2*3.15/2)/4-(5-9)/(3.14*23.88)"),
		(1+2*3.15/2)/4-(5-9)/(3.14*23.88));
	*/
	printf ("----------------\n");
	printf ("逆波兰迷你计算器\n");
	printf ("----------------\n");

	printf ("四则算式：");
	char infix[1024];
	gets (infix);

	char* suffix = rpn_convert (infix);
	printf ("逆波兰式：%s\n", suffix);
	rpn_free (suffix);

	printf ("计算结果：%g\n", rpn_calculate (infix));

	printf ("----------------\n");
	return 0;
}
