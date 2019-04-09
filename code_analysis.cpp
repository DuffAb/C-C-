// File Name: code_analysis.cpp
// Author: liangdefeng
// Created Time: 2019年02月19日 星期二 11时05分46秒

#include<vector>
#include<list>
#include<map>
#include<set>
#include<deque>
#include<stack>
#include<bitset>
#include<algorithm>
#include<functional>
#include<numeric>
#include<utility>
#include<sstream>
#include<iostream>
#include<iomanip>
#include<cstdio>
#include<cmath>
#include<cstdlib>
#include<cstring>
#include<ctime>

using namespace std;
// 1.分析下面代码的输出结果，i++ 以及 ++i, 还有运算顺序
#define product(x) (x*x)
void analysis_i_plus_plus()
{
	// 1.i++ 与 ++i的问题
	int i = 1, j = 2;
	int k = i+++j;
	// i+++j 从左向右运算，++运算符优先级高于+运算符。 i++:先把i值返回再自增。 ++i:先自增再把i值返回
	std::cout << "i+++j = " << k << std::endl;// 运行结果：i+++j = 3

	// 2.宏定义
	i = 3;
	k = product(i++);// 先整体运算完，i再自增2次
	std::cout << "product(i++) = " << k << std::endl;// 运行结果：product(i++) = 12 (g++ 编译器) | product(i++) = 9 (VC编译器)
	k = product(++i);// 先自增2次再运算
	std::cout << "product(i++) = " << k << std::endl;// 运行结果：product(i++) = 49 (g++ 编译器) | product(i++) = 49(VC编译器)

	// 3.逻辑运算符的运算
	i = 1, j = 2;
	std::cout << boolalpha << (!i&&j++) << std::endl;// 运行结果：false

	// 4.类型转换，这个例子中是 int 转 unsigned int
	unsigned int a4 = 6;
	int b4 = -20;
	(a4 + b4 > 6)?puts("> 6") :puts("<= 6");// 运行结果：> 6
	// 在32位机上，unsigned int 最大可表示2^32 - 1，int最大可表示2^31-1，这样int就转为了unsigned int，
	// 由于b4<0，即b4的最高位符号位是1，转为unsigned int后最高为不再是符号位，而是一个最高位的正数，于是两者相加就会是一个很大的正数了


}
// 运行结果：i+++j = 3、product(i++) = 6、product(i++) = 36、false
// 分析：


// 2.(int)a 、 &a 、 (int)&a 、 (int&)a 的区别
void analysis_int_a()
{
	float a = 1.0f;
	cout << sizeof(int) << endl; //4
	cout << sizeof(float) << endl;//4

	cout << (int)a << endl; // 将 1.0f 浮点型转换为整型 1
	cout << &a << endl;     // 取a的地址十六进制 0012FF7C
	cout << (int)&a << endl;// (int)&把a的地址强制转换成十进制的整数 1245052
	cout << (int&)a << endl;// (int&)a将a的引用强制转换为整型，意思是a所在的内存，本来定义的时候为float类型，并初始化为1.0f，但现在我要按int类型解释这段内存
	// (int&)a 相当于 *(int*)&a 1.0f在内存中的存储为 0 011 1111 1 000 0000 0000 0000 0000 0000
	// 把它按整型数解释为2^29+2^28+2^27+2^26+2^25+2^24+2^23 = 1065353216
	cout << boolalpha << ((int)a == (int&)a) << endl; // 输出：false  因为1 != 1065353216

	float b = 0.0f;
	cout << (int)b << endl; // 0
	cout << (int&)b << endl;// 0
	cout << boolalpha << ((int)b == (int&)b) << endl; // 输出：true, 因为 0 == 0
}

// 3
void analysis_str()
{
	char str1[] = "abc";
	char str2[] = "abc";
	const char str3[] = "abc";
	const char str4[] = "abc";
	const char* str5 = "abc";
	const char* str6 = "abc";
	cout << boolalpha << (str1 == str2) << endl; // 输出 false
	cout << boolalpha << (str3 == str4) << endl; // 输出 false
	cout << boolalpha << (str5 == str6) << endl; // 输出 true
	// 前4个str是字符数组，系统会分配各自的内存，后两个是指针，指向同一个常量字符串
}

