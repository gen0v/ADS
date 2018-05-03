#include "Tree.h"
#include <iostream>
#include <string>
#include <fstream>
Tree::Tree()
{
}

Tree::~Tree()
{
}
/*
	Create new TreeNode and then put it into the right position
*/
void Tree::add(std::string name, int age, double income, int plz) {
	nodeID++;
	TreeNode* newNode = new TreeNode(name, age, income, plz, nodeID);
	put(newNode);
}

/*
	position the new Node to the right position
*/
void Tree::put(TreeNode* node) {
	//Start at root
	if (root == nullptr) {
		root = node;
		return;
	}
	TreeNode* next_temp = root;
	//Search for next empty pointer
	while (next_temp != nullptr) {
		if (next_temp->nodePosID > node->nodePosID) {
			//if smaller then go left on tree
			if (next_temp->left == nullptr) {
				next_temp->left = node;
				return;
			}
			next_temp = next_temp->left;
		}
		else if (next_temp->nodePosID < node->nodePosID) {
			//if bigger then go right on tree
			if (next_temp->right == nullptr) {
				next_temp->right = node;
				return;
			}
			next_temp = next_temp->right;
		}
		else
		{
			next_temp = next_temp->left;
		}
		
	}
		//Found the empty spot and put it in now
		//next_temp = node;
}

void Tree::print() {
	if (root != nullptr) {
		std::cout << "ID" << " | " << "Name\t" << "| " << "Alter" << " | " << "Einkommen" << " | " << "PLZ\t" << "|\t" << "Pos" << std::endl;
		std::cout << "-----------------------------------------------------------------------------------------------------------------" << std::endl;
		print_rec(root);
	}
}

void Tree::print_rec(TreeNode* index) {
	//TO DO 

	//if (index == nullptr)return;
	//pre order -> recursive
	//std::cout << "++" << index->nodeID << "+" << index->name<<"+"<< index->age<< "+" <<index->income << "+" << std::endl;
	std::cout << index->nodeID << " | " << index->name << "\t" << " | " << index->age << " | " << index->income << "\t" << "|\t" << index->plz << "\t" << "|\t" << index->nodePosID << std::endl;
	//go left till you cant
	if (index->left != nullptr) print_rec(index->left);
	//then go right and restart
	if (index->right != nullptr) print_rec(index->right);
}

bool Tree::search(std::string name) {
	if (root != nullptr) {
		std::cout << "-source-" << std::endl;
		search_rec(root,name);
		return true;
	}
}
void Tree::search_rec(TreeNode* index, std::string name) {
	//TO DO 

	//if (index == nullptr)return;
	//pre order -> recursive
	//std::cout << "++" << index->nodeID << "+" << index->name<<"+"<< index->age<< "+" <<index->income << "+" << std::endl;
	//std::cout << index->nodeID << " | " << index->name << "\t" << " | " << index->age << " | " << index->income << "\t" << "|\t" << index->plz << "\t" << "|\t" << index->nodePosID << std::endl;
	if (index->name == name) {
		std::cout << "NodeID: " << index->nodeID;
		std::cout << ", Name:" << index->name;
		std::cout << ", Age:" << index->age;
		std::cout << ", Income:" << index->income;
		std::cout << ", PLZ:" << index->plz;
		std::cout << ", PosID" << index->nodePosID;
		std::cout << std::endl;
	}
	//go left till you cant
	if (index->left != nullptr) search_rec(index->left,name);
	//then go right and restart
	if (index->right != nullptr) search_rec(index->right,name);
}

