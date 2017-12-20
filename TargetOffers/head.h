#ifndef _HEAD_H
#define _HEAD_H

#include <iostream>
#include <string>
#include <set>
#include <vector>
#include <algorithm>
#include <stack>
#include <queue>
#include <hash_map>
#include <unordered_map>

using namespace std;

bool Find(int target, vector<vector<int> > array);
void testFind();
void replaceSpace(char *str, int length);
void testreplaceSpace();

//Definition for Single ListNode
struct ListNode {
	int val;
	struct ListNode *next;
	ListNode(int x) :
	val(x), next(NULL) {
	}
};
vector<int> printListFromTailToHead(ListNode* head);
void testprintListFromTailToHead();

//Definition for binary tree
struct TreeNode {
	int val;
	TreeNode *left;
	TreeNode *right;
	TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};
enum ModeBiT{ PreOrder, InOrder, PostOrder, BreadthFirstTravel, DepthFirstTravel };
TreeNode* reConstructBinaryTree(vector<int> pre, vector<int> vin);
void createBiT(TreeNode * & R, const vector<int> & pre, const vector<int> & vin, int sp, int ep, int sv, int ev);
void breadth_first_travel(queue<TreeNode*> & qu);
void depth_first_travel(stack<TreeNode *> & st);
void printBiT(TreeNode * root, const ModeBiT & printmode);
void testreConstructBinaryTree();
int Fibonacci(int n);
void testFibonacci();
int jumpFloor(int number);
void testjumpFloor();
int  NumberOf1(int n);
void testNumberOf1();
double Power(double base, int exponent);
void testPower();
void reOrderArray(vector<int> &array);
void testreOrderArray();
ListNode* Merge(ListNode* pHead1, ListNode* pHead2);
void testMerge();
bool HasSubtree(TreeNode* pRoot1, TreeNode* pRoot2);
bool isSubTree(TreeNode* pRoot1, TreeNode* pRoot2);
void Mirror(TreeNode *pRoot);
void testMirror();
vector<int> printMatrix(vector<vector<int> > matrix);
void testprintMatrix();

struct Stack{
	vector<int> vt;
	int top = -1;
};
static Stack st;
void push(int value);
void pop();
int top();
int min();
void testStack();
bool IsPopOrder(vector<int> pushV, vector<int> popV);
void testIsPopOrder();
vector<int> PrintFromTopToBottom(TreeNode* root);
void level_traversal(deque<TreeNode*> & dq, vector<int> & vti);
void testPrintFromTopToBottom();
bool VerifySquenceOfBST(vector<int> sequence);
bool verify_post_order_seq(vector<int> & seq, int s, int e);
void testVerifySquenceOfBST();
vector<vector<int> > FindPath(TreeNode* root, int expectNumber);
bool isLeaf(TreeNode * node);
void expectPath(stack<TreeNode *> & stk, vector<vector<int>> & allPath, vector<int> & currentPath, int & sumPath, int expectNumber);
void testFindPath();
struct RandomListNode {
	int label;
	struct RandomListNode *next, *random;
	RandomListNode(int x) :
		label(x), next(nullptr), random(nullptr) {
	}
};
RandomListNode* Clone(RandomListNode* pHead);
void testClone();
#endif