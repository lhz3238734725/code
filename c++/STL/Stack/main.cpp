#include <iostream>
#include <stack>

/*
* stack��һ���Ƚ����(First In Last Out,FILO)�����ݽṹ����ֻ��һ������
* @autor lhz
* @time 20200520
*/
int main(int argc, char* argv[]) {

	/*
	* ���캯��
	* stack<T> stk;                                 //stack����ģ����ʵ�֣� stack�����Ĭ�Ϲ�����ʽ
	* stack(const stack &stk);						//�������캯��
	*/
	std::stack<int>* stack1 = new std::stack<int>();


	/*
	* ��ֵ����
	* stack& operator=(const stack &stk);           //���صȺŲ�����
	*/
	
	/*
	* ���ݴ�ȡ
	* push(elem);									//��ջ�����Ԫ��
	* pop();										//��ջ���Ƴ���һ��Ԫ��
	* top();										//����ջ��Ԫ��
	*/
	for (int i = 0; i < 10; i++) {
		stack1->push(i);
	}
	

	/*
	* ��С����
	* empty();            //�ж϶�ջ�Ƿ�Ϊ��
	* size();              //����ջ�Ĵ�С
	*/
	std::cout << stack1->size() << std::endl;

	while (!stack1->empty())
	{
		std::cout << stack1->top() << std::endl;
		stack1->pop();
	}

	return 0;
}