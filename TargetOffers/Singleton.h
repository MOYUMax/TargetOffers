#pragma once
#include <iostream>

using namespace std;

class Singleton
{

public:
	

	static Singleton* getInstance()
	{
		static Singleton instance;//�ֲ���̬����
		cout << "Singleton getInstance...." << &instance << endl;
		return &instance;
	}
	
private:

	Singleton();
	//�Ѹ��ƹ��캯����=������Ҳ��Ϊ˽��,��ֹ������
	Singleton(const Singleton &);
	Singleton & operator=(const Singleton&);
	//˽�й���ʵ����̬����
	
	~Singleton();

};

