#include <iostream>
#include <deque>
#include <algorithm>

void printfDeque(std::deque<std::string>* d);

/*
* 双端数组，可以对头端进行插入删除操作
* @autor lhz
* @time 20230520
*/
int main(int argc, char* argv[]) {

	/*
	* 构造函数
	* deque<T> deqT;						//默认构造形式
	* deque(beg, end);						//构造函数将[beg, end)区间中的元素拷贝给本身。
	* deque(n, elem);						//构造函数将n个elem拷贝给本身。
	* deque(const deque &deq);				//拷贝构造函数
	*/
	std::deque<std::string>* d1 = new std::deque<std::string>();
	std::deque<std::string>* d2 = new std::deque<std::string>(10, "heiheihei");

	/*
	* 给deque容器进行赋值
	* deque& operator=(const deque &deq);							//重载等号操作符 
	* assign(beg, end);												//将[beg, end)区间中的数据拷贝赋值给本身。 
	* assign(n, elem);												//将n个elem拷贝赋值给本身。 
	*/



	/*
	* 对deque容器的大小进行操作
	* deque.empty();							//判断容器是否为空 
	* deque.size();								//返回容器中元素的个数 
	* deque.resize(num);						//重新指定容器的长度为num,若容器变长，则以默认值填充新位置。
												//如果容器变短，则末尾超出容器长度的元素被删除。 
	* deque.resize(num, elem);					//重新指定容器的长度为num,若容器变长，则以elem值填充新位置。
                                                //如果容器变短，则末尾超出容器长度的元素被删除。
	*/
	if (d1->empty())
	{
		std::cout << "d1 is empty" << std::endl;
	}
	std::cout << d1->size() << std::endl;

	/*
	* 向deque容器中插入和删除数据
	* 两端插入操作：
	* push_back(elem);						//在容器尾部添加一个数据
	* push_front(elem);						//在容器头部插入一个数据
	* pop_back();							//删除容器最后一个数据
	* pop_front();							//删除容器第一个数据
	*
	* 指定位置操作：
	* insert(pos,elem);						//在pos位置插入一个elem元素的拷贝，返回新数据的位置。 
	* insert(pos,n,elem);					//在pos位置插入n个elem数据，无返回值。 
	* insert(pos,beg,end);					//在pos位置插入[beg,end)区间的数据，无返回值。 
	* clear();								//清空容器的所有数据 
	* erase(beg,end);						//删除[beg,end)区间的数据，返回下一个数据的位置。 
	* erase(pos);							//删除pos位置的数据，返回下一个数据的位置。
	*/
	std::string s1 = "hello world";
	d1->push_back(s1);

	std::string s2 = "i am fine";
	d1->push_front(s2);

	std::string s3 = "hahaha";
	d1->push_back(s3);

	*d2 = *d1;
	printfDeque(d2);
	
	std::deque<std::string>::const_iterator iterator = d2->begin();
	d2->insert(iterator, 3, "lll");
	printfDeque(d2);
	d2->clear();
	printfDeque(d2);
	

	/*
	* 对deque 中的数据的存取操作
	* at(int idx);							//返回索引idx所指的数据
	* operator[];							//返回索引idx所指的数据
	* front();								//返回容器中第一个数据元素
	* back();								//返回容器中最后一个数据元素
	*/
	std::cout << "font:" << d1->front() << std::endl;
	std::cout << "back:" << d1->back() << std::endl;
	printfDeque(d1);

	/*
	* 利用算法实现对deque容器进行排序
	* sort(iterator beg, iterator end)		//对beg和end区间内元素进行排序
	*/
	std::sort(d1->begin(), d1->end());
	printfDeque(d1);

	return 0;
}


void printfDeque(std::deque<std::string>* d) {
	for (int i = 0; i < d->size(); i++)
	{
		std::cout << i << ":" << (*d)[i] << std::endl;
	}
}