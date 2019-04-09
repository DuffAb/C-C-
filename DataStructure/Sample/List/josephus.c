/* 小孩出列————约瑟夫环问题 */

#include <stdio.h>
#include <stdlib.h>

/* 小孩 */
typedef struct Child {
	int           numb; /* 编号 */
	struct Child* next; /* 下一个小孩 */
}	CHILD;

/* 创建小孩 */
CHILD* create_child (int numb, CHILD* next) {
	CHILD* child = malloc (sizeof (CHILD));
	child->numb = numb;
	child->next = next;
}

/* 销毁小孩 */
CHILD* destroy_child (CHILD* child) {
	CHILD* next = child->next;
	free (child);
	return next != child ? next : NULL;
}

/* 环 */
typedef struct Ring {
	CHILD* one; /* 报一小孩 */
	int    gap; /* 报数间隔 */
}	RING;

/* 初始化环 */
void ring_init (RING* ring, int children, int starter, int gap) {
	ring->one = NULL;
	ring->gap = gap;

	CHILD* head = NULL, *tail = NULL;

	int numb;
	for (numb = children; numb >= 1; --numb) {
		head = create_child (numb, head);
		if (! tail)
			tail = head;
	}
	if (tail)
		tail->next = head;

	if (head && 1 <= starter && starter <= children)
		for (ring->one = head; ring->one->numb != starter;
			ring->one = ring->one->next);
}

/* 销毁剩余小孩 */
void ring_deinit (RING* ring) {
	while (ring->one)
		ring->one = destroy_child (ring->one);
}

/* 出列 */
int ring_dequeue (RING* ring, CHILD* child) {
	int left = 0;

	if (ring->one) {
		CHILD* prev = NULL;
		for (prev = ring->one; prev->next != ring->one; prev = prev->next)
			++left;

		int i;
		for (i = 2; i <= ring->gap; ++i) {
			ring->one = ring->one->next;
			prev = prev->next;
		}

		*child = *ring->one;

		if (ring->one = destroy_child (ring->one))
			prev->next = ring->one;
	}

	return left;
}

/* 显示 */
void ring_show (RING* ring) {
	if (ring->one) {
		CHILD* child = ring->one;
		do {
			printf ("%d ", child->numb);
		}	while ((child = child->next) != ring->one);
	}
}

/* 主函数 */
int main (int argc, char* argv[]) {
	if (argc < 4) {
		printf ("用法：%s <人数> <起点> <间隔>\n", argv[0]);
		return -1;
	}

	RING ring;
	ring_init (&ring, atoi (argv[1]), atoi (argv[2]), atoi (argv[3]));

	for (;;) {
		ring_show (&ring);

		CHILD child;
		if (ring_dequeue (&ring, &child))
			printf ("- %d号出列...\n", child.numb);
		else {
			printf ("- %d号完胜！\n", child.numb);
			break;
		}
	}

	ring_deinit (&ring);
	return 0;
}
