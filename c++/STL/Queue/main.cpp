#include <iostream>
#include <queue>


/*
* Queue��һ���Ƚ��ȳ�(First In First Out,FIFO)�����ݽṹ��������������
* @autor lhz
* @time 20230520
*/
int main(int argc, char* argv[]) {

	/*
	* ���캯��
	* queue<T> que;                                 //queue����ģ����ʵ�֣�queue�����Ĭ�Ϲ�����ʽ
	* queue(const queue &que);						//�������캯��
	*/
	std::queue<int>* q1 = new std::queue<int>();

	/*
	* ��ֵ����
	* queue& operator=(const queue &que);           //���صȺŲ�����
	*/

	/*
	* ���ݴ�ȡ
	* push(elem);                             //����β���Ԫ��
	* pop();                                      //�Ӷ�ͷ�Ƴ���һ��Ԫ��
	* back();                                    //�������һ��Ԫ��
	* front();                                  //���ص�һ��Ԫ��
	*/
	for (int i = 0; i < 10; i++)
	{
		q1->push(i);
	}

	/*
	* ��С����
	* empty();            //�ж϶�ջ�Ƿ�Ϊ��
	* size();              //����ջ�Ĵ�С
	*/
	std::cout << q1->size() << std::endl;
	while (!q1->empty())
	{
		std::cout << q1->front() << std::endl;
		q1->pop();
	}

	return 0;
}