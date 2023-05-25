#include <iostream>
#include <algorithm>
#include <vector>
#include <functional>
#include <numeric>

using namespace std;

/*
* STL- �����㷨
* �㷨��Ҫ����ͷ�ļ�<algorithm> <functional> <numeric>��ɡ� 
* <algorithm>������STLͷ�ļ�������һ������Χ�漰���Ƚϡ� ���������ҡ��������������ơ��޸ĵȵ� 
* <numeric>�����С��ֻ��������������������м���ѧ�����ģ�庯�� 
* <functional>������һЩģ����,����������������
* 
* @autor lhz
* @time 20200524
*/
void test1_1(int val) {
	cout << val << endl;
}
class test1_2 {
public:
	void operator()(int val) {
		cout << val << endl;
	}
};

/*
	* ʵ�ֱ�������
	* for_each(iterator beg, iterator end, _func);
	* �����㷨 ��������Ԫ��
	* beg ��ʼ������
	* end ����������
	* _func �������ߺ�������
	*/
void test1() {
	cout << "test1" << endl;
	vector<int> v;
	for (int i = 0; i < 10; i++)
	{
		v.push_back(i);
	}

	for_each(v.begin(), v.end(), test1_1);

	for_each(v.begin(), v.end(), test1_2());
}

int test2_1(int val) {
	return val + 1;
}

/*
	* ������������һ��������
	* transform(iterator beg1, iterator end1, iterator beg2, _func);
	* beg1 Դ������ʼ������
	* end1 Դ��������������
	* beg2 Ŀ��������ʼ������
	* _func �������ߺ�������
	*/
void test2() {
	cout << "test2" << endl;
	vector<int> v1;
	for (int i = 0; i < 10; i++)
	{
		v1.push_back(i);
	}
	vector<int> v2;
	v2.resize(v1.size());
	transform(v1.begin(), v1.end(), v2.begin(), test2_1);

	for (int i = 0; i < v2.size(); i++)
	{
		cout << v2[i] << endl;
	}
}

/*
	* ����ָ��Ԫ�أ��ҵ�����ָ��Ԫ�صĵ��������Ҳ������ؽ���������end()
	* find(iterator beg, iterator end, value);
	* ��ֵ����Ԫ�أ��ҵ�����ָ��λ�õ��������Ҳ������ؽ���������λ��
	* beg ��ʼ������
	* end ����������
	* value ���ҵ�Ԫ��
	*/
void test3() {
	cout << "test3" << endl;
	vector<int> v;
	v.push_back(1);
	v.push_back(2);
	v.push_back(3);

	vector<int>::const_iterator it = find(v.begin(), v.end(), 1);
	cout << *it << endl;
}

/*
	* ����������Ԫ��
	* find_if(iterator beg, iterator end, _Pred);
	* ��ֵ����Ԫ�أ��ҵ�����ָ��λ�õ��������Ҳ������ؽ���������λ��
	* beg ��ʼ������
	* end ����������
	* _Pred ��������ν�ʣ�����bool���͵ķº�����
	*/
class test4_1
{
public:
	bool operator()(int val) {
		return val > 4;
	}

};

void test4() {
	cout << "test4" << endl;
	vector<int> v;
	v.push_back(1);
	v.push_back(2);
	v.push_back(3);

	vector<int>::const_iterator it = find_if(v.begin(), v.end(), test4_1());
	if (it == v.end()) {
		cout << "is not exit" << endl;
	}
}

/*
	* ���������ظ�Ԫ��
	* adjacent_find(iterator beg, iterator end);
	* ���������ظ�Ԫ��,��������Ԫ�صĵ�һ��λ�õĵ�����
	* beg ��ʼ������
	* end ����������
	*/
void test5() {
	cout << "test5" << endl;
	vector<int> v;
	v.push_back(1);
	v.push_back(2);
	v.push_back(3);
	v.push_back(3);
	v.push_back(2);
	v.push_back(1);

	vector<int>::const_iterator it = adjacent_find(v.begin(), v.end());
	if (it == v.end()) {
		cout << "is not exit" << endl;
	}
	else
	{
		cout << *it << endl;
	}
}

/*
	* ����ָ��Ԫ���Ƿ����
	* bool binary_search(iterator beg, iterator end, value);
	* ����ָ����Ԫ�أ��鵽 ����true  ����false
	* ע��: �����������в�����
	* beg ��ʼ������
	* end ����������
	* value ���ҵ�Ԫ��
	*/
void test6() {
	cout << "test6" << endl;
	vector<int> v;
	v.push_back(1);
	v.push_back(2);
	v.push_back(3);
	v.push_back(3);
	v.push_back(2);
	v.push_back(1);

	sort(v.begin(), v.end());

	bool flag = binary_search(v.begin(), v.end(), 1);
	if (flag)
	{
		cout << "is exit" << endl;
	}
	else
	{
		cout << "is not exit" << endl;
	}
}

