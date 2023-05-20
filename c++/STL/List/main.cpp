#include <iostream>
#include <list>

/*
* ����list����һ������洢��Ԫ�Ϸ������Ĵ洢�ṹ������Ԫ�ص��߼�˳����ͨ�������е�ָ������ʵ�ֵ�
* @autor lhz
* @time 20230520
*/

void printfList(std::list<int>* list1);

int main(int argc, char* argv[]) {

	/*
	* ���캯��
	* list<T> lst;									//list���ò���ģ����ʵ��,�����Ĭ�Ϲ�����ʽ��
	* list(beg,end);								//���캯����[beg, end)�����е�Ԫ�ؿ���������
	* list(n,elem);									//���캯����n��elem����������
	* list(const list &lst);						//�������캯����
	*/
	std::list<int>* list1 = new std::list<int>();


	/*
	* ��ֵ�ͽ���
	* assign(beg, end);								//��[beg, end)�����е����ݿ�����ֵ������
	* assign(n, elem);								//��n��elem������ֵ������
	* list& operator=(const list &lst);				//���صȺŲ�����
	* swap(lst);									//��lst�뱾���Ԫ�ػ�����
	*/



	/*
	* ��С����
	* size();										//����������Ԫ�صĸ��� 
	* empty();										//�ж������Ƿ�Ϊ�� 
	* resize(num);									//����ָ�������ĳ���Ϊnum���������䳤������Ĭ��ֵ�����λ�á�
													//���������̣���ĩβ�����������ȵ�Ԫ�ر�ɾ���� 
	* resize(num, elem);							//����ָ�������ĳ���Ϊnum���������䳤������elemֵ�����λ�á� 
													//���������̣���ĩβ�����������ȵ�Ԫ�ر�ɾ��
	*/
	std::cout << "size:" << list1->size() << std::endl;


	/*
	* ��list�����������ݵĲ����ɾ��
	* push_back(elem);								//������β������һ��Ԫ��
	* pop_back();									//ɾ�����������һ��Ԫ��
	* push_front(elem);								//��������ͷ����һ��Ԫ��
	* pop_front();									//��������ͷ�Ƴ���һ��Ԫ��
	* insert(pos,elem);								//��posλ�ò�elemԪ�صĿ��������������ݵ�λ�á�
	* insert(pos,n,elem);							//��posλ�ò���n��elem���ݣ��޷���ֵ��
	* insert(pos,beg,end);							//��posλ�ò���[beg,end)��������ݣ��޷���ֵ��
	* clear();										//�Ƴ���������������
	* erase(beg,end);								//ɾ��[beg,end)��������ݣ�������һ�����ݵ�λ�á�
	* erase(pos);									//ɾ��posλ�õ����ݣ�������һ�����ݵ�λ�á�
	* remove(elem);									//ɾ��������������elemֵƥ���Ԫ�ء�
	*/
	for (int i = 0; i < 10; i++)
	{
		list1->push_back(i);
	}
	for (int i = 9; i >= 0; i--)
	{
		list1->push_front(i);
	}
	printfList(list1);
	std::cout << "size:" << list1->size() << std::endl;

	std::list<int>* list2 = new std::list<int>(*list1);

	/*
	* ��list���������ݽ��д�ȡ
	* front();										//���ص�һ��Ԫ�ء�
	* back();										//�������һ��Ԫ�ء�
	*/


	/*
	* �������е�Ԫ�ط�ת���Լ��������е����ݽ�������
	* reverse();									//��ת����
	* sort();										//��������
	*/
	list1->sort();
	printfList(list1);

	list1->reverse();
	printfList(list1);

	list1->swap(*list2);
	printfList(list1);
	printfList(list2);

	while (!list1->empty())
	{
		std::cout << list1->back() << std::endl;
		list1->pop_back();
	}
	printfList(list1);


	list2->erase(list2->begin(), list2->end());
	printfList(list2);

	delete list1;
	delete list2;
	return 0;
}

void printfList(std::list<int>* list1) {
	for (std::list<int>::const_iterator it = list1->begin(); it != list1->end(); it++) {
		std::cout << *it << std::endl;
	}
}