#include <iostream>
#include <string>
#include <functional>

/*
* 概念：
* 重载函数调用操作符的类，其对象常称为函数对象
* 函数对象使用重载的()时，行为类似函数调用，也叫仿函数
* 本质：
* 函数对象(仿函数)是一个类，不是一个函数
* @autor lhz
* @time 20230524
*/

//1、函数对象在使用时，可以像普通函数那样调用, 可以有参数，可以有返回值
class MyAdd
{
public:
	int operator()(int v1, int v2) {
		return v1 + v2;
	}
};

void test1() {
	MyAdd myadd;
	std::cout << myadd(10, 10) << std::endl;
}

//2、函数对象可以有自己的状态
class MyPrint
{
public:
	int count;
	MyPrint() {
		count = 0;
	}
	void operator()(std::string& str) {
		std::cout << str <<count++ << std::endl;
	}

};

void test2() {
	MyPrint myPrint;
	std::string str("hello");

	myPrint(str);
	myPrint(str);
	myPrint(str);
}

//3、函数对象可以作为参数传递
void test3(MyPrint& mp, std::string str) {
	mp(str);
}

/*
* 返回bool类型的仿函数称为谓词
* 如果operator()接受一个参数，那么叫做一元谓词
* 如果operator()接受两个参数，那么叫做二元谓词
*/


/*
* STL内建了一些函数对象
* 算术仿函数 
* 关系仿函数 
* 逻辑仿函数 
* 使用内建函数对象，需要引入头文件 #include<functional>
*/

/*
* 算术仿函数 
* template<class T> T plus<T>					//加法仿函数
* template<class T> T minus<T>					//减法仿函数
* template<class T> T multiplies<T>				//乘法仿函数
* template<class T> T divides<T>				//除法仿函数
* template<class T> T modulus<T>				//取模仿函数
* template<class T> T negate<T>					//取反仿函数
*/
void test4() {
	std::negate<int> n;
	std::cout << n(10) << std::endl;

	std::plus<int> p;
	std::cout << p(10, 10) << std::endl;
}


/*
* 关系仿函数
* template<class T> bool equal_to<T>                    //等于
* template<class T> bool not_equal_to<T>				//不等于
* template<class T> bool greater<T>                     //大于
* template<class T> bool greater_equal<T>				//大于等于
* template<class T> bool less<T>                        //小于
* template<class T> bool less_equal<T>					//小于等于
*/
void test5() {
	std::equal_to<int> e;
	std::cout << e(10, 10) << std::endl;
	
	std::greater<int> g;
	std::cout << g(10, 20) << std::endl;
}

/*
* 逻辑仿函数 
* template<class T> bool logical_and<T>					//逻辑与
* template<class T> bool logical_or<T>					//逻辑或
* template<class T> bool logical_not<T>					//逻辑非
*/

int main(int argc, char* argv[]) {

	test1();

	test2();
	
	MyPrint myPrint;
	test3(myPrint, "clear");

	test4();

	test5();

	system("pause");
	return 0;
}