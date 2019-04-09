# C/C++概念题

###### 1. 请填写BOOL , float, 指针变量 与“零值”比较的 if 语句
提示：这里“零值”可以是0, 0.0 , FALSE或者“空指针”。例如 int 变量 n 与“零值”比较的 if 语句为： if ( n == 0 ) 和 if ( n != 0 ) 以此类推。
<1> BOOL  flag 与“零值”比较的 if 语句: if ( flag ) 或  if ( !flag )
<2> float  x 与“零值”比较的 if 语句：
```cpp
const float EPSINON = 0.00001;
if ((x >= - EPSINON) && (x <= EPSINON) // 不可将浮点变量用“==”或“！=”与数字比较，应该设法转化成“>=”或“<=”此类形式
```
<3> char * p 与“零值”比较的 if 语句： if (p == NULL) 或 if (p != NULL)

###### 2. 头文件中的 ifndef/define/endif 干什么用？
* 防止该头文件被重复引用

###### 3. #include  <filename.h>   和  #include  “filename.h” 有什么区别？
* 对于#include  <filename.h> ，编译器从标准库路径开始搜索 filename.h。对于#include  “filename.h” ，编译器从用户的工作路径开始搜索 filename.h

###### 4. const 有什么用途？（请至少说明两种）
1. const 修饰变量
 - const修饰指针变量时：
 - a) 只有一个const，如果const位于*左侧，表示指针所指数据是常量，不能通过解引用修改该数据；指针本身是变量，可以指向其他的内存单元
 - b) 只有一个const，如果const位于*右侧，表示指针本身是常量，不能指向其他内存地址；指针所指的数据可以通过解引用修改
 - c) 两个const，* 左右各一个，表示指针和指针所指数据都不能修改
2. const修饰函数参数
3. const修饰成员函数
 - a) const修饰的成员函数不能修改任何的成员变量(mutable修饰的变量除外)
 - b) const成员函数不能调用非onst成员函数，因为非const成员函数可以会修改成员变量
4. const修饰函数返回值
 - a) 指针传递
 - 如果返回const data,non-const pointer，返回值也必须赋给const data,non-const pointer。因为指针指向的数据是常量不能修改
 - b) 值传递
 - 如果函数返回值采用“值传递方式”，由于函数会把返回值复制到外部临时的存储单元中，加const 修饰没有任何价值。所以，对于值传递来说，加const没有太多意义

###### 5. 在C++ 程序中调用被 C编译器编译后的函数，为什么要加 extern “C”声明？
* C++语言支持函数重载，C语言不支持函数重载。函数被C++编译后在库中的名字与C语言的不同。假设某个函数的原型为： void foo(int x, int y); 该函数被C编译器编译后在库中的名字为_foo，而C++编译器则会产生像_foo_int_int之类的名字。C++提供了C连接交换指定符号extern“C”来解决名字匹配问题。

###### 6.编写strcpy函数,已知strcpy函数的原型是char * strcpy(char * strDest, const char * strSrc);	其中strDest是目的字符串，strSrc是源字符串。
1. 不调用C++/C的字符串库函数，请编写函数 strcpy.
```cpp
char * strcpy(char * strDest, const char * strSrc);
{
  assert((strDest!=NULL) && (strSrc !=NULL));
  char * address = strDest;
  while( (*strDest++ = * strSrc++) != '\0' )
    NULL ;
  return address ;
}
```
2. strcpy能把strSrc的内容复制到strDest，为什么还要char * 类型的返回值？
* 为了实现链式表达式。例如:int length = strlen( strcpy( strDest, “hello world”) );

###### 7.交换两个变量的值，不使用第三个变量
```cpp
// 1 使用 + - 只能对int
a = a + b;
b = a - b;
a = a - b;
// 2 使用 异或^ char..
b = a^b;
a = a^b;
b = a^b;
```

###### 8.要对绝对地址0x100000赋值，我们可以用 (unsigned int*)0x100000 = 1234; 那么要是想让程序跳转到绝对地址是0x100000去执行，应该怎么做？
 - \*((void (\*)())0x100000)(); 首先要将0x100000强制转换成函数指针,即: (void (\*)())0x100000 然后再调用它: \*((vovd (\*)())0x100000)(); 用typedef可以看得更直观些: typedef void(\*)() voidFuncPtr; \*((voidFuncPtr)0x100000)();

###### 9.引用与指针有什么区别？
 - 1) 引用必须被初始化，指针不必。
 - 2) 引用初始化以后不能被改变，指针可以改变所指的对象。
 - 3) 不存在指向空值的引用，但是存在指向空值的指针。
