#include <iostream>
#include <string>

using namespace std;
/**
*stl������string���ʹ��
*string��C++�����ַ�������string��������һ����
*@autor lhz
*@time 20230515
*/
int main(int argc, char* argv[]) {

	/*
	*���캯�� 
	*string();          		      //����һ���յ��ַ��� ����: string str;
	*string(const char* s);	          //ʹ���ַ���s��ʼ��
	*string(const string & str);      //ʹ��һ��string�����ʼ����һ��string����
	*string(int n, char c);           //ʹ��n���ַ�c��ʼ��
	*/
	std::string* s1 = new std::string();
	std::string* s2 = new std::string("test string");
	std::string* s3 = new std::string(*s2);
	std::string* s4 = new std::string(10, 0);

	std::cout << *s1 << std::endl;
	std::cout << *s2 << std::endl;
	std::cout << *s3 << std::endl;
	std::cout << *s4 << std::endl;


	/*
	*��ֵ����
	*string& operator=(const char* s);					//char*�����ַ��� ��ֵ����ǰ���ַ���
	*string& operator=(const string &s);				//���ַ���s������ǰ���ַ���
	*string& operator=(char c);                         //�ַ���ֵ����ǰ���ַ���
	*string& assign(const char *s);						//���ַ���s������ǰ���ַ���
	*string& assign(const char *s, int n);				//���ַ���s��ǰn���ַ�������ǰ���ַ���
	*string& assign(const string &s);					//���ַ���s������ǰ�ַ���
	*string& assign(int n, char c);						//��n���ַ�c������ǰ�ַ���
	*/
	* s1 = "hello world";
	std::cout << *s1 << std::endl;

	*s1 = *s2;
	std::cout << *s1 << std::endl;

	*s1 = 'a';
	std::cout << *s1 << std::endl;

	s1->assign("hello world");
	std::cout << *s1 << std::endl;

	s1->assign("hello world", 1);
	std::cout << *s1 << std::endl;

	s1->assign(*s3);
	std::cout << *s1 << std::endl;

	s1->assign(10, '0');
	std::cout << *s1 << std::endl;

	/*
	*�ַ���ƴ��
	*string& operator+=(const char* str);						//����+=������
	*string& operator+=(const char c);							//����+=������
	*string& operator+=(const string& str);						//����+=������
	*string& append(const char *s);                             //���ַ���s���ӵ���ǰ�ַ�����β
	*string& append(const char *s, int n);						//���ַ���s��ǰn���ַ����ӵ���ǰ�ַ�����β
	*string& append(const string &s);                           //ͬoperator+=(const string& str)
	*string& append(const string &s, int pos, int n);			//�ַ���s�д�pos��ʼ��n���ַ����ӵ��ַ�����β
	*/
	*s1 += "123456";
	std::cout << *s1 << std::endl;

	*s1 += '7';
	std::cout << *s1 << std::endl;

	*s1 += *s2;
	std::cout << *s1 << std::endl;

	s1->append("123456");
	std::cout << *s1 << std::endl;

	s1->append("789", 1);
	std::cout << *s1 << std::endl;

	s1->append(*s2);
	std::cout << *s1 << std::endl;

	s1->append(*s2, 1, 1);
	std::cout << *s1 << std::endl;

	/**
	*�ַ������Һ��滻
	*int find(const string& str, int pos = 0) const;				//����str��һ�γ���λ��,��pos��ʼ����
	*int find(const char* s, int pos = 0) const;                    //����s��һ�γ���λ��,��pos��ʼ����
	*int find(const char* s, int pos, int n) const;					//��posλ�ò���s��ǰn���ַ���һ��λ��
	*int find(const char c, int pos = 0) const;                     //�����ַ�c��һ�γ���λ��
	*int rfind(const string& str, int pos = npos) const;			//����str���һ��λ��,��pos��ʼ����
	*int rfind(const char* s, int pos = npos) const;				//����s���һ�γ���λ��,��pos��ʼ����
	*int rfind(const char* s, int pos, int n) const;				//��pos����s��ǰn���ַ����һ��λ��
	*int rfind(const char c, int pos = 0) const;                    //�����ַ�c���һ�γ���λ��
	*string& replace(int pos, int n, const string& str);			//�滻��pos��ʼn���ַ�Ϊ�ַ���str
	*string& replace(int pos, int n,const char* s);                 //�滻��pos��ʼ��n���ַ�Ϊ�ַ���
	*/
	int index;

	index = s1->find(*s2, 0);
	std::cout << index << std::endl;

	index = s1->find("123", 0);
	std::cout << index << std::endl;

	index = s1->find("123", 0, 1);
	std::cout << index << std::endl;

	index = s1->find('1', 0);
	std::cout << index << std::endl;

	index = s1->rfind(*s2, 0);
	std::cout << index << std::endl;

	index = s1->rfind("123", 0);
	std::cout << index << std::endl;

	index = s1->rfind("123", 0, 1);
	std::cout << index << std::endl;

	index = s1->rfind('1', 0);
	std::cout << index << std::endl;

	s1->replace(0, sizeof(*s2), *s2);
	std::cout << *s1 << std::endl;

	s1->replace(0, sizeof("hello"), "hello");
	std::cout << *s1 << std::endl;

	/**
	*�ַ���֮��ıȽ�
	*int compare(const string &s) const;	//���ַ���s�Ƚ�
	*int compare(const char *s) const;      //���ַ���s�Ƚ�
	*/
	int res;
	res = s1->compare(*s2);
	std::cout << res << std::endl;

	res = s1->compare("123");
	std::cout << res << std::endl;

	/*
	*string�е����ַ���ȡ��ʽ������
	*char& operator[](int n);			//ͨ��[]��ʽȡ�ַ�
	*char& at(int n);                   //ͨ��at������ȡ�ַ�
	*/

	std::cout << (*s1)[1] << std::endl;
	std::cout << s1->at(1) << std::endl;

	/*
	*��string�ַ������в����ɾ���ַ�����
	*string& insert(int pos, const char* s);                //�����ַ���
	*string& insert(int pos, const string& str);			//�����ַ���
	*string& insert(int pos, int n, char c);                //��ָ��λ�ò���n���ַ�c
	*string& erase(int pos, int n = npos);                  //ɾ����Pos��ʼ��n���ַ�
	*/
	s1->insert(0, "lhz");
	std::cout << *s1 << std::endl;

	s1->insert(0, *s2);
	std::cout << *s1 << std::endl;

	s1->insert(0, 1, '1');
	std::cout << *s1 << std::endl;

	s1->erase(0, 1);
	std::cout << *s1 << std::endl;

	/*
	* ���ַ����л�ȡ��Ҫ���Ӵ�
	* string substr(int pos = 0, int n = npos) const;   //������pos��ʼ��n���ַ���ɵ��ַ���
	*/
	*s1 = s1->substr(0, 5);
	std::cout << *s1 << std::endl;

	system("pause");

	delete s1, s2, s3, s4;

	return 0;
}