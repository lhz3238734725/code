#include <iostream>
#include <map>
#include <string>

/*
* map������Ԫ�ض���pair
* pair�е�һ��Ԫ��Ϊkey����ֵ�������������ã��ڶ���Ԫ��Ϊvalue��ʵֵ��
* ����Ԫ�ض������Ԫ�صļ�ֵ�Զ�����
* map/multimap���ڹ���ʽ�������ײ�ṹ���ö�����ʵ�֡�
* @autor lhz
* @time 20230520
*/
void printfMap(std::map<int, std::string>* mp);

class MyCompare {
public:
	bool operator()(int v1, int v2) const {
		return v1 > v2;
	}
};
int main(int argc, char* argv[]) {

	/*
	* ���캯��
	* map<T1, T2> mp;						//mapĬ�Ϲ��캯��:
	* map(const map &mp);					//�������캯��
	*/
	std::map<int, std::string>* mp1 = new std::map<int, std::string>();
	std::map<int, std::string, MyCompare>* mp2 = new std::map<int, std::string, MyCompare>();

	/*
	* ��ֵ
	* map& operator=(const map &mp);		//���صȺŲ�����
	*/



	/*
	* map��С�ͽ���
	* size();          //����������Ԫ�ص���Ŀ
	* empty();        //�ж������Ƿ�Ϊ��
	* swap(st);      //����������������
	*/



	/*
	* map�����ɾ��
	* insert(elem);           //�������в���Ԫ�ء�
	* clear();                    //�������Ԫ��
	* erase(pos);              //ɾ��pos��������ָ��Ԫ�أ�������һ��Ԫ�صĵ�������
	* erase(beg, end);    //ɾ������[beg,end)������Ԫ�� ��������һ��Ԫ�صĵ�������
	* erase(key);            //ɾ��������ֵΪkey��Ԫ�ء�
	*/
	mp1->insert(std::pair<int, std::string >(1, std::string("123")));
	mp1->insert(std::pair<int, std::string >(2, std::string("234")));
	mp1->insert(std::pair<int, std::string >(3, std::string("345")));
	printfMap(mp1);


	mp2->insert(std::pair<int, std::string >(1, std::string("123")));
	mp2->insert(std::pair<int, std::string >(2, std::string("234")));
	mp2->insert(std::pair<int, std::string >(3, std::string("345")));
	for (std::map<int, std::string, MyCompare>::iterator it2 = mp2->begin(); it2 != mp2->end(); it2++)
	{
		std::cout << (*it2).first << "--" << (*it2).second << std::endl;
	}


	/*
	* map���Һ�ͳ��
	* find(key);                  //����key�Ƿ����,�����ڣ����ظü���Ԫ�صĵ��������������ڣ�����set.end();
	* count(key);                //ͳ��key��Ԫ�ظ���
	*/
	std::cout << mp1->count(1) << std::endl;

	std::map<int, std::string>::iterator it = mp1->find(1);
	if (it != mp1->end()) {
		std::cout << "is exit" << std::endl;
		std::cout << (*it).first << "--" << (*it).second << std::endl;
	}
	else {
		std::cout << "is not exit" << std::endl;
	}


	/*
	* map��������
	* map����Ĭ���������Ϊ ����keyֵ���� ��С��������������θı��������
	* ���÷º��������Ըı��������
	*/

	delete mp1;
	delete mp2;
	return 0;
}

void printfMap(std::map<int, std::string>* mp) {
	for (std::map<int ,std::string>::iterator it = mp->begin(); it != mp->end(); it++)
	{
		std::cout << (*it).first << "--" << (*it).second << std::endl;
	}
}