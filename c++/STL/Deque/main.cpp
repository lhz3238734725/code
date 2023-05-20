#include <iostream>
#include <deque>
#include <algorithm>

void printfDeque(std::deque<std::string>* d);

/*
* ˫�����飬���Զ�ͷ�˽��в���ɾ������
* @autor lhz
* @time 20230520
*/
int main(int argc, char* argv[]) {

	/*
	* ���캯��
	* deque<T> deqT;						//Ĭ�Ϲ�����ʽ
	* deque(beg, end);						//���캯����[beg, end)�����е�Ԫ�ؿ���������
	* deque(n, elem);						//���캯����n��elem����������
	* deque(const deque &deq);				//�������캯��
	*/
	std::deque<std::string>* d1 = new std::deque<std::string>();
	std::deque<std::string>* d2 = new std::deque<std::string>(10, "heiheihei");

	/*
	* ��deque�������и�ֵ
	* deque& operator=(const deque &deq);							//���صȺŲ����� 
	* assign(beg, end);												//��[beg, end)�����е����ݿ�����ֵ������ 
	* assign(n, elem);												//��n��elem������ֵ������ 
	*/



	/*
	* ��deque�����Ĵ�С���в���
	* deque.empty();							//�ж������Ƿ�Ϊ�� 
	* deque.size();								//����������Ԫ�صĸ��� 
	* deque.resize(num);						//����ָ�������ĳ���Ϊnum,�������䳤������Ĭ��ֵ�����λ�á�
												//���������̣���ĩβ�����������ȵ�Ԫ�ر�ɾ���� 
	* deque.resize(num, elem);					//����ָ�������ĳ���Ϊnum,�������䳤������elemֵ�����λ�á�
                                                //���������̣���ĩβ�����������ȵ�Ԫ�ر�ɾ����
	*/
	if (d1->empty())
	{
		std::cout << "d1 is empty" << std::endl;
	}
	std::cout << d1->size() << std::endl;

	/*
	* ��deque�����в����ɾ������
	* ���˲��������
	* push_back(elem);						//������β�����һ������
	* push_front(elem);						//������ͷ������һ������
	* pop_back();							//ɾ���������һ������
	* pop_front();							//ɾ��������һ������
	*
	* ָ��λ�ò�����
	* insert(pos,elem);						//��posλ�ò���һ��elemԪ�صĿ��������������ݵ�λ�á� 
	* insert(pos,n,elem);					//��posλ�ò���n��elem���ݣ��޷���ֵ�� 
	* insert(pos,beg,end);					//��posλ�ò���[beg,end)��������ݣ��޷���ֵ�� 
	* clear();								//����������������� 
	* erase(beg,end);						//ɾ��[beg,end)��������ݣ�������һ�����ݵ�λ�á� 
	* erase(pos);							//ɾ��posλ�õ����ݣ�������һ�����ݵ�λ�á�
	*/
	std::string s1 = "hello world";
	d1->push_back(s1);

	std::string s2 = "i am fine";
	d1->push_front(s2);

	std::string s3 = "hahaha";
	d1->push_back(s3);

	*d2 = *d1;
	printfDeque(d2);
	
	std::deque<std::string>::const_iterator iterator = d2->begin();
	d2->insert(iterator, 3, "lll");
	printfDeque(d2);
	d2->clear();
	printfDeque(d2);
	

	/*
	* ��deque �е����ݵĴ�ȡ����
	* at(int idx);							//��������idx��ָ������
	* operator[];							//��������idx��ָ������
	* front();								//���������е�һ������Ԫ��
	* back();								//�������������һ������Ԫ��
	*/
	std::cout << "font:" << d1->front() << std::endl;
	std::cout << "back:" << d1->back() << std::endl;
	printfDeque(d1);

	/*
	* �����㷨ʵ�ֶ�deque������������
	* sort(iterator beg, iterator end)		//��beg��end������Ԫ�ؽ�������
	*/
	std::sort(d1->begin(), d1->end());
	printfDeque(d1);

	return 0;
}


void printfDeque(std::deque<std::string>* d) {
	for (int i = 0; i < d->size(); i++)
	{
		std::cout << i << ":" << (*d)[i] << std::endl;
	}
}