// 4.实现一个函数，把一个字符串中的字符从小写转为大写
void analysis_upper_case(const char * src, char * dest)
{
	// int *p = NULL;// sizeof(p) = 4 (32-bit) | sizeof(p) = 8 (64-bit)
	// printf("%d %d %d %d\n", sizeof(p), sizeof(src), sizeof(src[0]), sizeof(src)/ sizeof(src[0]));
	size_t len;
	len = strlen(src);
	for (int i = 0; i < len; ++i)
	{
		if ('a' <= src[i] && src[i] < 'z')
		{
			dest[i] = src[i]-'a'+'A';
		}
	}
	return ;
}

// 5. 将ASCII字符以16进制表示, 但是不能处理中文
char * analysis_ascii_char2hex(const char * src)
{
	size_t len = strlen(src);
	char * dest = (char*) malloc(len * 3 * sizeof(char));
	for (int i = 0; i < len; ++i)
	{
		char ch = src[i] / 0x10 + '0';
		char cl = src[i] % 0x10 + '0';
		if (ch > '9')
		{
			ch += ('A' - '9' - 1);
		}
		if (cl > '9')
		{
			cl += ('A' - '9' - 1);
		}
		dest[i*3+0]=ch;
		dest[i*3+1]=cl;
		dest[i*3+2]=' ';
	}
	return dest;
}

// 6.数组指针（也称行指针）与 指针数组
void analysis_array_pointer_and_pointer_array()
{
	// 数组指针（也称行指针）
	// 定义：int (*p)[n];
	// ()优先级高，首先说明p是一个指针，指向一个整型的一维数组，这个一维数组的长度是n，
	// 也可以说是p的步长。也就是说执行p+1时，p要跨过n个整型数据的长度。

	// 如要将二维数组赋给一指针，应这样赋值：
	int a[3][4] = {{1,2,3,4}, {5,6,7,8}, {9,10,11,12}};
	int (*array_pointer)[4];  //该语句是定义一个数组指针，指向含4个元素的一维数组。
 	array_pointer = a;        //将该二维数组的首地址赋给p，也就是a[0]或&a[0][0]
 	for (int i = 0; i < 3; ++i)
 	{
 		printf("{%d, %d, %d, %d}\n", array_pointer[0][0], array_pointer[0][1], array_pointer[0][2], array_pointer[0][3]);
 		array_pointer++;          //该语句执行过后，也就是p=p+1;p跨过行a[0][]指向了行a[1][]
 	}
 	// 所以数组指针也称指向一维数组的指针，亦称行指针


 	// 指针数组
	// 定义 int *p[n];
	// []优先级高，先与p结合成为一个数组，再由int*说明这是一个整型指针数组，它有n个指针类型的数组元素。
	// 这里执行p+1是错误的，这样赋值也是错误的：p=a；因为p是个不可知的表示，只存在p[0]、p[1]、p[2]...p[n-1],
	// 而且它们分别是指针变量可以用来存放变量地址。但可以这样 *p=a; 这里*p表示指针数组第一个元素的值，a的首地址的值。
	// 如要将二维数组赋给一指针数组:
	int *pointer_array[3];
	for(int i = 0; i < 3; ++i)
	{
		pointer_array[i] = a[i];
		printf("{%d, %d, %d, %d}\n", pointer_array[i][0], pointer_array[i][1], pointer_array[i][2], pointer_array[i][3]);
	}
	// 这里int *p[3] 表示一个一维数组内存放着三个指针变量，分别是p[0]、p[1]、p[2]
	// 所以要分别赋值。

	// 这样两者的区别就豁然开朗了，数组指针只是一个指针变量，似乎是C语言里专门用来指向二维数组的，
	// 它占有内存中一个指针的存储空间。指针数组是多个指针变量，以数组形式存在内存当中，占有多个指针的存储空间。
	// 还需要说明的一点就是，同时用来指向二维数组时，其引用和用数组名引用都是一样的。
	// 比如要表示数组中i行j列一个元素：
	// *(p[i]+j)、*(*(p+i)+j)、(*(p+i))[j]、p[i][j]

	// 优先级：()>[]>*
}

