#include <iostream>
#include <queue>


/*
* Queue是一种先进先出(First In First Out,FIFO)的数据结构，它有两个出口
* @autor lhz
* @time 20230520
*/
int main(int argc, char* argv[]) {

	/*
	* 构造函数
	* queue<T> que;                                 //queue采用模板类实现，queue对象的默认构造形式
	* queue(const queue &que);						//拷贝构造函数
	*/
	std::queue<int>* q1 = new std::queue<int>();

	/*
	* 赋值操作
	* queue& operator=(const queue &que);           //重载等号操作符
	*/

	/*
	* 数据存取
	* push(elem);                             //往队尾添加元素
	* pop();                                      //从队头移除第一个元素
	* back();                                    //返回最后一个元素
	* front();                                  //返回第一个元素
	*/
	for (int i = 0; i < 10; i++)
	{
		q1->push(i);
	}

	/*
	* 大小操作
	* empty();            //判断堆栈是否为空
	* size();              //返回栈的大小
	*/
	std::cout << q1->size() << std::endl;
	while (!q1->empty())
	{
		std::cout << q1->front() << std::endl;
		q1->pop();
	}

	return 0;
}