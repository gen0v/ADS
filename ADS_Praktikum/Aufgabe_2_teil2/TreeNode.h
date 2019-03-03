#pragma once
#include <string>

class TreeNode
{
	friend class Tree;

public:
	TreeNode();
	TreeNode(std::string name,int age,double income, int plz, int nodeID);
	~TreeNode();

	//Getter
	std::string getName() { return this->name; }
	int getAge() { return this->age; }
	double getIncome() { return this->income; }
	int getPlz () { return this->plz; }
	//Setter
	void setName(std::string name) { this->name = name; }
	void setAge(int age) { this->age = age; }
	void setIncome(double income) { this->income = income; }
	void setPlz(int plz) { this->plz = plz; }
	//functions
	void printData();


private:
	int nodePosID;
	int nodeID;
	std::string name;
	int age;
	double income;
	int plz;

	TreeNode* left = nullptr;
	TreeNode* right = nullptr;
};


