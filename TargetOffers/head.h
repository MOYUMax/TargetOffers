#ifndef _HEAD_H
#define _HEAD_H

#include <iostream>
#include <string>
#include <set>
#include <vector>
#include <algorithm>
#include <stack>

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
 enum ModeBiT{ PreOrder, InOrder, PostOrder };
 TreeNode* reConstructBinaryTree(vector<int> pre, vector<int> vin);
 void createBiT(TreeNode * & R, const vector<int> & pre, const vector<int> & vin, int sp, int ep, int sv, int ev);
 void printBiT(TreeNode * root, const ModeBiT & printmode);
 void testreConstructBinaryTree();


 int Fibonacci(int n);
 void testFibonacci();

#endif