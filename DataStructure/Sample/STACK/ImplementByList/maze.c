/* 老鼠走迷宫
 *
 * @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
 * ........@@  @XXXXXX@@XXXXXXX@@
 * @@@  @ ......@XXX@XXXXXXXXX@X@
 * @@@ @@    @@..@XXX@@XXXXX@@XX@
 * @  @    @    .......@XXXX@@X@@
 * @@       @   @  @@@..XXXXX@XX@
 * @     @        @   ..@@XX@@@X@
 * @@@@    @@ @ @ @  @.@@XX@X@XX@
 * @@ @@    @  @    @ ...@@XXXXX@
 * @     @   @@    @ @  .....XX@@
 * @   @@@  @@@ @@       @  .@@ @
 * @    @   @  @      @     ..@ @
 * @ @        @  @         @@.@ @
 * @ @@    @@    @ @@    @   ...>
 * @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
 * 共走169步，其中43步有效。
 * 我成功了！哈哈哈哈:)
 */
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <unistd.h>
#include <termios.h>
#include <sys/ioctl.h>
#include "sl.h"

/* 空间字符 */
#define SPACE_MOUSE   '*' /* 老鼠 */
#define SPACE_WAY     ' ' /* 通路 */
#define SPACE_WALL    '@' /* 墙壁 */
#define SPACE_PASS    '.' /* 足迹 */
#define SPACE_IMPASSE 'X' /* 死路 */

/* 行进方向 */
#define DIR_RIGHT 0 /* 向右 */
#define DIR_DOWN  1 /* 向下 */
#define DIR_LEFT  2 /* 向左 */
#define DIR_UP    3 /* 向上 */

/* 老鼠字符 */
const char* g_mouse = ">V<^";

/* 老鼠 */
typedef struct Mouse {
	int   x;     /* 水平坐标 */
	int   y;     /* 垂直坐标 */
	int   dir;   /* 行进方向 */
	int   total; /* 总步数 */
	int   valid; /* 有效步 */
	STACK brain; /* 大脑 */
}	MOUSE;

/* 老鼠初始化 */
void mouse_init (MOUSE* mouse, int x, int y, int dir) {
	mouse->x = x;
	mouse->y = y;
	mouse->dir = dir;
	mouse->total = 0;
	mouse->valid = 0;
	stack_init (&mouse->brain);
}

/* 老鼠终结化 */
void mouse_deinit (MOUSE* mouse) {
	stack_deinit (&mouse->brain);
}

/* 老鼠记忆 */
void mouse_remember (MOUSE* mouse, int dir) {
	stack_push (&mouse->brain, dir);
}

/* 老鼠回忆 */
int mouse_recall (MOUSE* mouse) {
	return stack_pop (&mouse->brain);
}

/* 老鼠前进 */
void mouse_go (MOUSE* mouse, int dir) {
	switch (dir) {
		case DIR_RIGHT:
			++mouse->x;
			break;
		case DIR_DOWN:
			++mouse->y;
			break;
		case DIR_LEFT:
			--mouse->x;
			break;
		case DIR_UP:
			--mouse->y;
			break;
	}

	mouse_remember (mouse, mouse->dir = dir);

	++mouse->total;
	++mouse->valid;
}

/* 老鼠后退 */
void mouse_back (MOUSE* mouse) {
	switch (mouse_recall (mouse)) {
		case DIR_RIGHT:
			--mouse->x;
			mouse->dir = DIR_LEFT;
			break;
		case DIR_DOWN:
			--mouse->y;
			mouse->dir = DIR_UP;
			break;
		case DIR_LEFT:
			++mouse->x;
			mouse->dir = DIR_RIGHT;
			break;
		case DIR_UP:
			++mouse->y;
			mouse->dir = DIR_DOWN;
			break;
	}

	++mouse->total;
	--mouse->valid;
}

/* 迷宫 */
typedef struct Maze {
	int   cx;    /* 宽度 */
	int   cy;    /* 高度 */
	char* space; /* 空间 */
	MOUSE mouse; /* 老鼠 */
}	MAZE;

