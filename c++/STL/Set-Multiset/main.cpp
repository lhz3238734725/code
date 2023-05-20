#include <iostream>
#include <set>

/*
* 所有元素都会在插入时自动被排序
* set/multiset属于关联式容器，底层结构是用二叉树实现，set不允许容器中有重复的元素，multiset允许容器中有重复的元素
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
	* 构造函数
	* set<T> st;                        //默认构造函数：
	* set(const set &st);				//拷贝构造函数
	*/
	std::set<int>* set1 = new std::set<int>();
	std::multiset<int>* set2 = new std::multiset<int>();


	/*
	* 赋值
	* set& operator=(const set &st);    //重载等号操作符
	*/



	/*
	* set大小和交换
	* size();							//返回容器中元素的数目
	* empty();							//判断容器是否为空
	* swap(st);							//交换两个集合容器
	*/



	/*
	* set插入和删除
	* insert(elem);						//在容器中插入元素。
	* clear();							//清除所有元素
	* erase(pos);						//删除pos迭代器所指的元素，返回下一个元素的迭代器。
	* erase(beg, end);					//删除区间[beg,end)的所有元素 ，返回下一个元素的迭代器。
	* erase(elem);						//删除容器中值为elem的元素。
	*/
	for (int i = 0; i < 10; i++)
	{
		set1->insert(1);
		set2->insert(1);
	}
	printfSet(set1);
	printfSet((std::set<int>*)set2);

	/*
	* set查找和统计
	* find(key);                  //查找key是否存在,若存在，返回该键的元素的迭代器；若不存在，返回set.end();
	* count(key);                //统计key的元素个数
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
	* set和multiset的区别
	* set不可以插入重复数据，而multiset可以
	* set插入数据的同时会返回插入结果，表示插入是否成功
	* multiset不会检测数据，因此可以插入重复数据
	*/


	/*
	* pair对组创建
	* 成对出现的数据，利用对组可以返回两个数据
	* pair<type, type> p ( value1, value2 );
	* pair<type, type> p = make_pair( value1, value2 );
	*/
	std::pair<int, std::string>* p = new std::pair<int, std::string>(1, std::string("name"));
	std::cout << p->first << "--" << p->second << std::endl;

	/*
	* set容器排序
	* set容器默认排序规则为从小到大，掌握如何改变排序规则
	* 利用仿函数，可以改变排序规则
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