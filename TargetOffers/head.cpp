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

void createBiT(TreeNode * & R ,const vector<int> & pre, const vector<int> & vin, int sp, int ep, int sv, int ev)
{
	if (sp <= ep)
	{
		R = new TreeNode(0);
		R->val = pre[sp];
		R->left = R->right = nullptr;
		int pos = -1;
		for (int i = sv; i <= ev;++i)
			if (vin[i] == pre[sp]){
				pos = i;
				break;
			}
		if (pos < 0)
			return;
		createBiT(R->left, pre, vin, sp + 1, sp + pos -sv , sv,pos-1 );
		createBiT(R->right, pre, vin, sp + pos -sv + 1, ep, pos + 1, ev);
	}
}

void printBiT(TreeNode * root,const ModeBiT & printmode)
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
	else{
		printBiT(root->left, printmode);
		printBiT(root->right, printmode);
		cout << root->val;
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
void push(int node) {
	stack1.push(node);
}

int pop() {
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
	vector<int> fib(n+2);
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
	while (cin>>n){
		cout << "The Fib(" << n << ") = " << Fibonacci(n) << endl;
	}
}
/*题目描述
一只青蛙一次可以跳上1级台阶，也可以跳上2级。求该青蛙跳上一个n级的台阶总共有多少种跳法。
思路：
*/
int jumpFloor(int number) {

}