bool Tree::del(int pos) {

	if (root == nullptr) {
		std::cout << "---tree ist empty---\n";
		return false;
	}

	//go through tree and find the pos
	//save the prev tree node
	TreeNode* nextdel = root;
	TreeNode* prevdel = nextdel;
	TreeNode* temp;
	TreeNode* save;
	//-------------------------
	while (nextdel->nodePosID != pos) {
		if (nextdel->nodePosID > pos && nextdel->left != nullptr) {
			prevdel = nextdel;
			nextdel = nextdel->left;
		}else if (nextdel->nodePosID < pos && nextdel->right != nullptr) {
			prevdel = nextdel;
			nextdel = nextdel->right;
		}
		else {
			//not found
			std::cout << "NOT FOUND !!!\n";
			return false;
		}
	}
	//found and test the cases now
	//del is root
	if (nextdel == root && nextdel->right == nullptr) {
		//no right subtree
		temp = root->left;
		delete root;
		root = temp;
		return true;
	}
	else if (nextdel == root) {
		//root is the node
		temp = nextdel;
		temp = temp->right;
		if (temp->left == nullptr) {
			//just once to the right
			nextdel->right = nullptr;
		}
		while (temp->left != nullptr) {
			prevdel = temp;
			temp = temp->left;
		}
		setNullPtr(prevdel, temp);
		//found temp for building tree
		save = nextdel;
		temp->left = save->left;
		if(temp->right == nullptr)temp->right = save->right;
		delete root;
		root = temp;
	}
	else if (nextdel->left == nullptr && nextdel->right == nullptr) {
		//the node is a leaf 
		setNullPtr(prevdel, nextdel);
		delete nextdel;
	}
	else if (nextdel->left == nullptr || nextdel->right == nullptr) {
		//the node is a leaf with one child
		if (nextdel->left == nullptr) {
			if (prevdel->left == nextdel)prevdel->left = nextdel->right;
			else prevdel->right = nextdel->right;
			delete nextdel;

		}
		else {
			if (prevdel->left == nextdel)prevdel->left = nextdel->left;
			else prevdel->right = nextdel->left;
			delete nextdel;
		}
	}
	else {
		//node is leaf with two children
		temp = nextdel;
		temp = temp->right;
		if (temp->left == nullptr) {
			//just once to the right
			nextdel->right = nullptr;
		}
		while (temp->left != nullptr) { 
			temp = temp->left;
		}
		//found temp for building tree
		save = nextdel;
		temp->left = save->left;
		temp->right = temp->right;
		if (prevdel->left == nextdel)prevdel->left = temp;
		else prevdel->right = temp;
		delete nextdel;
		

	}
	return true;

}
void Tree::del_rec(TreeNode* index, int pos) {
	//if found delete and repair tree
	if (index->nodePosID == pos) {

	}
	//go left till you cant
	if (index->left != nullptr) del_rec(index->left, pos);
	//then go right and restart
	if (index->right != nullptr) del_rec(index->right, pos);
}
void Tree::setNullPtr(TreeNode* prev, TreeNode* next) {
	if (prev->left == next) {
		prev->left = nullptr;
	}else if (prev->right == next) {
		prev->right = nullptr;
	}else {
		//std::cout << "not found\n";
	}
	//std::cout << "TEST\n";
}

void Tree::readCSV() {
	std::ifstream read,count;
	int first, second, third;
	std::string name;
	int age, plz;
	double income;
	int col = 0;
	read.open("ExportZielanalyse.csv", std::ios::in);
	count.open("ExportZielanalyse.csv", std::ios::in);
	if (read) {
		//Datei bis Ende einlesen und bei ';' strings trennen 
		std::string s = "";
		while (std::getline(count, s, '\n')) {
			col++;
		}
		count.close();
		for (int i = 0; i < col; i++)
		{
			std::getline(read, s, '\n');
			first = s.find_first_of(";");
			second = s.find(';', first+1);
			third = s.find(";", second+1);
			/**
			std::cout << s.substr(0, first) << std::endl;
			std::cout << s.substr(first+1, second-first-1) << std::endl;
			std::cout << s.substr(second + 1, third - second - 1) << std::endl;
			std::cout << s.substr(third+1, s.length()) << std::endl;
			*/
			name = s.substr(0, first);
			age = std::stoi(s.substr(first + 1, second - first - 1));
			income = std::stod(s.substr(second + 1, third - second - 1));
			plz = std::stoi(s.substr(third + 1, s.length()));
			nodeID++;
			TreeNode* node = new TreeNode(name, age, income, plz, nodeID);
			put(node);
		}

		read.close();
		
	}
	else {
		std::cerr << "Fehler beim Lesen!" << std::endl;
	}

}