/* 迷宫初始化 */
void maze_init (MAZE* maze, int cx, int cy) {
	maze->cx = cx;
	maze->cy = cy;
	maze->space = malloc (cx * cy * sizeof (char));
	mouse_init (&maze->mouse, 0, 1, DIR_RIGHT);

	srand (time (NULL));

	char (*space)[cx] = (char (*)[cx])maze->space;
	int y, x;

	for (y = 0; y < cy; ++y)
		for (x = 0; x < cx; ++x)
			if (x == maze->mouse.x && y == maze->mouse.y)
				space[y][x] = SPACE_MOUSE;
			else
			if ((y == 1 && x < 4) || (y == cy - 2 && x > cx - 5))
				space[y][x] = SPACE_WAY;
			else
			if (y == 0 || y == cy - 1 || x == 0 || x == cx - 1)
				space[y][x] = SPACE_WALL;
			else
				space[y][x] = rand () % 4 ? SPACE_WAY : SPACE_WALL;
}

/* 迷宫终结化 */
void maze_deinit (MAZE* maze) {
	free (maze->space);
	mouse_deinit (&maze->mouse);
}

/* 显示迷宫 */
void maze_show (MAZE* maze) {
	char (*space)[maze->cx] = (char (*)[maze->cx])maze->space;
	int y, x;

	for (y = 0; y < maze->cy; ++y) {
		for (x = 0; x < maze->cx; ++x) {
			switch (space[y][x]) {
				case SPACE_MOUSE:
					printf ("\033[;;31m");
					break;
				case SPACE_WALL:
					printf ("\033[;;34m");
					break;
				case SPACE_PASS:
					printf ("\033[;;32m");
					break;
				case SPACE_IMPASSE:
					printf ("\033[;;35m");
					break;
			}
			printf ("%c\033[0m", space[y][x] == SPACE_MOUSE ?
				g_mouse[maze->mouse.dir] : space[y][x]);
		}
		printf ("\n");
	}

	printf ("共走%d步，其中%d步有效。\n", maze->mouse.total,
		maze->mouse.valid);
}

/* 从标准输入读取一个字符，不回显不回车 */
int getch (void) {
	struct termios old;
	ioctl (STDIN_FILENO, TCGETS, &old);

	struct termios new = old;
	new.c_lflag &= ~(ECHO | ICANON);
	ioctl (STDIN_FILENO, TCSETS, &new);

	int ch = getchar ();

	ioctl (STDIN_FILENO, TCSETS, &old);
	return ch;
}

/* 是否退出 */
bool maze_quit (void) {
	printf ("按<Q>键退出，按其它键继续...");
	int ch = getch ();
	printf ("\n");

	return strchr ("Qq", ch) != NULL;
}

/* 下一步 */
bool maze_step (MAZE* maze) {
	char (*space)[maze->cx] = (char (*)[maze->cx])maze->space;

	int y = maze->mouse.y;
	int x = maze->mouse.x;
	space[y][x] = SPACE_PASS;

	if (x + 1 <= maze->cx - 1 && space[y][x + 1] == SPACE_WAY)
		mouse_go (&maze->mouse, DIR_RIGHT);
	else
	if (y + 1 <= maze->cy - 1 && space[y + 1][x] == SPACE_WAY)
		mouse_go (&maze->mouse, DIR_DOWN);
	else
	if (x - 1 >= 0 && space[y][x - 1] == SPACE_WAY)
		mouse_go (&maze->mouse, DIR_LEFT);
	else
	if (y - 1 >= 0 && space[y - 1][x] == SPACE_WAY)
		mouse_go (&maze->mouse, DIR_UP);
	else {
		space[y][x] = SPACE_IMPASSE;
		mouse_back (&maze->mouse);
	}

	y = maze->mouse.y;
	x = maze->mouse.x;
	space[y][x] = SPACE_MOUSE;

	maze_show (maze);

	if (y == maze->cy - 2 && x == maze->cx - 1) {
		printf ("我成功了！哈哈哈哈:)\n");
		return false;
	}

	if (y == 1 && x == 0) {
		printf ("我要死了！呜呜呜呜:(\n");
		return false;
	}

	return true;
}

/* 运行 */
void maze_run (MAZE* maze) {
	for (maze_show (maze); ! maze_quit () && maze_step (maze););
}

/* 主函数 */
int main (int argc, char* argv[]) {
	if (argc < 3) {
		printf ("用法：%s <迷宫宽度> <迷宫高度>\n", argv[0]);
		return -1;
	}

	MAZE maze;
	maze_init (&maze, atoi (argv[1]), atoi (argv[2]));

	maze_run (&maze);

	maze_deinit (&maze);
	return 0;
}
