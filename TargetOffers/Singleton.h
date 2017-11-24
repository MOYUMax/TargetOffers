#pragma once
#include <iostream>

using namespace std;

class Singleton
{

public:
	

	static Singleton* getInstance()
	{
		static Singleton instance;//局部静态变量
		cout << "Singleton getInstance...." << &instance << endl;
		return &instance;
	}
	
private:

	Singleton();
	//把复制构造函数和=操作符也设为私有,防止被复制
	Singleton(const Singleton &);
	Singleton & operator=(const Singleton&);
	//私有构造实例静态函数
	
	~Singleton();

};

