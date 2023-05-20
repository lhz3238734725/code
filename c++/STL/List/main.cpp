#include <iostream>
#include <list>

/*
* 链表（list）是一种物理存储单元上非连续的存储结构，数据元素的逻辑顺序是通过链表中的指针链接实现的
* @autor lhz
* @time 20230520
*/

void printfList(std::list<int>* list1);

int main(int argc, char* argv[]) {

	/*
	* 构造函数
	* list<T> lst;									//list采用采用模板类实现,对象的默认构造形式：
	* list(beg,end);								//构造函数将[beg, end)区间中的元素拷贝给本身。
	* list(n,elem);									//构造函数将n个elem拷贝给本身。
	* list(const list &lst);						//拷贝构造函数。
	*/
	std::list<int>* list1 = new std::list<int>();


	/*
	* 赋值和交换
	* assign(beg, end);								//将[beg, end)区间中的数据拷贝赋值给本身。
	* assign(n, elem);								//将n个elem拷贝赋值给本身。
	* list& operator=(const list &lst);				//重载等号操作符
	* swap(lst);									//将lst与本身的元素互换。
	*/



	/*
	* 大小操作
	* size();										//返回容器中元素的个数 
	* empty();										//判断容器是否为空 
	* resize(num);									//重新指定容器的长度为num，若容器变长，则以默认值填充新位置。
													//如果容器变短，则末尾超出容器长度的元素被删除。 
	* resize(num, elem);							//重新指定容器的长度为num，若容器变长，则以elem值填充新位置。 
													//如果容器变短，则末尾超出容器长度的元素被删除
	*/
	std::cout << "size:" << list1->size() << std::endl;


	/*
	* 对list容器进行数据的插入和删除
	* push_back(elem);								//在容器尾部加入一个元素
	* pop_back();									//删除容器中最后一个元素
	* push_front(elem);								//在容器开头插入一个元素
	* pop_front();									//从容器开头移除第一个元素
	* insert(pos,elem);								//在pos位置插elem元素的拷贝，返回新数据的位置。
	* insert(pos,n,elem);							//在pos位置插入n个elem数据，无返回值。
	* insert(pos,beg,end);							//在pos位置插入[beg,end)区间的数据，无返回值。
	* clear();										//移除容器的所有数据
	* erase(beg,end);								//删除[beg,end)区间的数据，返回下一个数据的位置。
	* erase(pos);									//删除pos位置的数据，返回下一个数据的位置。
	* remove(elem);									//删除容器中所有与elem值匹配的元素。
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
	* 对list容器中数据进行存取
	* front();										//返回第一个元素。
	* back();										//返回最后一个元素。
	*/


	/*
	* 将容器中的元素反转，以及将容器中的数据进行排序
	* reverse();									//反转链表
	* sort();										//链表排序
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