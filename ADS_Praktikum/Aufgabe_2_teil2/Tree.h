#pragma once
#include "TreeNode.h"
#include <string>
class Tree
{
	friend class TreeNode;

public:
	
	Tree(TreeNode* node) :root(node) {};
	Tree();
	~Tree();
	void add(std::string name, int age, double income, int plz);

	bool del(int pos);
	void del_rec(TreeNode* index, int pos);

	void print();
	void print_rec(TreeNode* node);
	bool search(std::string name);
	void search_rec(TreeNode* index, std::string name);

	void put(TreeNode* node);
	void setNullPtr(TreeNode* prev, TreeNode* next);

	void readCSV();

private:
	TreeNode* root = nullptr;
	int nodeID = -1;

};