//7.不重复地输出升序数组中的元素
void analysis_no_repeat_output_array(char[] arr, int len){
	if (len < 1) {
		return;
	}
	else if (len == 1) {
		printf("%s\n", arr[0]);
	}
	else {
		for (size_t i = 0; i < len; i++) {
			if (arr[i] != arr[i + 1]) {
				printf("%c ", arr[i]);
			}
			i++;
		}
	}
}

// 8.将长型转换为字符串
char * analysis_ltoa(long value) {
	long dloop = 1;
	int len = 1;
	while (!(value / dloop < 10)) {
		dloop *= 10;
		++len;
	}

	char* str = (char*)malloc(len * sizeof(char));
	for (int i = 0; i < len; ++i)
	{
		str[i] = value / dloop + '0';
		value = value % dloop;
		dloop /= 10;
	}
	str[len] = '\0';

	return   str;
}

// 9.输入一个字符串，输出长型整数
long analysis_atol(const char* str) {
	long result = 0;
	long loop = 1;
	char c = *str;
	while (c != '\0')
	{
		if ('0' <= c && c <= '9')
		{
			result = result * 10 + c - '0';
		}
		str++;
		c = *str;
	}
	return result;
}

// 10.
void analysis_10(){
	int a[5]={1,2,3,4,5};
   int *ptr=(int *)(&a+1);
   printf("%d,%d",*(a+1),*(ptr-1)); // 2 , 5
}
// *(a+1)就是a[1]，*(ptr-1)就是a[4], 执行结果是2, 5。&a+1不是首地址+1，系统会认为加一个a数组的偏移，是偏移了一个数组的大小(本例是5个int)。
// int *ptr=(int *)(&a+1); 则ptr实际是&(a[5]),也就是a+5
// 原因如下：
// &a是数组指针，其类型为 int (*)[5]; 而指针加1要根据指针类型加上一定的值，不同类型的指针+1之后增加的大小不同;
// a是长度为5的int数组指针，所以要加 5*sizeof(int)。所以ptr实际是a[5]。但是ptr与(&a+1)类型是不一样的(这点很重要)，
// 所以prt-1只会减去sizeof(int*)。a,&a的地址是一样的，但意思不一样，a是数组首地址，也就是a[0]的地址，&a是对象(数组)首地址，
// a+1是数组下一元素的地址，即a[1],&a+1是下一个对象的地址，即a[5]。


// 11.请写一个C函数，若处理器是BigEndian的，则返回 0；若是LittleEndian的，则返回 1
int analysis_11_checkCPU(){
	union check{
		int big;
		char little;
	}c;
	c.big = 1;
	return (c.little == 1);
}

// 12. 统计一个数的二进制中1的个数
int analysis_12_count_binary_1(int value){
	int count_v = 0;
	while(value){
		count_v ++;
		value = value & (value - 1);
	}
	return count_v;
}


int main(){
	int action;
	printf("选择想要分析的代码编号：");
	scanf("%d", &action);
	while (getchar() != '\n' && getchar() != EOF);
	switch (action)
	{
		case 1:	analysis_i_plus_plus();	break;
		case 2:	analysis_int_a(); break;
		case 3: analysis_str();	  break;
		case 4:{
			char src[] = "abfdasfdgds0";
			char *dest = (char*)malloc(strlen(src) * sizeof(char));
			analysis_upper_case(src, dest);
			cout << dest << endl;
			free(dest);
		}
		case 5:{
			char src[] = "abfdasfdgds中国";// 处理不了 "中国"
			char * dest = analysis_ascii_char2hex(src);
			cout << dest << endl;
			free(dest);
		}
		case 6: analysis_array_pointer_and_pointer_array(); break;
		case 7: {
			const char* arr = "abbccddeef";
			analysis_no_repeat_output_array((char*)arr, 10);
			break;
		}
		case 8: analysis_ltoa(1234560789);	 break;
		case 9: analysis_atol(123-.0o=-456); break;
	}
	return 0;
}
