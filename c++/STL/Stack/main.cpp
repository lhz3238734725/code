#include <iostream>
#include <stack>

/*
* stack是一种先进后出(First In Last Out,FILO)的数据结构，它只有一个出口
* @autor lhz
* @time 20200520
*/
int main(int argc, char* argv[]) {

	/*
	* 构造函数
	* stack<T> stk;                                 //stack采用模板类实现， stack对象的默认构造形式
	* stack(const stack &stk);						//拷贝构造函数
	*/
	std::stack<int>* stack1 = new std::stack<int>();


	/*
	* 赋值操作
	* stack& operator=(const stack &stk);           //重载等号操作符
	*/
	
	/*
	* 数据存取
	* push(elem);									//向栈顶添加元素
	* pop();										//从栈顶移除第一个元素
	* top();										//返回栈顶元素
	*/
	for (int i = 0; i < 10; i++) {
		stack1->push(i);
	}
	

	/*
	* 大小操作
	* empty();            //判断堆栈是否为空
	* size();              //返回栈的大小
	*/
	std::cout << stack1->size() << std::endl;

	while (!stack1->empty())
	{
		std::cout << stack1->top() << std::endl;
		stack1->pop();
	}

	return 0;
}