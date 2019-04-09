/* 逆波兰法求解四则运算表达式 */

#ifndef _RPN_H
#define _RPN_H

/* 将中缀表达式转换为后缀表达式 */
char* rpn_convert (const char* infix);

/* 释放后缀表达式 */
void rpn_free (char* suffix);

/* 计算中缀表达式 */
double rpn_calculate (const char* infix);

#endif /* _RPN_H */
