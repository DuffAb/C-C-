
struct bytedata
{
  unsigned bit_2:2;   /*位段a，占2位*/
  unsigned:6;         /*无名位段，占6位，但不能访问*/
  unsigned:0;         /*无名位段，占0位，表下一位段从下一字边界开始*/
  unsigned bit_10:10; /*位段b，占10位*/
  int i;              /*成员i，从下一字边界开始*/
}data_t;

int main(int argc, char const *argv[])
{
	printf("最大描述符数量(%d)\n", OGetMaxDescriptorNumber());
	data_t dt;
  printf("bit_2(%d)\n", dt.bit_2);
  printf("%sizeof(data_t) (%d)\n", sizeof(data_t));
	return 0;
}
