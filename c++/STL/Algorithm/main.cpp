#include <iostream>
#include <algorithm>
#include <vector>
#include <functional>
#include <numeric>

using namespace std;

/*
* STL- 常用算法
* 算法主要是由头文件<algorithm> <functional> <numeric>组成。 
* <algorithm>是所有STL头文件中最大的一个，范围涉及到比较、 交换、查找、遍历操作、复制、修改等等 
* <numeric>体积很小，只包括几个在序列上面进行简单数学运算的模板函数 
* <functional>定义了一些模板类,用以声明函数对象。
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
	* 实现遍历容器
	* for_each(iterator beg, iterator end, _func);
	* 遍历算法 遍历容器元素
	* beg 开始迭代器
	* end 结束迭代器
	* _func 函数或者函数对象
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
	* 搬运容器到另一个容器中
	* transform(iterator beg1, iterator end1, iterator beg2, _func);
	* beg1 源容器开始迭代器
	* end1 源容器结束迭代器
	* beg2 目标容器开始迭代器
	* _func 函数或者函数对象
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
	* 查找指定元素，找到返回指定元素的迭代器，找不到返回结束迭代器end()
	* find(iterator beg, iterator end, value);
	* 按值查找元素，找到返回指定位置迭代器，找不到返回结束迭代器位置
	* beg 开始迭代器
	* end 结束迭代器
	* value 查找的元素
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
	* 按条件查找元素
	* find_if(iterator beg, iterator end, _Pred);
	* 按值查找元素，找到返回指定位置迭代器，找不到返回结束迭代器位置
	* beg 开始迭代器
	* end 结束迭代器
	* _Pred 函数或者谓词（返回bool类型的仿函数）
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
	* 查找相邻重复元素
	* adjacent_find(iterator beg, iterator end);
	* 查找相邻重复元素,返回相邻元素的第一个位置的迭代器
	* beg 开始迭代器
	* end 结束迭代器
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
	* 查找指定元素是否存在
	* bool binary_search(iterator beg, iterator end, value);
	* 查找指定的元素，查到 返回true  否则false
	* 注意: 在无序序列中不可用
	* beg 开始迭代器
	* end 结束迭代器
	* value 查找的元素
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
	* 统计元素个数
	* count(iterator beg, iterator end, value);
	* 统计元素出现次数
	* beg 开始迭代器
	* end 结束迭代器
	* value 统计的元素
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
	* 按条件统计元素个数
	* count_if(iterator beg, iterator end, _Pred);
	* 按条件统计元素出现次数
	* beg 开始迭代器
	* end 结束迭代器
	* _Pred 谓词
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
*  对容器内元素进行排序
*  sort(iterator beg, iterator end, _Pred);
*  按值查找元素，找到返回指定位置迭代器，找不到返回结束迭代器位置
*  beg    开始迭代器
*  end    结束迭代器
* _Pred  谓词 
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
* 洗牌   指定范围内的元素随机调整次序
* random_shuffle(iterator beg, iterator end);
* 指定范围内的元素随机调整次序
* beg 开始迭代器
* end 结束迭代器
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
* 两个容器元素合并，并存储到另一容器中
* merge(iterator beg1, iterator end1, iterator beg2, iterator end2, iterator dest);
* 容器元素合并，并存储到另一容器中
* 注意: 两个容器必须是有序的
* beg1   容器1开始迭代器
* end1   容器1结束迭代器
* beg2   容器2开始迭代器
* end2   容器2结束迭代器
* dest    目标容器开始迭代器
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
* 将容器内元素进行反转
* reverse(iterator beg, iterator end);
* 反转指定范围的元素
* beg 开始迭代器
* end 结束迭代器
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
* 容器内指定范围的元素拷贝到另一容器中
* copy(iterator beg, iterator end, iterator dest);
* 按值查找元素，找到返回指定位置迭代器，找不到返回结束迭代器位置
* beg  开始迭代器
* end  结束迭代器
* dest 目标起始迭代器 
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
* 将容器内指定范围的旧元素修改为新元素
* replace(iterator beg, iterator end, oldvalue, newvalue);
* 将区间内旧元素 替换成 新元素
* beg 开始迭代器
* end 结束迭代器
* oldvalue 旧元素
* newvalue 新元素 
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
* 将区间内满足条件的元素，替换成指定元素
* replace_if(iterator beg, iterator end, _pred, newvalue);
* 按条件替换元素，满足条件的替换成指定元素
* beg 开始迭代器
* end 结束迭代器
* _pred 谓词
* newvalue 替换的新元素 
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
* 互换两个容器的元素
* swap(container c1, container c2);
* 互换两个容器的元素
* c1容器1
* c2容器2
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
* 计算区间内 容器元素累计总和
* accumulate(iterator beg, iterator end, value);
* 计算容器元素累计总和
* beg 开始迭代器
* end 结束迭代器
* value 起始值 
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
* 向容器中填充指定的元素
* fill(iterator beg, iterator end, value);
* 向容器中填充元素
* beg 开始迭代器
* end 结束迭代器
* value 填充的值 
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
* 求两个容器的交集
* set_intersection(iterator beg1, iterator end1, iterator beg2, iterator end2, iterator dest);
* 求两个集合的交集
* 注意:两个集合必须是有序序列
* beg1 容器1开始迭代器
* end1 容器1结束迭代器
* beg2 容器2开始迭代器
* end2 容器2结束迭代器
* dest 目标容器开始迭代器 
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
* 求两个集合的并集
* set_union(iterator beg1, iterator end1, iterator beg2, iterator end2, iterator dest);
* 求两个集合的并集
* 注意:两个集合必须是有序序列
* beg1 容器1开始迭代器
* end1 容器1结束迭代器
* beg2 容器2开始迭代器
* end2 容器2结束迭代器
* dest 目标容器开始迭代器set_union(iterator beg1, iterator end1, iterator beg2, iterator end2, iterator dest);
* 求两个集合的并集
* 注意:两个集合必须是有序序列
* beg1 容器1开始迭代器
* end1 容器1结束迭代器
* beg2 容器2开始迭代器
* end2 容器2结束迭代器
* dest 目标容器开始迭代器
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
* 求两个集合的差集
* set_difference(iterator beg1, iterator end1, iterator beg2, iterator end2, iterator dest);
* 求两个集合的差集
* 注意:两个集合必须是有序序列
* beg1 容器1开始迭代器
* end1 容器1结束迭代器
* beg2 容器2开始迭代器
* end2 容器2结束迭代器
* dest 目标容器开始迭代器
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
	* 常用遍历算法
	* for_each		//遍历容器
	* transform		//搬运容器到另一个容器中
	*/

	test1();
	test2();

	/*
	* 常用的查找算法
	* find						//查找元素
	* find_if					//按条件查找元素
	* adjacent_find				//查找相邻重复元素
	* binary_search				//二分查找法
	* count						//统计元素个数
	* count_if					//按条件统计元素个数
	*/
	test3();
	test4();
	test5();
	test6();
	test7();
	test8();

	/*
	* 常用的排序算法
	* sort						//对容器内元素进行排序
	* random_shuffle			//洗牌   指定范围内的元素随机调整次序
	* merge						// 容器元素合并，并存储到另一容器中
	* reverse					// 反转指定范围的元素
	*/
	test9();
	test10();
	test11();
	test12();

	/*
	* 常用的拷贝和替换算法
	* copy							// 容器内指定范围的元素拷贝到另一容器中
	* replace						// 将容器内指定范围的旧元素修改为新元素
	* replace_if					// 容器内指定范围满足条件的元素替换为新元素
	* swap							// 互换两个容器的元素
	*/
	test13();
	test14();
	test15();
	test16();

	/*
	* 常用的算术生成算法
	* accumulate      // 计算容器元素累计总和 
	* fill                 // 向容器中添加元素
	*/
	test17();
	test18();

	/*
	* 常用的集合算法
	* set_intersection          // 求两个容器的交集 
	* set_union                       // 求两个容器的并集 
	* set_difference              // 求两个容器的差集
	*/
	test19();
	test20();
	test21();

	return 0;
}