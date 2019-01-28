#include <stdio.h>

struct bytedata
{
  unsigned bit_2:2;   /*位段a，占2位*/
  unsigned:6;         /*无名位段，占6位，但不能访问*/
  unsigned:0;         /*无名位段，占0位，表下一位段从下一字边界开始*/
  unsigned bit_10:10; /*位段b，占10位*/
  int i;              /*成员i，从下一字边界开始*/
};

int main(int argc, char const *argv[])
{
  bytedata dt = {0};
  printf("amplitude before: bit_2(%d)\n", dt.bit_2);
  dt.bit_2 = 10; // 超出范围，最大现实2
  printf("amplitude after: bit_2(%d)\n", dt.bit_2);
  printf("sizeof(bytedata) (%d)\n", sizeof(bytedata));
	
  return 0;
}
