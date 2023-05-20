#include <iostream>
#include <vector>

/*
* vector���ݽṹ������ǳ����ƣ�Ҳ��Ϊ��������
* ��֮ͬ�����������Ǿ�̬�ռ䣬��vector���Զ�̬��չ
* @autor lhz
* @time 20230517
*/

void printVector(std::vector<int>* v);

int main(int argc, char* argv[]) {

	/*
	* ���캯��
	* vector<T> v;               				//����ģ��ʵ����ʵ�֣�Ĭ�Ϲ��캯��
	* vector(v.begin(), v.end());				//��v[begin(), end())�����е�Ԫ�ؿ���������
	* vector(n, elem);                          //���캯����n��elem����������
	* vector(const vector &vec);				//�������캯����
	*/
	std::vector<int>* v1 = new std::vector<int>();
	std::vector<int>* v2 = new std::vector<int>(10, 9);

	/*
	* ��vector�������и�ֵ
	* vector& operator=(const vector &vec);		//���صȺŲ����� 
	* assign(beg, end);							//��[beg, end)�����е����ݿ�����ֵ������ 
	* assign(n, elem);							//��n��elem������ֵ������ 
	*/



	/*
	* ��vector�����������ʹ�С����
	* empty();									//�ж������Ƿ�Ϊ�� 
	* capacity();								//���������� 
	* size();									//����������Ԫ�صĸ��� 
	* resize(int num);							//����ָ�������ĳ���Ϊnum���������䳤������Ĭ��ֵ�����λ�á�
												//���������̣���ĩβ�����������ȵ�Ԫ�ر�ɾ���� 
	* resize(int num, elem);					//����ָ�������ĳ���Ϊnum���������䳤������elemֵ�����λ�á�
												//���������̣���ĩβ�����������ȵ�Ԫ�ر�ɾ�� 
	*/
	if (v1->empty()) {
		std::cout << "v1 is empty" << std::endl;
	}

	int cap = v1->capacity();
	std::cout << "capacity" << cap << std::endl;

	int size = v1->size();
	std::cout << "size" << size << std::endl;


	/**
	* ��vector�������в��롢ɾ������
	* push_back(ele);												//β������Ԫ��ele
	* pop_back();													//ɾ�����һ��Ԫ��
	* insert(const_iterator pos, ele);								//������ָ��λ��pos����Ԫ��ele
	* insert(const_iterator pos, int count,ele);					//������ָ��λ��pos����count��Ԫ��ele
	* erase(const_iterator pos);									//ɾ��������ָ���Ԫ��
	* erase(const_iterator start, const_iterator end);				//ɾ����������start��end֮���Ԫ��
	* clear();                                                      //ɾ������������Ԫ��
	*/
	for (int i = 0; i < 10 ; i++)
	{
		v1->push_back(i);
	}

	printVector(v1);

	v1->pop_back();

	printVector(v1);

	std::vector<int>::iterator start = v1->begin();
	std::vector<int>::iterator end = v1->end();

	v2->assign(start, end);

	v1->insert(start, 0);
	v1->insert(v1->end(), 2, 0);
	printVector(v1);
	printVector(v2);

	/*
	* ��vector�е����ݵĴ�ȡ����
	* at(int idx);					//��������idx��ָ������
	* operator[];					//��������idx��ָ������
	* front();						//���������е�һ������Ԫ��
	* back();						//�������������һ������Ԫ��
	*/

	std::cout << v1->front() << std::endl;
	std::cout << v1->back() << std::endl;

	/*
	* ʵ������������Ԫ�ؽ��л���
	* swap(vec);					// ��vec�뱾���Ԫ�ػ���
	*/
	v1->swap(*v2);
	printVector(v1);
	printVector(v2);

	/*
	* ����vector�ڶ�̬��չ����ʱ����չ����
	* reserve(int len);				//����Ԥ��len��Ԫ�س��ȣ�Ԥ��λ�ò���ʼ����Ԫ�ز��ɷ��ʡ�
	*/
	v1->reserve(100);
	std::cout << "size:" << v1->size() << "---" << "capacity:" << v1->capacity() << std::endl;


	v1->clear();
	printVector(v1);
	v2->erase(v2->begin(), v2->end());
	printVector(v2);

	system("pause");
	delete v1;
	delete v2;
	return 0;
}

void printVector(std::vector<int>* v) {
	for (int i = 0; i < v->size(); i++)
	{
		std::cout << v->at(i);
	}
	std::cout << std::endl;
}