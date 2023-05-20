#include <iostream>
#include <vector>

/*
* vector数据结构和数组非常相似，也称为单端数组
* 不同之处在于数组是静态空间，而vector可以动态扩展
* @autor lhz
* @time 20230517
*/

void printVector(std::vector<int>* v);

int main(int argc, char* argv[]) {

	/*
	* 构造函数
	* vector<T> v;               				//采用模板实现类实现，默认构造函数
	* vector(v.begin(), v.end());				//将v[begin(), end())区间中的元素拷贝给本身。
	* vector(n, elem);                          //构造函数将n个elem拷贝给本身。
	* vector(const vector &vec);				//拷贝构造函数。
	*/
	std::vector<int>* v1 = new std::vector<int>();
	std::vector<int>* v2 = new std::vector<int>(10, 9);

	/*
	* 给vector容器进行赋值
	* vector& operator=(const vector &vec);		//重载等号操作符 
	* assign(beg, end);							//将[beg, end)区间中的数据拷贝赋值给本身。 
	* assign(n, elem);							//将n个elem拷贝赋值给本身。 
	*/



	/*
	* 对vector容器的容量和大小操作
	* empty();									//判断容器是否为空 
	* capacity();								//容器的容量 
	* size();									//返回容器中元素的个数 
	* resize(int num);							//重新指定容器的长度为num，若容器变长，则以默认值填充新位置。
												//如果容器变短，则末尾超出容器长度的元素被删除。 
	* resize(int num, elem);					//重新指定容器的长度为num，若容器变长，则以elem值填充新位置。
												//如果容器变短，则末尾超出容器长度的元素被删除 
	*/
	if (v1->empty()) {
		std::cout << "v1 is empty" << std::endl;
	}

	int cap = v1->capacity();
	std::cout << "capacity" << cap << std::endl;

	int size = v1->size();
	std::cout << "size" << size << std::endl;


	/**
	* 对vector容器进行插入、删除操作
	* push_back(ele);												//尾部插入元素ele
	* pop_back();													//删除最后一个元素
	* insert(const_iterator pos, ele);								//迭代器指向位置pos插入元素ele
	* insert(const_iterator pos, int count,ele);					//迭代器指向位置pos插入count个元素ele
	* erase(const_iterator pos);									//删除迭代器指向的元素
	* erase(const_iterator start, const_iterator end);				//删除迭代器从start到end之间的元素
	* clear();                                                      //删除容器中所有元素
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
	* 对vector中的数据的存取操作
	* at(int idx);					//返回索引idx所指的数据
	* operator[];					//返回索引idx所指的数据
	* front();						//返回容器中第一个数据元素
	* back();						//返回容器中最后一个数据元素
	*/

	std::cout << v1->front() << std::endl;
	std::cout << v1->back() << std::endl;

	/*
	* 实现两个容器内元素进行互换
	* swap(vec);					// 将vec与本身的元素互换
	*/
	v1->swap(*v2);
	printVector(v1);
	printVector(v2);

	/*
	* 减少vector在动态扩展容量时的扩展次数
	* reserve(int len);				//容器预留len个元素长度，预留位置不初始化，元素不可访问。
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