#include "stdafx.h"
#include "head.h"

/*��Ŀ����
��һ����ά�����У�ÿһ�ж����մ����ҵ�����˳������ÿһ�ж����մ��ϵ��µ�����˳������
�����һ������������������һ����ά�����һ���������ж��������Ƿ��и�������
����˼·��һ���ǣ���ÿһ�п���������������飬���ö��ֲ��ң�ͨ������ÿһ�еõ��𰸣�ʱ�临�Ӷ���nlogn
	����һ��˼·�ǣ����ö�ά�������ϵ��£������ҵ����Ĺ��ɣ�
	��ôѡȡ���Ͻǻ������½ǵ�Ԫ��a[row][col]��target���бȽϣ�
	��targetС��Ԫ��a[row][col]ʱ����ôtarget�ض���Ԫ��a�����е����,��col--��
	��target����Ԫ��a[row][col]ʱ����ôtarget�ض���Ԫ��a�����е��±�,��row++��
��һ�ֵ�ʱ�临�Ӷ���mlogn���ڶ�����m+n����m��n�У���ֻ����m��nС�ܶ�ʱ��һ�ַ����űȵڶ��ֺ�
�˴�ʵ�ֵڶ��֡�
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
	//�����½� row = rows-1, col = 0;
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
/*��Ŀ����
��ʵ��һ����������һ���ַ����еĿո��滻�ɡ�%20����
���磬���ַ���ΪWe Are Happy.�򾭹��滻֮����ַ���ΪWe%20Are%20Happy��
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
��Ŀ����
����һ��������β��ͷ��ӡ����ÿ���ڵ��ֵ��
˼·���������ã�Ȼ���ٴ�ͷ��β����β��ͷ����ӡ��
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

/*��Ŀ����
����ĳ��������ǰ���������������Ľ�������ؽ����ö�������
���������ǰ���������������Ľ���ж������ظ������֡�
��������ǰ���������{1,2,4,7,3,5,6,8}�������������{4,7,2,1,5,3,8,6}�����ؽ������������ء�
˼·��ǰ���������->��->�ң������������->��->�ҡ�
�ݹ����⣺������������ȡǰ�������һ�������ɸ����������������ҳ������������������ݹ�������������
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
	else if(ModeBiT::DepthFirstTravel == printmode){
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
		return ;
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
��Ŀ����
������ջ��ʵ��һ�����У���ɶ��е�Push��Pop������ �����е�Ԫ��Ϊint���͡�
˼·��stack1 ��ջ�� stack2 ��ջ����stack2���� stack1 �ǿ�ʱ����1 ȫ����ջ 2��
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
��Ŀ����
��һ�������ʼ�����ɸ�Ԫ�ذᵽ�����ĩβ�����ǳ�֮Ϊ�������ת�� 
����һ���ǵݼ�����������һ����ת�������ת�������СԪ�ء� 
��������{3,4,5,1,2}Ϊ{1,2,3,4,5}��һ����ת�����������СֵΪ1��
NOTE������������Ԫ�ض�����0���������СΪ0���뷵��0��
˼·����СԪ�رض���ʱ�Ǹ�ǰ���ں�ĺ�Ԫ�ء�
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

/*��Ŀ����
��Ҷ�֪��쳲��������У�����Ҫ������һ������n���������쳲��������еĵ�n�n<=39
˼·��ʹ��vector<int> fib ���飬���� fib[i] = fib[i-1]+fib[i-1] �㷨
0,1,1,2,3,5,8,13,21,34,55,89,144,233������OEIS�е�����A000045��
�ر�ָ����0���ǵ�һ����ǵ����
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
/*��Ŀ����
һֻ����һ�ο�������1��̨�ף�Ҳ��������2���������������һ��n����̨���ܹ��ж�����������
˼·����̬�滮���⣬
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
/*��Ŀ����
һֻ����һ�ο�������1��̨�ף�Ҳ��������2��������Ҳ��������n���������������һ��n����̨���ܹ��ж�����������
˼·��	��ʼ������x(2) = 2, x(1) = 1;
		���ƹ�ʽ��x(n) = x(n-1)+x(n-2).....+x(1) 
				  x(n-1) = x(n-2)+......+x(1)
		���ƽ����x(n) = 2^(n-1)*(x(1))
,
*/
int jumpFloorII(int number) {
	return int(pow(2, number - 1));
}
/*��Ŀ����
���ǿ�����2*1��С���κ��Ż�������ȥ���Ǹ���ľ��Ρ�������n��2*1��С�������ص��ظ���һ��2*n�Ĵ���Σ��ܹ��ж����ַ�����
˼·��
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
/*��Ŀ����
����һ��������������������Ʊ�ʾ��1�ĸ��������и����ò����ʾ��
˼·������λ���� n & (n-1) �൱���������ұ�һ��1�����������������е�1 ʱ��n==0
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
/*��Ŀ����
����һ��double���͵ĸ�����base��int���͵�����exponent����base��exponent�η���
˼·��
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
/*��Ŀ����
����һ���������飬ʵ��һ�����������������������ֵ�˳��
ʹ�����е�����λ�������ǰ�벿�֣����е�ż��λ��λ������ĺ�벿�֣�
����֤������������ż����ż��֮������λ�ò��䡣
˼·������ʼ��������ż�������ƶ���������������ǰ�ƶ�
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
/*��Ŀ����
����һ��������ת�����������������Ԫ�ء�
˼·��
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
/*��Ŀ����
���������������������������������ϳɺ��������Ȼ������Ҫ�ϳɺ���������㵥����������
˼·��
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
/*��Ŀ����
�������ö�����A��B���ж�B�ǲ���A���ӽṹ����ps������Լ��������������һ�������ӽṹ��
˼·���������壺��B����A����һ����㼰��������������ͬ��ʽ���ɵ�����
      �ж�������
	  ��������:
	  {8,8,7,9,2,#,#,#,#,4,7},{8,9,2}

	  ��Ӧ���Ӧ��Ϊ:

	  true

	  ������Ϊ:

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
/*��Ŀ����
���������Ķ�����������任ΪԴ�������ľ���
˼·���������������Ը��ڵ�Ϊ�Գ�����жԵ���ע�⣺���������󣬲��ǵݹ�ķ�ʽ��
��̽�����ݹ齻������������ָ�롣
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
/*��Ŀ����
����һ�����󣬰��մ���������˳ʱ���˳�����δ�ӡ��ÿһ�����֣�
���磬����������¾��� 1 2 3 4 5 6 7 8 9 10 11 12 13 14 15 16 
�����δ�ӡ������1,2,3,4,8,12,16,15,14,13,9,5,6,7,11,10.
˼·��˳ʱ�룺�ȵ����У�����n,�ٵ����У�����n,�ٵݼ��е���0���ٵݼ��У�����1���ٵ����У����ֱ������ȫ�������
	����洢��vector �������൱�ھ���������±��һһ��Ӧ��
*/
vector<int> printMatrix(vector<vector<int> > matrix) {
	vector<int> ret;
	ret.clear();

	int row = matrix.size();
	int col = matrix[0].size();
	//ÿ�δ�ӡһȦ������Ȧ��
	int circle = ((row < col ? row : col) - 1) / 2 + 1;
	//ѭ����ӡcircle Ȧ
	for (int i = 0; i < circle; ++i){
		//��i��
		int j = i;
		for (; j < col - i; ++j)
			ret.push_back(matrix[i][j]);
		//��circle-i��
		int temp = i + 1;
		--j;
		for (; temp < row - i; ++temp)
			ret.push_back(matrix[temp][j]);
		//��circle-i��
		--temp;
		--j;
		for (; j >= i && (row - i - 1 != i); --j)
			ret.push_back(matrix[temp][j]);
		//��i��
		++j;
		--temp;
		for (; temp > i && (col-i-1!=i); --temp)
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
/*��Ŀ����
����ջ�����ݽṹ�����ڸ�������ʵ��һ���ܹ��õ�ջ��СԪ�ص�min������
˼·��
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
/*��Ŀ����
���������������У���һ�����б�ʾջ��ѹ��˳�����жϵڶ��������Ƿ�Ϊ��ջ�ĵ���˳��
����ѹ��ջ���������־�����ȡ���������1,2,3,4,5��ĳջ��ѹ��˳������4��5,3,2,1�Ǹ�ѹջ���ж�Ӧ��һ���������У�
��4,3,5,1,2�Ͳ������Ǹ�ѹջ���еĵ������С���ע�⣺���������еĳ�������ȵģ�
˼·����һ��ջģ����ջ���ջ���̡���ѹ��˳�����������ջ��ֱ����ջ��������ջ�������ջ˳�����������ȣ�
	������ģ��ջ�����ջ˳��������ͬ�����������޸ĳ�ջ˳�������������* ���ѭ����������stack�л���Ԫ�أ���˵��arr2���в���pop���С�
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
/*��Ŀ����
�������´�ӡ����������ÿ���ڵ㣬ͬ��ڵ�������Ҵ�ӡ��
˼·����������������õݹ�ķ�ʽ,�������У�ȡ������ͷ�ڵ㲢��ӡ�������������ӽڵ���ӣ�
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
/*��Ŀ����
����һ���������飬�жϸ������ǲ���ĳ�����������ĺ�������Ľ��������������Yes,�������No��
�������������������������ֶ�������ͬ��
˼·��
*/
bool VerifySquenceOfBST(vector<int> sequence) {

}