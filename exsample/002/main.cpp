#include <stdio.h>
#include <string.h>

class OString
{
public:
  OString(const char *str = NULL);           // 普通构造函数
  OString(const OString &other);              // 拷贝构造函数
  ~ OString(void);                           // 析构函数

public:
  char* Oc_str();
  OString & operator=(const OString &other);  // 赋值函数
  
private:
  char    *m_data;                          // 用于保存字符串
};


// OString的析构函数
OString::~OString(void)
{
  delete [] m_data;
}

// OString的普通构造函数             
OString::OString(const char *str)
{
  if(str == NULL)
  {
    m_data = new char[1];    // 若能加 NULL 判断则更好
    *m_data = '\0';                      
  }                                        
  else
  {
    int length = strlen(str);           
    m_data = new char[length + 1];  // 若能加 NULL 判断则更好      
    strcpy(m_data, str);                
  }
}

// 拷贝构造函数
OString::OString(const OString &other)
{ 
  int length = strlen(other.m_data);   
  m_data = new char[length+1];      // 若能加 NULL 判断则更好    
  strcpy(m_data, other.m_data);         
}

char* OString::Oc_str()
{
  return m_data;
}

// 赋值函数
OString & OString::operator=(const OString &other)
{
  // (1) 检查自赋值
  if(this == &other)
    return *this;
  
  // (2) 释放原有的内存资源
  delete [] m_data;
    
  //（3）分配新的内存资源，并复制内容
  int length = strlen(other.m_data);  
  m_data = new char[length+1];         // 若能加 NULL 判断则更好
  strcpy(m_data, other.m_data);
    
  //（4）返回本对象的引用
  return *this;
} 

int sum(int a) 
{    
auto  c=0;    
static int b=3;  
c+=1;  
b+=2;  
printf("%d  %d  %d\n", a, b, c);
return(a+b+c); 
}  

int main(int argc, char const *argv[])
{
  OString ostr01("ldf");
  printf("ostr01(%s)\n", ostr01.Oc_str());
  OString ostr02 = ostr01;
  printf("ostr02(%s)\n", ostr02.Oc_str());
  int I;  
int a=2;  
for(I=0;I <5;I++)  
{    
printf("%d,", sum(a));  
}

  return 0;
}
