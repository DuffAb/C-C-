/* 逆波兰法求解四则运算表达式 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "rpn.h"
#include "ql.h"
#include "sl.h"

/* 中缀表达式预处理 */
static char* preproc (const char* infix) {
	char* pinfix = malloc (strlen (infix) + 1);

	size_t i;
	for (i = 0; *infix; ++infix)
		if (*infix != ' ')
			pinfix[i++] = *infix;
	pinfix[i] = '\0';

	for (i = 0; pinfix[i]; ++i)
		if (pinfix[i] == '+' &&
			(i == 0 || strchr ("+-*/(", pinfix[i-1])))
				pinfix[i] = '#';
		else
		if (pinfix[i] == '-' &&
			(i == 0 || strchr ("+-*/(", pinfix[i-1])))
				pinfix[i] = '~';

	return pinfix;
}

/* 判断运算符的优先级 */
static int prior (char op1, char op2) {
	return strchr ("*/", op1) && strchr ("+-", op2);
}
/*
   将中缀表达式转换为后缀表达式

   1 + 2        ->  1 2 +      运算数在前，运算符在后
   1 + 2 - 3    ->  1 2 + 3 -  同级运算符，左在前，右在后 
   1 + 2 * 3    ->  1 2 3 * +  不同级运算符，高在前，低在后
   (1 + 2) * 3  ->  1 2 + 3 *  小括号内的运算符在前
   (1 + 2) * (3 + 4)  ->  1 2 + 3 4 + *
*/
char* rpn_convert (const char* infix) {
	char* pinfix = preproc (infix);

	QUEUE queue;
	queue_init (&queue);
	STACK stack;
	stack_init (&stack);

	size_t i, len = strlen (pinfix);
	/* 遍历中缀表达式中的每一个字符 */
	for (i = 0; i < len; ++i) {
		/* 数字、小数点和正负号 */
		if (isdigit (pinfix[i]) || strchr (".#~", pinfix[i]))
			queue_push (&queue, pinfix[i]); /* 入队 */
		/* 左括号 */
		else if (pinfix[i] == '(')
			stack_push (&stack, pinfix[i]); /* 入栈 */
		/* 右括号 */
		else if (pinfix[i] == ')') {
			/* 将与对应左括号之间的运算符出栈入队 */
			while (! stack_empty (&stack) && stack_top (&stack) != '(') {
				queue_push (&queue, ' ');
				queue_push (&queue, stack_pop (&stack));
			}
			/* 左括号出栈 */
			if (! stack_empty (&stack))
				stack_pop (&stack);
		}
		/* 运算符 */
		else if (strchr ("+-*/", pinfix[i])) {
			queue_push (&queue, ' ');
			/* 若该运算符不优于栈顶，则出栈入队 */
			while (! stack_empty (&stack) && stack_top (&stack) != '(' &&
				! prior (pinfix[i], stack_top (&stack))) {
				queue_push (&queue, stack_pop (&stack));
				queue_push (&queue, ' ');
			}
			/* 优者入栈 */
			stack_push (&stack, pinfix[i]);
		}
	}
	/* 余者出栈入队 */
	while (! stack_empty (&stack)) {
		queue_push (&queue, ' ');
		queue_push (&queue, stack_pop (&stack));
	}

	/* 释放预处理后的中缀表达式 */
	free (pinfix);

	/* 构建后缀表达式字符串 */
	char* suffix = malloc ((queue_size (&queue) + 1) *
		sizeof (char));
	for (i = 0; ! queue_empty (&queue); ++i)
		suffix[i] = queue_pop (&queue);
	suffix[i] = '\0';

	stack_deinit (&stack);
	queue_deinit (&queue);

	return suffix;
}

/* 释放后缀表达式 */
void rpn_free (char* suffix) {
	free (suffix);
}

/* 从后缀表达式提取运算数 */
static double operand (const char* suffix, size_t* pos) {
	double operand = 0;

	int negative = 0;
	if (suffix[*pos] == '#')
		++*pos;
	else
	if (suffix[*pos] == '~') {
		++*pos;
		negative = 1;
	}

	/* 整数部分 */
	for (; isdigit (suffix[*pos]); ++*pos)
		operand = operand * 10 + (suffix[*pos] - '0');

	/* 小数部分 */
	if (suffix[*pos] == '.') {
		size_t decimals = 0;

		for (++*pos; isdigit (suffix[*pos]); ++*pos) {
			operand = operand * 10 + (suffix[*pos] - '0');
			++decimals;
		}

		for (; decimals; --decimals)
			operand /= 10;
	}

	return negative ? -operand : operand;
}

typedef union Double {
	double f;
	int i[2];
}	DOUBLE;

/* 将double型数据压入int型堆栈 */
static void push_double (STACK* stack, double f) {
	DOUBLE d;
	d.f = f;

	stack_push (stack, d.i[0]);
	stack_push (stack, d.i[1]);
}

/* 从int型堆栈弹出double型数据 */
static double pop_double (STACK* stack) {
	DOUBLE d = {0};

	if (! stack_empty (stack))
		d.i[1] = stack_pop (stack);
	if (! stack_empty (stack))
		d.i[0] = stack_pop (stack);

	return d.f;
}
/*
   计算后缀表达式

   若当前字符为运算数，则压栈；
   若当前字符为运算符，则从栈中弹出两个运算数，并将运算结果压栈；
   处理完整个表达式，栈中最后一个数就是表达式的值。
*/
static double calculate (char* suffix) {
	STACK stack;
	stack_init (&stack);

	size_t i, len = strlen (suffix);
	for (i = 0; i < len; ++i)
		if (isdigit (suffix[i]) || strchr (".#~", suffix[i]))
			push_double (&stack, operand (suffix, &i));
		else
		if (strchr ("+-*/", suffix[i])) {
			double f2 = pop_double (&stack);
			double f1 = pop_double (&stack);

			switch (suffix[i]) {
				case '+':
					push_double (&stack, f1 + f2);
					break;

				case '-':
					push_double (&stack, f1 - f2);
					break;

				case '*':
					push_double (&stack, f1 * f2);
					break;

				case '/':
					push_double (&stack, f1 / f2);
					break;
			}
		}

	rpn_free (suffix);
	double res = pop_double (&stack);

	stack_deinit (&stack);
	return res;
}

/* 计算中缀表达式 */
double rpn_calculate (const char* infix) {
	return calculate (rpn_convert (infix));
}
