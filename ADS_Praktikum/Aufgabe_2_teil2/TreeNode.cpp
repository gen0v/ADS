#include "TreeNode.h"
#include <string>


TreeNode::TreeNode()
{
}

TreeNode::~TreeNode()
{
}

TreeNode::TreeNode(std::string name, int age, double income, int plz, int nodeID) {
	this->name = name;
	this->age = age;
	this->income = income;
	this->plz = plz;
	this->nodeID = nodeID;
	this->nodePosID = (double)age + (double)plz + income;
}