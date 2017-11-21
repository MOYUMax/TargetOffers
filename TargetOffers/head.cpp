#include "stdafx.h"
#include "head.h"

/*题目描述
在一个二维数组中，每一行都按照从左到右递增的顺序排序，每一列都按照从上到下递增的顺序排序。
请完成一个函数，输入这样的一个二维数组和一个整数，判断数组中是否含有该整数。

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
/*题目描述
请实现一个函数，将一个字符串中的空格替换成“%20”。
例如，当字符串为We Are Happy.则经过替换之后的字符串为We%20Are%20Happy。
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