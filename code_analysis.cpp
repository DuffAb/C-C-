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
	int i = 1, j = 2;
	int k = i+++j;
	std::cout << "i+++j = " << k << std::endl;
	
	k = product(i++);// 先整体运算完，i再自增2次
	std::cout << "product(i++) = " << k << std::endl;
	k = product(++i);// 先自增2次再运算
	std::cout << "product(i++) = " << k << std::endl;

	i = 1, j = 2;
	std::cout << boolalpha << !i&&j++ << std::endl;
}
// 运行结果：i+++j= 3 、(i++)+j = 3 、i+(++j) = 4 、(++i)+j = 4 
// 分析：根据输出，i+++j 从左向右运算，++运算符优先级高于+运算符。 i++:先把i值返回再自增。 ++i:先自增再把i值返回


// 2

int main(){
	int action;
	printf("选择想要分析的代码编号：");
	scanf("%d", &action);
	while (getchar() != '\n' && getchar() != EOF);
	switch (action)
	{
		case 1:
		analysis_i_plus_plus();
		break;
	}
	return 0;
}
