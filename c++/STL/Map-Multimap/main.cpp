#include <iostream>
#include <map>
#include <string>

/*
* map中所有元素都是pair
* pair中第一个元素为key（键值），起到索引作用，第二个元素为value（实值）
* 所有元素都会根据元素的键值自动排序
* map/multimap属于关联式容器，底层结构是用二叉树实现。
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
	* 构造函数
	* map<T1, T2> mp;						//map默认构造函数:
	* map(const map &mp);					//拷贝构造函数
	*/
	std::map<int, std::string>* mp1 = new std::map<int, std::string>();
	std::map<int, std::string, MyCompare>* mp2 = new std::map<int, std::string, MyCompare>();

	/*
	* 赋值
	* map& operator=(const map &mp);		//重载等号操作符
	*/



	/*
	* map大小和交换
	* size();          //返回容器中元素的数目
	* empty();        //判断容器是否为空
	* swap(st);      //交换两个集合容器
	*/



	/*
	* map插入和删除
	* insert(elem);           //在容器中插入元素。
	* clear();                    //清除所有元素
	* erase(pos);              //删除pos迭代器所指的元素，返回下一个元素的迭代器。
	* erase(beg, end);    //删除区间[beg,end)的所有元素 ，返回下一个元素的迭代器。
	* erase(key);            //删除容器中值为key的元素。
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
	* map查找和统计
	* find(key);                  //查找key是否存在,若存在，返回该键的元素的迭代器；若不存在，返回set.end();
	* count(key);                //统计key的元素个数
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
	* map容器排序
	* map容器默认排序规则为 按照key值进行 从小到大排序，掌握如何改变排序规则
	* 利用仿函数，可以改变排序规则
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