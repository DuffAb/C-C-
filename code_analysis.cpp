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
void analysis_i_plus_plus()
{
	int i = 1;
	int j = 2;
	int k = i+++j;
	printf("i+++j(%d)\n", k);
	std::cout << k << std::endl;
	i = 1;
	j = 2;
	k = (i++) + j;
	printf("(i++)+j(%d)\n", k);
	std::cout << k << std::endl;
	i = 1;
	j = 2;
	k = i + (++j);
	printf("i+(++j)(%d)\n", k);
	std::cout << k << std::endl;
	i = 1;
	j = 2;
	k = (++i) + j;
	printf("(++i)+j(%d)\n", k);
	std::cout << k << std::endl;
}
// 运行结果：3 3 4 4 分析：根据输出，

int main(){
	int action;
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
