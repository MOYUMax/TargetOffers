#include "stdafx.h"
#include "head.h"

/*��Ŀ����
��һ����ά�����У�ÿһ�ж����մ����ҵ�����˳������ÿһ�ж����մ��ϵ��µ�����˳������
�����һ������������������һ����ά�����һ���������ж��������Ƿ��и�������

*/
bool Find(int target, vector<vector<int> > array) {
	/*for each (vector<int> var in array)
	{
		if (binary_search(var.begin(), var.end(), target) == true)
			return true;
	}*/
	for (vector<vector<int>>::iterator vvit = array.begin(); vvit != array.end(); ++vvit)
	{
		if (binary_search(vvit->begin(), vvit->end(), target) == true)
			return true;
	}
	return false;
}
void testFind()
{
	vector<vector<int>> array = {
		{1,2,3},
		{4,5,6},
		{7,8,9}
	};
	int target = 0;
	while (cin >> target){
		cout << "The " << target << " is " << (Find(target, array) ? "" : "not ") << "in the array!" << endl;
		cout << "Number(exit ctl+c):";
	}
}
/*��Ŀ����
��ʵ��һ����������һ���ַ����еĿո��滻�ɡ�%20����
���磬���ַ���ΪWe Are Happy.�򾭹��滻֮����ַ���ΪWe%20Are%20Happy��
*/
void replaceSpace(char *str, int length) {
	string tempstr(str);
	for (string::iterator sit = tempstr.begin(); sit != tempstr.end(); ++sit){
		if (' ' == *sit){
			tempstr.replace(sit, sit + 1, "%");
			tempstr.insert(++sit, '2');
			tempstr.insert(sit, '0');
		}
	}
	cout << "tempstr:" << tempstr << endl;
	int len = tempstr.length();
	str = (char *)malloc(len + 1);
	tempstr.copy(str, len, 0);
	str[len + 1] = '\0';
	cout << "str:" << str << endl;
}
void testreplaceSpace()
{
	char *str = "I want to make money!";
	replaceSpace(str, strlen(str));
	cout << "After replace, str = " << str << endl;
}