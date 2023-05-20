#include <iostream>
#include <set>

/*
* ����Ԫ�ض����ڲ���ʱ�Զ�������
* set/multiset���ڹ���ʽ�������ײ�ṹ���ö�����ʵ�֣�set���������������ظ���Ԫ�أ�multiset�������������ظ���Ԫ��
* @autor lhz
* @time 20230520
*/
void printfSet(std::set<int>* set);

class MyCompare {
public:
	bool operator()(int v1, int v2) const{
		return v1 > v2;
	}
};

int main(int argc, char* argv[]) {

	/*
	* ���캯��
	* set<T> st;                        //Ĭ�Ϲ��캯����
	* set(const set &st);				//�������캯��
	*/
	std::set<int>* set1 = new std::set<int>();
	std::multiset<int>* set2 = new std::multiset<int>();


	/*
	* ��ֵ
	* set& operator=(const set &st);    //���صȺŲ�����
	*/



	/*
	* set��С�ͽ���
	* size();							//����������Ԫ�ص���Ŀ
	* empty();							//�ж������Ƿ�Ϊ��
	* swap(st);							//����������������
	*/



	/*
	* set�����ɾ��
	* insert(elem);						//�������в���Ԫ�ء�
	* clear();							//�������Ԫ��
	* erase(pos);						//ɾ��pos��������ָ��Ԫ�أ�������һ��Ԫ�صĵ�������
	* erase(beg, end);					//ɾ������[beg,end)������Ԫ�� ��������һ��Ԫ�صĵ�������
	* erase(elem);						//ɾ��������ֵΪelem��Ԫ�ء�
	*/
	for (int i = 0; i < 10; i++)
	{
		set1->insert(1);
		set2->insert(1);
	}
	printfSet(set1);
	printfSet((std::set<int>*)set2);

	/*
	* set���Һ�ͳ��
	* find(key);                  //����key�Ƿ����,�����ڣ����ظü���Ԫ�صĵ��������������ڣ�����set.end();
	* count(key);                //ͳ��key��Ԫ�ظ���
	*/
	std::set<int>::iterator it = set1->find(1);
	if (it == set1->end()) {
		std::cout << "is not exit" << std::endl;
	}
	else
	{
		std::cout << "is exit" << std::endl;
		std::cout << set1->count(1) << std::endl;
	}

	it = set2->find(1);
	if (it == set2->end()) {
		std::cout << "is not exit" << std::endl;
	}
	else
	{
		std::cout << "is exit" << std::endl;
		std::cout << set2->count(1) << std::endl;
	}


	/*
	* set��multiset������
	* set�����Բ����ظ����ݣ���multiset����
	* set�������ݵ�ͬʱ�᷵�ز���������ʾ�����Ƿ�ɹ�
	* multiset���������ݣ���˿��Բ����ظ�����
	*/


	/*
	* pair���鴴��
	* �ɶԳ��ֵ����ݣ����ö�����Է�����������
	* pair<type, type> p ( value1, value2 );
	* pair<type, type> p = make_pair( value1, value2 );
	*/
	std::pair<int, std::string>* p = new std::pair<int, std::string>(1, std::string("name"));
	std::cout << p->first << "--" << p->second << std::endl;

	/*
	* set��������
	* set����Ĭ���������Ϊ��С����������θı��������
	* ���÷º��������Ըı��������
	*/

	std::set<int, MyCompare>* set3 = new std::set<int, MyCompare>();
	set3->insert(3);
	set3->insert(2);
	set3->insert(1);
	set3->insert(10);
	set3->insert(8);
	for (std::set<int, MyCompare>::const_iterator it1 = set3->begin(); it1 != set3->end(); it1++) {
		std::cout << *it1;
	}
	std::cout << std::endl;

	delete p;
	delete set1;
	delete set2;
	delete set3;
	return 0;
}

void printfSet(std::set<int>* set) {
	for (std::set<int>::const_iterator it = set->begin(); it != set->end(); it++) {
		std::cout << *it ;
	}
	std::cout << std::endl;
}