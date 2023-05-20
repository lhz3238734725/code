#include <iostream>
#include <string>

using namespace std;
/**
*stl容器类string类的使用
*string是C++风格的字符串，而string本质上是一个类
*@autor lhz
*@time 20230515
*/
int main(int argc, char* argv[]) {

	/*
	*构造函数 
	*string();          		      //创建一个空的字符串 例如: string str;
	*string(const char* s);	          //使用字符串s初始化
	*string(const string & str);      //使用一个string对象初始化另一个string对象
	*string(int n, char c);           //使用n个字符c初始化
	*/
	std::string* s1 = new std::string();
	std::string* s2 = new std::string("test string");
	std::string* s3 = new std::string(*s2);
	std::string* s4 = new std::string(10, 0);

	std::cout << *s1 << std::endl;
	std::cout << *s2 << std::endl;
	std::cout << *s3 << std::endl;
	std::cout << *s4 << std::endl;


	/*
	*赋值操作
	*string& operator=(const char* s);					//char*类型字符串 赋值给当前的字符串
	*string& operator=(const string &s);				//把字符串s赋给当前的字符串
	*string& operator=(char c);                         //字符赋值给当前的字符串
	*string& assign(const char *s);						//把字符串s赋给当前的字符串
	*string& assign(const char *s, int n);				//把字符串s的前n个字符赋给当前的字符串
	*string& assign(const string &s);					//把字符串s赋给当前字符串
	*string& assign(int n, char c);						//用n个字符c赋给当前字符串
	*/
	* s1 = "hello world";
	std::cout << *s1 << std::endl;

	*s1 = *s2;
	std::cout << *s1 << std::endl;

	*s1 = 'a';
	std::cout << *s1 << std::endl;

	s1->assign("hello world");
	std::cout << *s1 << std::endl;

	s1->assign("hello world", 1);
	std::cout << *s1 << std::endl;

	s1->assign(*s3);
	std::cout << *s1 << std::endl;

	s1->assign(10, '0');
	std::cout << *s1 << std::endl;

	/*
	*字符串拼接
	*string& operator+=(const char* str);						//重载+=操作符
	*string& operator+=(const char c);							//重载+=操作符
	*string& operator+=(const string& str);						//重载+=操作符
	*string& append(const char *s);                             //把字符串s连接到当前字符串结尾
	*string& append(const char *s, int n);						//把字符串s的前n个字符连接到当前字符串结尾
	*string& append(const string &s);                           //同operator+=(const string& str)
	*string& append(const string &s, int pos, int n);			//字符串s中从pos开始的n个字符连接到字符串结尾
	*/
	*s1 += "123456";
	std::cout << *s1 << std::endl;

	*s1 += '7';
	std::cout << *s1 << std::endl;

	*s1 += *s2;
	std::cout << *s1 << std::endl;

	s1->append("123456");
	std::cout << *s1 << std::endl;

	s1->append("789", 1);
	std::cout << *s1 << std::endl;

	s1->append(*s2);
	std::cout << *s1 << std::endl;

	s1->append(*s2, 1, 1);
	std::cout << *s1 << std::endl;

	/**
	*字符串查找和替换
	*int find(const string& str, int pos = 0) const;				//查找str第一次出现位置,从pos开始查找
	*int find(const char* s, int pos = 0) const;                    //查找s第一次出现位置,从pos开始查找
	*int find(const char* s, int pos, int n) const;					//从pos位置查找s的前n个字符第一次位置
	*int find(const char c, int pos = 0) const;                     //查找字符c第一次出现位置
	*int rfind(const string& str, int pos = npos) const;			//查找str最后一次位置,从pos开始查找
	*int rfind(const char* s, int pos = npos) const;				//查找s最后一次出现位置,从pos开始查找
	*int rfind(const char* s, int pos, int n) const;				//从pos查找s的前n个字符最后一次位置
	*int rfind(const char c, int pos = 0) const;                    //查找字符c最后一次出现位置
	*string& replace(int pos, int n, const string& str);			//替换从pos开始n个字符为字符串str
	*string& replace(int pos, int n,const char* s);                 //替换从pos开始的n个字符为字符串
	*/
	int index;

	index = s1->find(*s2, 0);
	std::cout << index << std::endl;

	index = s1->find("123", 0);
	std::cout << index << std::endl;

	index = s1->find("123", 0, 1);
	std::cout << index << std::endl;

	index = s1->find('1', 0);
	std::cout << index << std::endl;

	index = s1->rfind(*s2, 0);
	std::cout << index << std::endl;

	index = s1->rfind("123", 0);
	std::cout << index << std::endl;

	index = s1->rfind("123", 0, 1);
	std::cout << index << std::endl;

	index = s1->rfind('1', 0);
	std::cout << index << std::endl;

	s1->replace(0, sizeof(*s2), *s2);
	std::cout << *s1 << std::endl;

	s1->replace(0, sizeof("hello"), "hello");
	std::cout << *s1 << std::endl;

	/**
	*字符串之间的比较
	*int compare(const string &s) const;	//与字符串s比较
	*int compare(const char *s) const;      //与字符串s比较
	*/
	int res;
	res = s1->compare(*s2);
	std::cout << res << std::endl;

	res = s1->compare("123");
	std::cout << res << std::endl;

	/*
	*string中单个字符存取方式有两种
	*char& operator[](int n);			//通过[]方式取字符
	*char& at(int n);                   //通过at方法获取字符
	*/

	std::cout << (*s1)[1] << std::endl;
	std::cout << s1->at(1) << std::endl;

	/*
	*对string字符串进行插入和删除字符操作
	*string& insert(int pos, const char* s);                //插入字符串
	*string& insert(int pos, const string& str);			//插入字符串
	*string& insert(int pos, int n, char c);                //在指定位置插入n个字符c
	*string& erase(int pos, int n = npos);                  //删除从Pos开始的n个字符
	*/
	s1->insert(0, "lhz");
	std::cout << *s1 << std::endl;

	s1->insert(0, *s2);
	std::cout << *s1 << std::endl;

	s1->insert(0, 1, '1');
	std::cout << *s1 << std::endl;

	s1->erase(0, 1);
	std::cout << *s1 << std::endl;

	/*
	* 从字符串中获取想要的子串
	* string substr(int pos = 0, int n = npos) const;   //返回由pos开始的n个字符组成的字符串
	*/
	*s1 = s1->substr(0, 5);
	std::cout << *s1 << std::endl;

	system("pause");

	delete s1, s2, s3, s4;

	return 0;
}