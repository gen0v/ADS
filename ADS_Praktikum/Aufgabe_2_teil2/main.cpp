#include <iostream>
#include "Tree.h"
/*	Author: Eugen Burikov	*/

void test_tree(Tree* tree) {
	
	tree->add("Mustermann", 1, 1000, 1);
	tree->add("Ritter", 1, 2000, 1);
	tree->add("Kaiser", 1, 3000, 1);
	tree->add("Hans", 1, 500, 1);
	tree->add("Schmitt", 1, 500, 2);
	tree->add("Schmitz", 1, 400, 2);
	
	//tree->del(403);
	//tree->del(502);
	/*
	tree->readCSV();
	tree->del(77099);
	tree->del(77153);
	*/
}

void print_menu() {
	std::cout << "" << std::endl;
	std::cout << "0) Exit" << std::endl;
	std::cout << "1) Insert dataset, manually" << std::endl;
	std::cout << "2) Insert dataset, (CSV) File" << std::endl;
	std::cout << "3) Delete dataset" << std::endl;
	std::cout << "4) Search" << std::endl;
	std::cout << "5) Show datastructure" << std::endl;
	std::cout << "6) Test Tree" << std::endl;
	std::cout << "=>>";
}

int main() {
	Tree* tree = new Tree();
	int input = 10;
	char in = 'a';
	
	std::string name = "";
	int id = 0;
	int age = 0;
	int plz = 0;
	double income = 0;

	std::string search = "";
	
	int delpos = 0;

	


	std::cout << "+++++++++++++++++++++++++" << std::endl;
	std::cout << "________binary_tree______" << std::endl;
	std::cout << "+++++++++++++++++++++++++" << std::endl;

	while (input != 0) {
		print_menu();
		std::cin >> input;
		if (!std::cin.good()) {
			std::cin.clear(); //clear bad input flag
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); //discard input
			input = 10;
		}
		switch (input)
		{
		case 0:
			break;
		case 1:
			std::cout << "Name ?> ";
			std::cin.ignore();
			std::getline(std::cin, name);
			std::cout << "Age ?> ";
			std::cin >> age;
			std::cout << "Income ?> ";
			std::cin >> income;
			std::cout << "PLZ ?> ";
			std::cin >> plz;
			tree->add(name, age, income, plz);
			std::cout << "+ dataset added!";
			break;
		case 2:
			while (in != 'y' && in != 'n') {
				std::cout << "Do you want to import the file 'ExportZielanalyse.csv' (y\n) > ";
				std::cin >> in;
			}
			if (in == 'y')tree->readCSV();
			break;
		case 3:
			std::cout << "+ Please enter the dataset which you want to delete\n";
			std::cout << "Pos ?> ";
			std::cin >> delpos;
			if (!std::cin.good()) {
				std::cin.clear(); //clear bad input flag
				std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); //discard input
				delpos = 0;
				std::cout << "Not a PositionID ??? Starting program with ID = 0 ";
			}
			tree->del(delpos);
			break;
		case 4:
			std::cout << "+ Please enter the dataset which you want to search\n";
			std::cout << "Name ?> ";
			std::cin.ignore();
			std::getline(std::cin, search);
			tree->search(search);
			break;
		case 5:
			tree->print();
			break;
		case 6:
			test_tree(tree);
			break;
		default:
			std::cout << "NOT DEFINED INPUT....\n";
			break;
		}

	}

	system("PAUSE");
	return 0;
}