/*
	* ͳ��Ԫ�ظ���
	* count(iterator beg, iterator end, value);
	* ͳ��Ԫ�س��ִ���
	* beg ��ʼ������
	* end ����������
	* value ͳ�Ƶ�Ԫ��
	*/
void test7() {
	cout << "test7" << endl;
	vector<int> v;
	v.push_back(1);
	v.push_back(2);
	v.push_back(3);
	v.push_back(3);
	v.push_back(2);
	v.push_back(1);

	int cou = count(v.begin(), v.end(), 1);
	cout << cou << endl;
}

/*
	* ������ͳ��Ԫ�ظ���
	* count_if(iterator beg, iterator end, _Pred);
	* ������ͳ��Ԫ�س��ִ���
	* beg ��ʼ������
	* end ����������
	* _Pred ν��
	*/
class test8_1
{
public:
	bool operator()(int val) {
		return val > 4;
	}

};
void test8() {
	cout << "test8" << endl;
	vector<int> v;
	v.push_back(1);
	v.push_back(2);
	v.push_back(3);
	v.push_back(3);
	v.push_back(2);
	v.push_back(1);

	int cou = count_if(v.begin(), v.end(), test8_1());
	cout << cou << endl;
}

/*
*  ��������Ԫ�ؽ�������
*  sort(iterator beg, iterator end, _Pred);
*  ��ֵ����Ԫ�أ��ҵ�����ָ��λ�õ��������Ҳ������ؽ���������λ��
*  beg    ��ʼ������
*  end    ����������
* _Pred  ν�� 
*/
void test9() {
	cout << "test9" << endl;
	vector<int> v;
	v.push_back(1);
	v.push_back(2);
	v.push_back(3);
	v.push_back(3);
	v.push_back(2);
	v.push_back(1);

	sort(v.begin(), v.end());
	for (auto val:v)
	{
		cout << val;
	}
	cout << endl;
	sort(v.begin(), v.end(), greater<int>());
	for (auto val : v)
	{
		cout << val << "-";
	}
	cout << endl;
}

/*
* ϴ��   ָ����Χ�ڵ�Ԫ�������������
* random_shuffle(iterator beg, iterator end);
* ָ����Χ�ڵ�Ԫ�������������
* beg ��ʼ������
* end ����������
*/
void test10() {
	cout << "test10" << endl;
	vector<int> v;
	v.push_back(1);
	v.push_back(2);
	v.push_back(3);
	v.push_back(3);
	v.push_back(2);
	v.push_back(1);

	for (auto val : v)
	{
		cout << val << "-";
	}
	cout << endl;

	random_shuffle(v.begin(), v.end());

	for (auto val : v)
	{
		cout << val << "-";
	}
	cout << endl;
}

/*
* ��������Ԫ�غϲ������洢����һ������
* merge(iterator beg1, iterator end1, iterator beg2, iterator end2, iterator dest);
* ����Ԫ�غϲ������洢����һ������
* ע��: �������������������
* beg1   ����1��ʼ������
* end1   ����1����������
* beg2   ����2��ʼ������
* end2   ����2����������
* dest    Ŀ��������ʼ������
*/
void test11() {
	cout << "test11" << endl;
	vector<int> v1;
	v1.push_back(5);
	v1.push_back(2);
	v1.push_back(3);

	vector<int> v2;
	v2.push_back(10);
	v2.push_back(4);
	v2.push_back(30);

	vector<int> v3;
	v3.resize(v1.size() + v2.size());
	
	sort(v1.begin(), v1.end());
	sort(v2.begin(), v2.end());

	merge(v1.begin(), v1.end(), v2.begin(), v2.end(), v3.begin());

	for (auto val : v3)
	{
		cout << val <<"-";
	}
	cout << endl;
}

/*
* ��������Ԫ�ؽ��з�ת
* reverse(iterator beg, iterator end);
* ��תָ����Χ��Ԫ��
* beg ��ʼ������
* end ����������
*/
void test12() {
	cout << "test12" << endl;
	vector<int> v;
	v.push_back(5);
	v.push_back(2);
	v.push_back(3);

	reverse(v.begin(), v.end());
	for (auto val : v)
	{
		cout << val << "-";
	}
	cout << endl;
}

