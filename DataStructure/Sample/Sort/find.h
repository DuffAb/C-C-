/* 查找算法 */

#ifndef _FIND_H
#define _FIND_H

#include <sys/types.h>

/* 线性查找 */
size_t line_find (int data[], size_t size, int key);

/* 二分查找 */
size_t half_find (int data[], size_t size, int key);

#endif /* _FIND_H */
