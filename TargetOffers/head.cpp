#include "stdafx.h"
#include "head.h"

/*题目描述
在一个二维数组中，每一行都按照从左到右递增的顺序排序，每一列都按照从上到下递增的顺序排序。
请完成一个函数，输入这样的一个二维数组和一个整数，判断数组中是否含有该整数。
两种思路：一种是，把每一行看成有序递增的数组，利用二分查找，通过遍历每一行得到答案，时间复杂度是nlogn
另外一种思路是：利用二维数组由上到下，由左到右递增的规律，
那么选取右上角或者左下角的元素a[row][col]与target进行比较，
当target小于元素a[row][col]时，那么target必定在元素a所在行的左边,即col--；
当target大于元素a[row][col]时，那么target必定在元素a所在列的下边,即row++；
第一种的时间复杂度是mlogn，第二种是m+n，（m行n列），只有在m比n小很多时第一种方法才比第二种好
此处实现第二种。
*/
bool Find(int target, vector<vector<int> > array) {
	/*for each (vector<int> var in array)
	{
	if (binary_search(var.begin(), var.end(), target) == true)
	return true;
	}
	for (vector<vector<int>>::iterator vvit = array.begin(); vvit != array.end(); ++vvit)
	{
	if (binary_search(vvit->begin(), vvit->end(), target) == true)
	return true;
	}
	return false;
	*/
	if (array.empty())
		return false;
	bool found = false;
	int rows = array.size();
	int cols = array.at(0).size();
	//从左下角 row = rows-1, col = 0;
	int row = rows - 1;
	int col = 0;

	while (row >= 0 && col < cols){
		if (target == array[row][col])
		{
			found = true;
			break;
		}
		else if (target < array[row][col]){
			--row;
		}
		else{
			++col;
		}
	}
	return found;
}
void testFind()
{
	vector<vector<int>> array = {
		{ 1, 2, 3 },
		{ 4, 5, 6 },
		{ 7, 8, 9 }
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
	int i = 0, count = 0;
	while (str[i] != '\0')
	{
		if (str[i] == ' ')
			++count;
		++i;
	}
	if (count == 0)
		return;

	int j = i + 2 * count;
	while (i >= 0 && j >= 0){
		if (str[i] == ' '){
			str[j--] = '0';
			str[j--] = '2';
			str[j] = '%';
		}
		else{
			str[j] = str[i];
		}
		--i;
		--j;
	}
	return;
	/*string tempstr(str);
	for (string::iterator sit = tempstr.begin(); sit != tempstr.end(); ++sit){
	if (' ' == *sit){
	tempstr.replace(sit, sit + 1, "%");
	tempstr.insert(++sit, '0');
	tempstr.insert(sit, '2');
	}
	}
	cout << "tempstr:" << tempstr << endl;
	int len = tempstr.length();
	str = (char *)malloc(len + 1);
	tempstr.copy(str, len, 0);
	str[len + 1] = '\0';
	cout << "str:" << str << endl;*/
}
void testreplaceSpace()
{
	char str[1024] = " helloworld";
	replaceSpace(str, strlen(str));
	cout << "After replace, str = " << str << endl;
}

/*
题目描述
输入一个链表，从尾到头打印链表每个节点的值。
思路：将链表倒置，然后再从头（尾）到尾（头）打印。
*/
vector<int> printListFromTailToHead(ListNode* head) {
	vector<int> result;
	if (nullptr == head)
		return result;
	ListNode * p = head;
	while (nullptr != p)
	{
		vector<int>::iterator vit = result.begin();
		result.insert(vit, p->val);
		p = p->next;
	}
	return result;
	/*ListNode * p, * q, *r;
	p = head;
	q = p->next;
	r = q->next;
	q->next = p;
	p->next = nullptr;
	p = q;
	q = r;
	while (nullptr != q->next){
	r = q->next;
	q->next = p;
	p = q;
	q = r;
	}
	q->next = p;
	p = q;
	head = p;
	q = nullptr;
	r = nullptr;
	while (nullptr != p){
	result.push_back(p->val);
	p = p->next;
	}
	return result;*/
}

void testprintListFromTailToHead()
{
	ListNode * head = new ListNode(0);
	ListNode * p = head;
	for (int i = 0; i < 5; ++i)
	{
		p->next = new ListNode(i);
		p = p->next;
	}
	vector<int> result = printListFromTailToHead(head->next);
	for (size_t i = 0; i < result.size(); ++i)
	{
		cout << result.at(i) << " ";
	}
}

/*题目描述
输入某二叉树的前序遍历和中序遍历的结果，请重建出该二叉树。
假设输入的前序遍历和中序遍历的结果中都不含重复的数字。
例如输入前序遍历序列{1,2,4,7,3,5,6,8}和中序遍历序列{4,7,2,1,5,3,8,6}，则重建二叉树并返回。
思路：前序遍历：根->左->右，中序遍历：左->根->右。
递归的求解：基本操作，读取前序数组第一个数生成根，在中序数组中找出左子树和右子树，递归生成左右子树
*/
TreeNode* reConstructBinaryTree(vector<int> pre, vector<int> vin) {
	if (pre.size() <= 0 || vin.size() <= 0 || pre.size() != vin.size())
		return nullptr;
	TreeNode * root = nullptr;
	int ep = (int)pre.size() - 1;
	int ev = (int)vin.size() - 1;
	createBiT(root, pre, vin, 0, ep, 0, ev);
	return root;
}

void createBiT(TreeNode * & R, const vector<int> & pre, const vector<int> & vin, int sp, int ep, int sv, int ev)
{
	if (sp <= ep)
	{
		R = new TreeNode(0);
		R->val = pre[sp];
		R->left = R->right = nullptr;
		int pos = -1;
		for (int i = sv; i <= ev; ++i)
			if (vin[i] == pre[sp]){
				pos = i;
				break;
			}
		if (pos < 0)
			return;
		createBiT(R->left, pre, vin, sp + 1, sp + pos - sv, sv, pos - 1);
		createBiT(R->right, pre, vin, sp + pos - sv + 1, ep, pos + 1, ev);
	}
}

void printBiT(TreeNode * root, const ModeBiT & printmode)
{
	if (nullptr == root)
		return;
	if (ModeBiT::PreOrder == printmode)
	{
		cout << root->val;
		printBiT(root->left, printmode);
		printBiT(root->right, printmode);
	}
	else if (ModeBiT::InOrder == printmode){
		printBiT(root->left, printmode);
		cout << root->val;
		printBiT(root->right, printmode);
	}
	else if (ModeBiT::PostOrder == printmode){
		printBiT(root->left, printmode);
		printBiT(root->right, printmode);
		cout << root->val;
	}
	else if (ModeBiT::BreadthFirstTravel == printmode){
		queue<TreeNode*> qu;
		qu.push(root);
		breadth_first_travel(qu);
	}
	else if (ModeBiT::DepthFirstTravel == printmode){
		stack<TreeNode *> st;
		st.push(root);
		depth_first_travel(st);
	}
	else{
		cout << "Printmode error, Please check!\n";
	}
}
void breadth_first_travel(queue<TreeNode*> & qu){
	if (qu.empty())
		return;
	else
	{
		TreeNode * front = qu.front();
		if (nullptr == front)
			return;
		cout << front->val << " ";
		if (nullptr != front->left)
			qu.push(front->left);
		if (nullptr != front->right)
			qu.push(front->right);
		qu.pop();
		breadth_first_travel(qu);
	}
}
void depth_first_travel(stack<TreeNode *> & st){
	if (st.empty())
		return;
	else{
		TreeNode * top = st.top();
		cout << top->val << " ";
		st.pop();
		if (nullptr != top->right)
			st.push(top->right);
		if (nullptr != top->left)
			st.push(top->left);
		depth_first_travel(st);
	}
}
void testreConstructBinaryTree()
{
	vector<int> pre = { 1, 2, 4, 7, 3, 5, 6, 8 };
	vector<int> vin = { 4, 7, 2, 1, 5, 3, 8, 6 };
	TreeNode * root = reConstructBinaryTree(pre, vin);
	cout << "PreOrder Print:";
	printBiT(root, ModeBiT::PreOrder);
	cout << "\nInOrder Print:";
	printBiT(root, ModeBiT::InOrder);
	cout << "\nPostOrder Print:";
	printBiT(root, ModeBiT::PostOrder);
}

/*
题目描述
用两个栈来实现一个队列，完成队列的Push和Pop操作。 队列中的元素为int类型。
思路：stack1 入栈， stack2 出栈，当stack2空且 stack1 非空时，将1 全部入栈 2。
*/
stack<int> stack1;
stack<int> stack2;
void Push(int node) {
	stack1.push(node);
}

int Pop() {
	int ret = -1;
	if (stack2.empty()){
		while (!stack1.empty())
		{
			stack2.push(stack1.top());
			stack1.pop();
		}
	}
	ret = stack2.top();
	stack2.pop();
	return ret;
}

/*
题目描述
把一个数组最开始的若干个元素搬到数组的末尾，我们称之为数组的旋转。
输入一个非递减排序的数组的一个旋转，输出旋转数组的最小元素。
例如数组{3,4,5,1,2}为{1,2,3,4,5}的一个旋转，该数组的最小值为1。
NOTE：给出的所有元素都大于0，若数组大小为0，请返回0。
思路：最小元素必定就时那个前大于后的后元素。
*/
int minNumberInRotateArray(vector<int> rotateArray) {
	if (rotateArray.size() <= 0)
		return 0;
	for (size_t i = 1; i < rotateArray.size(); ++i){
		if (rotateArray[i] < rotateArray[i - 1])
			return rotateArray[i];
	}
	return 0;
}

/*题目描述
大家都知道斐波那契数列，现在要求输入一个整数n，请你输出斐波那契数列的第n项。n<=39
思路：使用vector<int> fib 数组，采用 fib[i] = fib[i-1]+fib[i-1] 算法
0,1,1,2,3,5,8,13,21,34,55,89,144,233……（OEIS中的数列A000045）
特别指出：0不是第一项，而是第零项。
*/
int Fibonacci(int n) {
	if (n > 39)
		return -1;
	vector<int> fib(n + 2);
	fib[0] = 0;
	fib[1] = 1;
	for (int i = 2; i <= n; ++i)
	{
		fib[i] = fib[i - 1] + fib[i - 2];
	}
	return fib[n];
}
void testFibonacci()
{
	int n;
	while (cin >> n){
		cout << "The Fib(" << n << ") = " << Fibonacci(n) << endl;
	}
}
/*题目描述
一只青蛙一次可以跳上1级台阶，也可以跳上2级。求该青蛙跳上一个n级的台阶总共有多少种跳法。
思路：动态规划问题，
*/
int jumpFloor(int number) {
	if (number < 3)
		return number;
	vector<int> steps;
	steps.push_back(0);
	steps.push_back(1);
	steps.push_back(2);

	for (int i = 3; i <= number; ++i)
	{
		steps.push_back(steps[i - 1] + steps[i - 2]);
	}
	return steps[number];
}

void testjumpFloor()
{
	int number;
	while (cin >> number)
	{
		int result = jumpFloor(number);
		cout << "The stair:" << number << " has " << result << " ways to Jump" << endl;
	}
}
/*题目描述
一只青蛙一次可以跳上1级台阶，也可以跳上2级……它也可以跳上n级。求该青蛙跳上一个n级的台阶总共有多少种跳法。
思路：	初始条件：x(2) = 2, x(1) = 1;
递推公式：x(n) = x(n-1)+x(n-2).....+x(1)
x(n-1) = x(n-2)+......+x(1)
递推结果：x(n) = 2^(n-1)*(x(1))
,
*/
int jumpFloorII(int number) {
	return int(pow(2, number - 1));
}
/*题目描述
我们可以用2*1的小矩形横着或者竖着去覆盖更大的矩形。请问用n个2*1的小矩形无重叠地覆盖一个2*n的大矩形，总共有多少种方法？
思路：
*/
int rectCover(int number) {
	if (number < 1)
		return 0;
	vector<int> steps;
	steps.push_back(0);
	steps.push_back(1);
	steps.push_back(2);

	for (int i = 3; i <= number; ++i)
	{
		steps.push_back(steps[i - 1] + steps[i - 2]);
	}
	return steps[number];
}
/*题目描述
输入一个整数，输出该数二进制表示中1的个数。其中负数用补码表示。
思路：利用位运算 n & (n-1) 相当于消掉最右边一个1，从左往右消掉所有的1 时，n==0
*/
int  NumberOf1(int n) {
	int count = 0;
	while (n != 0)
	{
		++count;
		n = n&(n - 1);
	}
	return count;
}
void testNumberOf1()
{
	int n = 0;
	while (cin >> n){
		int result = NumberOf1(n);
		cout << "The count of 1 in:" << n << " is :" << result << endl;
	}
}
/*题目描述
给定一个double类型的浮点数base和int类型的整数exponent。求base的exponent次方。
思路：
*/
double Power(double base, int exponent) {
	//return pow(base, (double)exponent);
	long long p = abs((long long)exponent);
	double ret = 1.0;
	while (p > 0){
		if (p & 1) ret *= base;
		base *= base;
		p >>= 1;
	}
	return exponent < 0 ? 1 / ret : ret;
}
void testPower()
{
	double b;
	int e;
	while (cin >> b >> e){
		double result = Power(b, e);
		cout << "The " << b << "^" << e << " = " << result << endl;
	}
}
/*题目描述
输入一个整数数组，实现一个函数来调整该数组中数字的顺序，
使得所有的奇数位于数组的前半部分，所有的偶数位于位于数组的后半部分，
并保证奇数和奇数，偶数和偶数之间的相对位置不变。
思路：从左开始，把所有偶数往后移动，把所有奇数往前移动
*/
void reOrderArray(vector<int> &array) {
	int length = int(array.size());
	int i = 0, j = 1;
	int tempA = 0, tempB = 0;
	int count = 0;
	for (size_t p = 0; p < array.size(); ++p)
		if (0 != array[p] % 2)
			++count;

	while (i < count && j < length)
	{
		while (i < count && 0 != (array[i] % 2))
			++i;
		if (i == count)
			return;
		tempA = array[i];
		j = i + 1;

		while (j < length && 0 == (array[j] % 2)){
			tempB = array[j];
			array[j] = tempA;
			tempA = tempB;
			++j;
		}
		if (j == length)
			return;
		tempB = array[j];
		array[j] = tempA;
		array[i] = tempB;
		++i;
		++j;
		if (j == length - 1 && 0 == (array[j] % 2))
			return;
	}
	/*int length = int(array.size());
	vector<int>::iterator it = array.begin();
	for (int i = 0; i < length; ++i){
	if (*it % 2 == 0){
	int tmp = *it;
	array.erase(it);
	array.push_back(tmp);
	}
	else
	++it;
	}*/
}
void testreOrderArray()
{
	vector<int> array = { 1, 3, 5, 7, 2, 4, 6 };
	reOrderArray(array);
	cout << "After reOrderArray:";
	for (size_t i = 0; i < array.size(); ++i)
		cout << array[i] << " ";
}
/*题目描述
输入一个链表，反转链表后，输出链表的所有元素。
思路：
*/
ListNode* ReverseList(ListNode* pHead) {
	if (nullptr == pHead || nullptr == pHead->next)
		return pHead;
	ListNode * newHead = nullptr;
	ListNode * p = pHead;
	ListNode * q = nullptr;
	while (nullptr != p){
		q = p->next;
		p->next = newHead;
		newHead = p;
		p = q;
	}
	return newHead;
}
/*题目描述
输入两个单调递增的链表，输出两个链表合成后的链表，当然我们需要合成后的链表满足单调不减规则。
思路：
*/
ListNode* Merge(ListNode* pHead1, ListNode* pHead2)
{
	if (nullptr == pHead1 && nullptr == pHead2)
		return nullptr;
	if (nullptr == pHead1 && nullptr != pHead2)
		return pHead2;
	if (nullptr != pHead1 && nullptr == pHead2)
		return pHead1;

	ListNode *ret = nullptr;
	ListNode *p1, *p2;
	if (pHead1->val <= pHead2->val){
		ret = pHead1;
		p1 = pHead1->next;
		p2 = pHead2;
	}
	else{
		ret = pHead2;
		p1 = pHead1;
		p2 = pHead2->next;
	}
	ListNode *p = ret;
	while (nullptr != p1 && nullptr != p2){
		if (p1->val <= p2->val){
			p->next = p1;
			p1 = p1->next;
			p = p->next;
		}
		else{
			p->next = p2;
			p2 = p2->next;
			p = p->next;
		}
	}
	while (nullptr != p1){
		p->next = p1;
		p1 = p1->next;
		p = p->next;
	}
	while (nullptr != p2){
		p->next = p2;
		p2 = p2->next;
		p = p->next;
	}
	return ret;
}

void testMerge()
{
	ListNode *pHead1 = new ListNode(100), *pHead2 = new ListNode(222);
	for (int i = 5, j = 10; i > 0; --i, j -= 2){
		ListNode * tmp1 = new ListNode(i);
		tmp1->next = pHead1;
		pHead1 = tmp1;
		ListNode * tmp2 = new ListNode(j);
		tmp2->next = pHead2;
		pHead2 = tmp2;
	}
	ListNode *result = Merge(pHead1, pHead2);
	while (result){
		cout << result->val << " ";
		result = result->next;
	}
}
/*题目描述
输入两棵二叉树A，B，判断B是不是A的子结构。（ps：我们约定空树不是任意一个树的子结构）
思路：子树定义：树B是树A其中一个结点及其所有子孙以相同方式构成的树。
判定方法：
测试用例:
{8,8,7,9,2,#,#,#,#,4,7},{8,9,2}

对应输出应该为:

true

你的输出为:

false
*/
bool HasSubtree(TreeNode* pRoot1, TreeNode* pRoot2)
{
	bool flag = false;
	if (nullptr != pRoot1&&nullptr != pRoot2){
		if (pRoot1->val == pRoot2->val)
			flag = isSubTree(pRoot1, pRoot2);
		if (!flag)
			flag = HasSubtree(pRoot1->left, pRoot2);
		if (!flag)
			flag = HasSubtree(pRoot1->right, pRoot2);
	}
	return flag;
}

bool isSubTree(TreeNode* pRoot1, TreeNode* pRoot2){
	if (nullptr == pRoot2)
		return true;
	if (nullptr == pRoot1)
		return false;
	if (pRoot1->val != pRoot2->val)
		return false;
	return isSubTree(pRoot1->left, pRoot2->left) && isSubTree(pRoot1->right, pRoot2->right);
}
/*题目描述
操作给定的二叉树，将其变换为源二叉树的镜像。
思路：镜像：左右子树以根节点为对称轴进行对调（注意：进入子树后，不是递归的方式）
编程解决：递归交换左右子树的指针。
*/
void Mirror(TreeNode *pRoot) {
	if (nullptr == pRoot)
		return;
	else{
		TreeNode * temp = pRoot->left;
		pRoot->left = pRoot->right;
		pRoot->right = temp;
		Mirror(pRoot->left);
		Mirror(pRoot->right);
	}
}
void testMirror()
{
	vector<int> pre = { 1, 2, 4, 7, 3, 5, 6, 8 };
	vector<int> vin = { 4, 7, 2, 1, 5, 3, 8, 6 };
	TreeNode * root = reConstructBinaryTree(pre, vin);
	Mirror(root);
	cout << "PreOrder Print:";
	printBiT(root, ModeBiT::PreOrder);
	cout << "\nInOrder Print:";
	printBiT(root, ModeBiT::InOrder);
	cout << "\nPostOrder Print:";
	printBiT(root, ModeBiT::PostOrder);
}
/*题目描述
输入一个矩阵，按照从外向里以顺时针的顺序依次打印出每一个数字，
例如，如果输入如下矩阵： 1 2 3 4 5 6 7 8 9 10 11 12 13 14 15 16
则依次打印出数字1,2,3,4,8,12,16,15,14,13,9,5,6,7,11,10.
思路：顺时针：先递增列，到达n,再递增行，到达n,再递减列到达0，再递减行，到达1，再递增列，如此直到矩阵全部输出。
输出存储到vector 容器，相当于矩阵和数组下标的一一对应。
*/
vector<int> printMatrix(vector<vector<int> > matrix) {
	vector<int> ret;
	ret.clear();

	int row = matrix.size();
	int col = matrix[0].size();
	//每次打印一圈，计算圈数
	int circle = ((row < col ? row : col) - 1) / 2 + 1;
	//循环打印circle 圈
	for (int i = 0; i < circle; ++i){
		//第i行
		int j = i;
		for (; j < col - i; ++j)
			ret.push_back(matrix[i][j]);
		//第circle-i列
		int temp = i + 1;
		--j;
		for (; temp < row - i; ++temp)
			ret.push_back(matrix[temp][j]);
		//第circle-i行
		--temp;
		--j;
		for (; j >= i && (row - i - 1 != i); --j)
			ret.push_back(matrix[temp][j]);
		//第i列
		++j;
		--temp;
		for (; temp > i && (col - i - 1 != i); --temp)
			ret.push_back(matrix[temp][j]);
	}
	return ret;
}

void testprintMatrix()
{
	/*vector<vector<int>> mat{
		{ 1, 2, 3, 4 },
		{ 5, 6, 7, 8 },
		{ 9, 10, 11, 12 },
		{ 13, 14, 15, 16 }
		};*/
	/*vector<vector<int>> mat{
		{ 1 },
		{ 5 },
		{ 9 },
		{ 13 }
		};*/
	vector<vector<int>> mat{
		{ 1, 2, 3, 4 }
	};
	vector<int> result = printMatrix(mat);
	for (size_t i = 0; i < result.size(); ++i)
		cout << result.at(i) << " ";
}
/*题目描述
定义栈的数据结构，请在该类型中实现一个能够得到栈最小元素的min函数。
思路：
*/

void push(int value) {
	st.vt.push_back(value);
	++st.top;
}
void pop() {
	st.vt.pop_back();
	--st.top;
}
int top() {
	return st.vt[st.top];
}
int min() {
	if (st.top < 0)
		return INT_MIN;
	if (0 == st.top)
		return st.vt[0];
	int ret = st.vt[0];
	for (int i = 1; i <= st.top; ++i){
		if (ret > st.vt[i])
			ret = st.vt[i];
	}
	return ret;
}
void testStack()
{
	for (int i = 5; i > 0; --i)
		push(i);

	cout << "The min():" << min() << endl;
	cout << "The top():" << top() << endl;
	pop();
	cout << "The min():" << min() << endl;
	cout << "The top():" << top() << endl;
	push(0);
	push(100);
	cout << "The min():" << min() << endl;
	cout << "The top():" << top() << endl;
}
/*题目描述
输入两个整数序列，第一个序列表示栈的压入顺序，请判断第二个序列是否为该栈的弹出顺序。
假设压入栈的所有数字均不相等。例如序列1,2,3,4,5是某栈的压入顺序，序列4，5,3,2,1是该压栈序列对应的一个弹出序列，
但4,3,5,1,2就不可能是该压栈序列的弹出序列。（注意：这两个序列的长度是相等的）
思路：用一个栈模拟入栈与出栈过程。按压入顺序数组的数入栈，直到入栈的数（即栈顶）与出栈顺序数组的数相等，
则按逆序将模拟栈里与出栈顺序数组相同的数弹出；修改出栈顺序数组的索引。* 如果循环结束，而stack中还有元素，就说明arr2序列不是pop序列。
*/
bool IsPopOrder(vector<int> pushV, vector<int> popV) {
	int lenPush = int(pushV.size());
	int lenPop = int(popV.size());
	if (lenPush != lenPop)
		return false;
	stack<int> stk;
	int j = 0;
	for (int i = 0; i < lenPush; ++i){
		stk.push(pushV[i]);
		while (j < lenPop&&popV[j] == stk.top()){
			stk.pop();
			++j;
		}
	}
	if (!stk.empty())
		return false;
	else
		return true;
}
void testIsPopOrder()
{
	vector<int> PUSH{ 1, 2, 3, 4, 5 };
	vector<int> POPA{ 4, 5, 3, 2, 1 };
	vector<int> POPB{ 4, 3, 5, 1, 2 };
	cout << "POPA is Stack output from PUSH?" << IsPopOrder(PUSH, POPA) << endl;
	cout << "POPB is Stack output from PUSH?" << IsPopOrder(PUSH, POPB) << endl;
}
/*题目描述
从上往下打印出二叉树的每个节点，同层节点从左至右打印。
思路：层序遍历树，采用递归的方式,借助队列，取出队列头节点并打印，并将其左右子节点入队，
*/
vector<int> PrintFromTopToBottom(TreeNode* root) {
	vector<int> ret;
	deque<TreeNode *> dq;
	if (nullptr == root)
		return ret;
	else
	{
		dq.push_back(root);
		level_traversal(dq, ret);
	}
	return ret;
}
void level_traversal(deque<TreeNode*> & dq, vector<int> & vti)
{
	if (dq.empty())
		return;
	else{
		TreeNode * front = dq.front();
		vti.push_back(front->val);
		if (nullptr != front->left)
			dq.push_back(front->left);
		if (nullptr != front->right)
			dq.push_back(front->right);
		dq.pop_front();
		level_traversal(dq, vti);
	}
}
void testPrintFromTopToBottom()
{
	vector<int> pre = { 1, 2, 4, 7, 3, 5, 6, 8 };
	vector<int> vin = { 4, 7, 2, 1, 5, 3, 8, 6 };
	TreeNode * root = reConstructBinaryTree(pre, vin);
	vector<int> result = PrintFromTopToBottom(root);
	cout << "LevelTraversal Print:";
	for (auto i : result){
		cout << i << " ";
	}
	cout << "\nBreadthFirstTravel Print:";
	printBiT(root, ModeBiT::BreadthFirstTravel);
	cout << "\nDepthFirstTravel Print:";
	printBiT(root, ModeBiT::DepthFirstTravel);
}
/*题目描述
输入一个整数数组，判断该数组是不是某二叉搜索树的后序遍历的结果。如果是则输出Yes,否则输出No。
假设输入的数组的任意两个数字都互不相同。
思路：BST的后序序列的合法序列是，对于一个序列S，最后一个元素是x （也就是根），
如果去掉最后一个元素的序列为T，那么T满足：T可以分成两段，前一段（左子树）小于x，
后一段（右子树）大于x，且这两段（子树）都是合法的后序序列。完美的递归定义 : ) 。
注意：[5,4,3,2,1]和{ 1, 2, 3, 4, 5 }为特殊情况，
*/
bool VerifySquenceOfBST(vector<int> sequence) {
	int length = int(sequence.size());
	if (length < 1)
		return false;
	return verify_post_order_seq(sequence, 0, length - 1);
}
bool verify_post_order_seq(vector<int> & seq, int s, int e)
{
	if (s >= e)return true;
	int i = e - 1;
	while (i >= s && seq[i]>seq[e])
		--i;
	for (int j = i - 1; j >= s; --j)if (seq[j] > seq[e])return false;
	return verify_post_order_seq(seq, s, i) && verify_post_order_seq(seq, i + 1, e - 1);
}
/*bool verify_post_order_seq(vector<int> & seq, int s, int e)
{
int length = e - s + 1;
bool flag = false;
if (length > 3){
int ls = s;
int rs = ls;
while (seq[rs] < seq[e])
++rs;
int le = rs - 1;
int re = e - 1;
for (int i = rs; i <= re; ++i)
if (seq[i] <= seq[e])
return false;
return verify_post_order_seq(seq, ls, le) && verify_post_order_seq(seq, rs, re);
}
else if(length == 3){
if (seq[s] < seq[e] && seq[e] < seq[e - 1])
flag = true;
else if (seq[s]<seq[s + 1] && seq[s + 1] < seq[e])
flag = true;
else if (seq[s] > seq[s + 1] && seq[s + 1]>seq[e])
flag = true;
}
else {
flag = true;
}
return flag;
}*/
void testVerifySquenceOfBST()
{
	//vector<int> PostOrderSeq = { 5, 7, 6, 9, 11, 10, 8 };
	//vector<int> PostOrderSeq = { 4, 6, 12, 8, 16, 14, 10 };
	//vector<int> PostOrderSeq = { 5, 7, 6, 11, 12, 10, 8 };
	vector<int> PostOrderSeq = { 1, 2, 3, 4, 5 };
	cout << "The Seq " << (VerifySquenceOfBST(PostOrderSeq) ? "is" : "isn't") << " a PostOrder of BST !\n ";
}
/*题目描述
输入一颗二叉树和一个整数，打印出二叉树中结点值的和为输入整数的所有路径。
路径定义为从树的根结点开始往下一直到叶结点所经过的结点形成一条路径。
思路：深度优先遍历所有路径，存在vector<int> 中, 如果满足到叶节点时 = expectNumber Push 并返回
*/
vector<vector<int> > FindPath(TreeNode* root, int expectNumber) {
	vector<vector<int>> ret;
	if (nullptr == root)
		return ret;
	stack<TreeNode*> stk;
	stk.push(root);
	vector<int> path;
	int sumPath = 0;
	expectPath(stk, ret, path, sumPath, expectNumber);
	return ret;
}
bool isLeaf(TreeNode * node)
{
	return (nullptr == node->left && nullptr == node->right) ? true : false;
}
void expectPath(stack<TreeNode *> & stk, vector<vector<int>> & allPath, vector<int> & currentPath,int & sumPath, int expectNumber)
{
	TreeNode * root = stk.top();
	currentPath.push_back(root->val);
	sumPath += root->val;
	if (isLeaf(root)){
		if (expectNumber == sumPath){
			vector<int> add = currentPath;
			allPath.push_back(add);
		}
	}
	else{
		if (nullptr != root->left){
			stk.push(root->left);
			expectPath(stk, allPath, currentPath, sumPath, expectNumber);
		}
		if (nullptr != root->right){
			stk.push(root->right);
			expectPath(stk, allPath, currentPath, sumPath, expectNumber);
		}
	}
	currentPath.pop_back();
	sumPath -= root->val;
	stk.pop();
}
void testFindPath()
{
	vector<int> pre = { 1, 2, 6, 7, 3, 5, 4, 8 };
	vector<int> vin = { 6, 7, 2, 1, 5, 3, 8, 4 };
	TreeNode * root = reConstructBinaryTree(pre, vin);
	vector<vector<int>> result = FindPath(root, 16);
	for (auto vvi : result){
		for (auto vi : vvi){
			cout << vi << " ";
		}
		cout << endl;
	}
	//cout << "PreOrder Print:";
	//printBiT(root, ModeBiT::PreOrder);
}
/*题目描述
输入一个复杂链表（每个节点中有节点值，以及两个指针，一个指向下一个节点，另一个特殊指针指向任意一个节点），
返回结果为复制后复杂链表的head。（注意，输出结果中请不要返回参数中的节点引用，否则判题程序会直接返回空）
思路：
*/
//思路1：先以主线next复制所有节点，再通过查找逐一匹配每个节点的random，然后设置复制节点的random
//RandomListNode* Clone(RandomListNode* pHead)
//{
//	if (nullptr == pHead)
//		return nullptr;
//	RandomListNode* ret = new RandomListNode(pHead->label);
//	RandomListNode* p = ret;
//	RandomListNode* h = pHead;
//	while (h->next){
//		RandomListNode* q = new RandomListNode(h->next->label);
//		p->next = q;
//		p = q;
//		h = h->next;
//	}
//	h = pHead;
//	p = ret;
//	RandomListNode* q;
//	RandomListNode* r;
//	while (nullptr != h){
//		if (nullptr != h->random){
//			r = pHead;
//			q = ret;
//			while (r != h->random){
//				r = r->next;
//				q = q->next;
//			}
//			p->random = q;
//		}
//		h = h->next;
//		p = p->next;
//	}
//	return ret;
//}

//思路2：由于思路1采用的查找方法复杂度为O(n^2)，
//可以通过借助哈希表存储 <N, copy_N>，原表中 N->random 指向的 S，通过hash表可以直接找到 copy_N->random指向copy_S
//RandomListNode* Clone(RandomListNode* pHead){
//	if (nullptr == pHead)
//		return nullptr;
//	RandomListNode* ret = new RandomListNode(pHead->label);
//	RandomListNode* h = pHead;
//	RandomListNode* p = ret;
//
//  //hash_map<RandomListNode*, RandomListNode*> hm;
//	unordered_map<RandomListNode*, RandomListNode*> hm;
//	hm.insert(pair<RandomListNode*, RandomListNode*>(h, p));
//	while (nullptr != h->next){
//		RandomListNode* q = new RandomListNode(h->next->label);
//		p->next = q;		
//		p = q;
//		h = h->next;
//		hm.insert(pair<RandomListNode*, RandomListNode*>(h, p));
//	}
//	
//	h = pHead;
//	p = ret;
//	while (nullptr != h){
//		if (nullptr != h->random){
//			p->random = hm.at(h->random);
//		}
//		h = h->next;
//		p = p->next;
//	}
//	return ret;
//}

//思路3：为了不用额外空间，仍使时间复杂度为O(n)，我们在每次复制N时，将 copy_N 插入在N的后面，即 copy_N->next = N->next, N->next = copy_N;
// 这样，某个节点的random 就是原节点的random 的 next
/*
测试用例:
{1, 2, 3, 4, 5, 3, 5, #, 2, #}
对应输出应该为:
{1, 2, 3, 4, 5, 3, 5, #, 2, #}
你的输出为:
空。请检查一下你的代码，有没有循环输入处理多个case。*/
RandomListNode* Clone(RandomListNode* pHead){
	if (nullptr == pHead)
		return nullptr;
	RandomListNode* ret = new RandomListNode(pHead->label);
	RandomListNode* h = pHead;
	RandomListNode* p = ret;
	p->next = h->next;
	h->next = p;
	h = p->next;
	while (nullptr != h){
		RandomListNode* q = new RandomListNode(h->label);
		q->next = h->next;
		h->next = q;
		h = q->next;
	}
	h = pHead;
	p = ret;
	while (nullptr != h){
		p = h->next; // h->next 必定是非空指针，因为之前逐一复制并放在原节点后面，所以必定存在
		if (nullptr != h->random){
			p->random = h->random->next;
		}
		h = p->next;		
	}

	h = pHead;
	while (nullptr != h->next){
		p = h->next;
		h->next = p->next;
		h = p;
	}
	return ret;
}
void testClone()
{
	RandomListNode* head = new RandomListNode(0);
	RandomListNode* p;
	for (int i = 5; i > 0; --i)
	{
		p = new RandomListNode(i);
		p->next = head->next;
		head->next = p;
	}
	head->random = p->next;
	p->random = head;
	p->next->random = p->next->next;
	p->next->next->next->next->random = p->next->next->next;
	RandomListNode* result = Clone(head);
	cout << "Clone end!\n";
}
/*题目描述
输入一棵二叉搜索树，将该二叉搜索树转换成一个排序的双向链表。要求不能创建任何新的结点，只能调整树中结点指针的指向。
思路：
*/
TreeNode* Convert(TreeNode* pRootOfTree)
{

}