/*
* ������ָ����Χ��Ԫ�ؿ�������һ������
* copy(iterator beg, iterator end, iterator dest);
* ��ֵ����Ԫ�أ��ҵ�����ָ��λ�õ��������Ҳ������ؽ���������λ��
* beg  ��ʼ������
* end  ����������
* dest Ŀ����ʼ������ 
*/
void test13() {
	cout << "test13" << endl;
	vector<int> v1;
	v1.push_back(5);
	v1.push_back(2);
	v1.push_back(3);

	vector<int> v2;
	v2.resize(v1.size());

	copy(v1.begin(), v1.end(), v2.begin());

	for_each(v2.begin(), v2.end(), [](int val) {
		cout << val << "-";
		});
	cout << endl;
}

/*
* ��������ָ����Χ�ľ�Ԫ���޸�Ϊ��Ԫ��
* replace(iterator beg, iterator end, oldvalue, newvalue);
* �������ھ�Ԫ�� �滻�� ��Ԫ��
* beg ��ʼ������
* end ����������
* oldvalue ��Ԫ��
* newvalue ��Ԫ�� 
*/
void test14() {
	cout << "test14" << endl;
	vector<int> v;
	v.push_back(5);
	v.push_back(2);
	v.push_back(3);
	v.push_back(5);
	v.push_back(2);
	v.push_back(3);

	for_each(v.begin(), v.end(), [](int val) {
		cout << val << "-";
		});
	cout << endl;

	replace(v.begin(), v.end(), 2, 10);

	for_each(v.begin(), v.end(), [](int val) {
		cout << val << "-";
		});
	cout << endl;
}

/*
* ������������������Ԫ�أ��滻��ָ��Ԫ��
* replace_if(iterator beg, iterator end, _pred, newvalue);
* �������滻Ԫ�أ������������滻��ָ��Ԫ��
* beg ��ʼ������
* end ����������
* _pred ν��
* newvalue �滻����Ԫ�� 
*/
class test15_1
{
public:
	bool operator()(int val) {
		return val > 3;
	}

};

void test15() {
	cout << "test15" << endl;
	vector<int> v;
	v.push_back(5);
	v.push_back(2);
	v.push_back(3);
	v.push_back(5);
	v.push_back(2);
	v.push_back(3);

	for_each(v.begin(), v.end(), [](int val) {
		cout << val << "-";
		});
	cout << endl;

	replace_if(v.begin(), v.end(), test15_1(), 100);

	for_each(v.begin(), v.end(), [](int val) {
		cout << val << "-";
		});
	cout << endl;
}

/*
* ��������������Ԫ��
* swap(container c1, container c2);
* ��������������Ԫ��
* c1����1
* c2����2
*/
void test16() {
	cout << "test16" << endl;
	vector<int> v1;
	v1.push_back(5);
	v1.push_back(2);
	v1.push_back(3);

	vector<int> v2;
	v2.push_back(1);
	v2.push_back(2);
	v2.push_back(3);

	for_each(v1.begin(), v1.end(), [](int val) {
		cout << val << "-";
		});
	cout << endl;

	swap(v1, v2);

	for_each(v1.begin(), v1.end(), [](int val) {
		cout << val << "-";
		});
	cout << endl;
}

/*
* ���������� ����Ԫ���ۼ��ܺ�
* accumulate(iterator beg, iterator end, value);
* ��������Ԫ���ۼ��ܺ�
* beg ��ʼ������
* end ����������
* value ��ʼֵ 
*/
void test17() {
	cout << "test17" << endl;
	vector<int> v;
	v.push_back(5);
	v.push_back(2);
	v.push_back(3);

	int total = accumulate(v.begin(), v.end(), 10);
	cout << total << endl;
}

/*
* �����������ָ����Ԫ��
* fill(iterator beg, iterator end, value);
* �����������Ԫ��
* beg ��ʼ������
* end ����������
* value ����ֵ 
*/
void test18() {
	cout << "test18" << endl;
	vector<int> v;
	v.resize(10);

	fill(v.begin(), v.end(), 100);

	for_each(v.begin(), v.end(), [](int val) {
		cout << val << "-";
		});
	cout << endl;
}

/*
* �����������Ľ���
* set_intersection(iterator beg1, iterator end1, iterator beg2, iterator end2, iterator dest);
* ���������ϵĽ���
* ע��:�������ϱ�������������
* beg1 ����1��ʼ������
* end1 ����1����������
* beg2 ����2��ʼ������
* end2 ����2����������
* dest Ŀ��������ʼ������ 
*/
void test19() {
	cout << "test19" << endl;
	vector<int> v1;
	v1.push_back(5);
	v1.push_back(2);
	v1.push_back(3);

	vector<int> v2;
	v2.push_back(1);
	v2.push_back(2);
	v2.push_back(3);

	vector<int> v3;
	v3.resize(min(v1.size(), v2.size()));

	sort(v1.begin(), v1.end());
	sort(v2.begin(), v2.end());

	vector<int>::iterator it = set_intersection(v1.begin(), v1.end(), v2.begin(), v2.end(), v3.begin());
	
	for_each(v3.begin(), it, [](int val) {
		cout << val << "-";
		});
	cout << endl;
}

