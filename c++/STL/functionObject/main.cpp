#include <iostream>
#include <string>
#include <functional>

/*
* ���
* ���غ������ò��������࣬����󳣳�Ϊ��������
* ��������ʹ�����ص�()ʱ����Ϊ���ƺ������ã�Ҳ�зº���
* ���ʣ�
* ��������(�º���)��һ���࣬����һ������
* @autor lhz
* @time 20230524
*/

//1������������ʹ��ʱ����������ͨ������������, �����в����������з���ֵ
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

//2����������������Լ���״̬
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

//3���������������Ϊ��������
void test3(MyPrint& mp, std::string str) {
	mp(str);
}

/*
* ����bool���͵ķº�����Ϊν��
* ���operator()����һ����������ô����һԪν��
* ���operator()����������������ô������Ԫν��
*/


/*
* STL�ڽ���һЩ��������
* �����º��� 
* ��ϵ�º��� 
* �߼��º��� 
* ʹ���ڽ�����������Ҫ����ͷ�ļ� #include<functional>
*/

/*
* �����º��� 
* template<class T> T plus<T>					//�ӷ��º���
* template<class T> T minus<T>					//�����º���
* template<class T> T multiplies<T>				//�˷��º���
* template<class T> T divides<T>				//�����º���
* template<class T> T modulus<T>				//ȡģ�º���
* template<class T> T negate<T>					//ȡ���º���
*/
void test4() {
	std::negate<int> n;
	std::cout << n(10) << std::endl;

	std::plus<int> p;
	std::cout << p(10, 10) << std::endl;
}


/*
* ��ϵ�º���
* template<class T> bool equal_to<T>                    //����
* template<class T> bool not_equal_to<T>				//������
* template<class T> bool greater<T>                     //����
* template<class T> bool greater_equal<T>				//���ڵ���
* template<class T> bool less<T>                        //С��
* template<class T> bool less_equal<T>					//С�ڵ���
*/
void test5() {
	std::equal_to<int> e;
	std::cout << e(10, 10) << std::endl;
	
	std::greater<int> g;
	std::cout << g(10, 20) << std::endl;
}

/*
* �߼��º��� 
* template<class T> bool logical_and<T>					//�߼���
* template<class T> bool logical_or<T>					//�߼���
* template<class T> bool logical_not<T>					//�߼���
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