/*
* ���������ϵĲ���
* set_union(iterator beg1, iterator end1, iterator beg2, iterator end2, iterator dest);
* ���������ϵĲ���
* ע��:�������ϱ�������������
* beg1 ����1��ʼ������
* end1 ����1����������
* beg2 ����2��ʼ������
* end2 ����2����������
* dest Ŀ��������ʼ������set_union(iterator beg1, iterator end1, iterator beg2, iterator end2, iterator dest);
* ���������ϵĲ���
* ע��:�������ϱ�������������
* beg1 ����1��ʼ������
* end1 ����1����������
* beg2 ����2��ʼ������
* end2 ����2����������
* dest Ŀ��������ʼ������
*/
void test20() {
	cout << "test20" << endl;
	vector<int> v1;
	v1.push_back(5);
	v1.push_back(2);
	v1.push_back(3);

	vector<int> v2;
	v2.push_back(1);
	v2.push_back(2);
	v2.push_back(3);

	vector<int> v3;
	v3.resize(v1.size()+v2.size());

	sort(v1.begin(), v1.end());
	sort(v2.begin(), v2.end());

	vector<int>::iterator it = set_union(v1.begin(), v1.end(), v2.begin(), v2.end(), v3.begin());

	for_each(v3.begin(), it, [](int val) {
		cout << val << "-";
		});
	cout << endl;

}

/*
* ���������ϵĲ
* set_difference(iterator beg1, iterator end1, iterator beg2, iterator end2, iterator dest);
* ���������ϵĲ
* ע��:�������ϱ�������������
* beg1 ����1��ʼ������
* end1 ����1����������
* beg2 ����2��ʼ������
* end2 ����2����������
* dest Ŀ��������ʼ������
*/
void test21() {
	cout << "test21" << endl;
	vector<int> v1;
	v1.push_back(5);
	v1.push_back(2);
	v1.push_back(3);

	vector<int> v2;
	v2.push_back(1);
	v2.push_back(2);
	v2.push_back(3);

	vector<int> v3;
	v3.resize(max(v1.size(), v2.size()));

	sort(v1.begin(), v1.end());
	sort(v2.begin(), v2.end());

	vector<int>::iterator it = set_difference(v1.begin(), v1.end(), v2.begin(), v2.end(), v3.begin());

	for_each(v3.begin(), it, [](int val) {
		cout << val << "-";
		});
	cout << endl;

	it = set_difference(v2.begin(), v2.end(), v1.begin(), v1.end(), v3.begin());

	for_each(v3.begin(), it, [](int val) {
		cout << val << "-";
		});
	cout << endl;
}

int main(int argc, char* argv[]) {

	/*
	* ���ñ����㷨
	* for_each		//��������
	* transform		//������������һ��������
	*/

	test1();
	test2();

	/*
	* ���õĲ����㷨
	* find						//����Ԫ��
	* find_if					//����������Ԫ��
	* adjacent_find				//���������ظ�Ԫ��
	* binary_search				//���ֲ��ҷ�
	* count						//ͳ��Ԫ�ظ���
	* count_if					//������ͳ��Ԫ�ظ���
	*/
	test3();
	test4();
	test5();
	test6();
	test7();
	test8();

	/*
	* ���õ������㷨
	* sort						//��������Ԫ�ؽ�������
	* random_shuffle			//ϴ��   ָ����Χ�ڵ�Ԫ�������������
	* merge						// ����Ԫ�غϲ������洢����һ������
	* reverse					// ��תָ����Χ��Ԫ��
	*/
	test9();
	test10();
	test11();
	test12();

	/*
	* ���õĿ������滻�㷨
	* copy							// ������ָ����Χ��Ԫ�ؿ�������һ������
	* replace						// ��������ָ����Χ�ľ�Ԫ���޸�Ϊ��Ԫ��
	* replace_if					// ������ָ����Χ����������Ԫ���滻Ϊ��Ԫ��
	* swap							// ��������������Ԫ��
	*/
	test13();
	test14();
	test15();
	test16();

	/*
	* ���õ����������㷨
	* accumulate      // ��������Ԫ���ۼ��ܺ� 
	* fill                 // �����������Ԫ��
	*/
	test17();
	test18();

	/*
	* ���õļ����㷨
	* set_intersection          // �����������Ľ��� 
	* set_union                       // �����������Ĳ��� 
	* set_difference              // �����������Ĳ
	*/
	test19();
	test20();
	test21();

	return 0;
}