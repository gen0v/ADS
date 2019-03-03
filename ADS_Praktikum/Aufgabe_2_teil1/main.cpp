#include <iostream>
#include "Ringnode.h"
#include "Ringpuffer.h"

void test_puffer(Ringpuffer* puffer) {
	std::cout << "+++ THIS IS A TEST OF THE PROGRAMM +++" << std::endl;
	puffer->addNode("A", "dataA");
	puffer->addNode("B", "dataB");
	puffer->addNode("C", "dataC");
	puffer->addNode("D", "dataD");
	puffer->addNode("E", "dataE");
	puffer->addNode("F", "dataF");
	puffer->addNode("G", "dataG");
}
void print_menu() {
	std::cout << "" << std::endl;
	std::cout << "0) Exit" << std::endl;
	std::cout << "1) Insert backup" << std::endl;
	std::cout << "2) Search backup" << std::endl;
	std::cout << "3) Print all backups" << std::endl;
	std::cout << "4) Test Input A-G" << std::endl;
	std::cout << "=>>";
}

int main() {

	int input = 10;
	char rep = 'y';
	std::string desc = "";
	std::string data = "";
	std::string search = "";
	Ringpuffer* puffer = new Ringpuffer();
	
	std::cout << "+++++++++++++++++++++++++" << std::endl;
	std::cout << "________Ringpuffer_______" << std::endl;
	std::cout << "+++++++++++++++++++++++++" << std::endl;

	while (input != 0) {
		print_menu();
		std::cin >> input;
		if (!std::cin.good()) {
			input = 1;
		}
		switch (input)
		{
		case 0:
			break;
		case 1:
			std::cout << "Description =>>  ";
			std::cin.ignore();
			std::getline(std::cin, desc);
			std::cout << "Data =>>  ";
			//std::cin.ignore();
			std::getline(std::cin, data);
			puffer->addNode(desc, data);
			std::cout << "++ Backup added ++" << std::endl;
			break;
		case 2:
			std::cout << "Search for data, please enter..." << std::endl;
			std::cin.ignore();
			std::getline(std::cin, search);
			//if(puffer->search(search) == true)std::cout << "++ Backup found ++" << std::endl;
			//else std::cout << "-- Backup not found --" << std::endl;
			puffer->search(search);
			break;
		case 3:
			puffer->print();
			break;
		case 4:
			test_puffer(puffer);
			break;
		default:
			std::cout << "NOT DEFINED INPUT....\n";
			break;
		}
		/*
		std::cout << "Back to menu?('n' for exit)" << std::endl;
		std::cin >> rep;
		std::cout << "-------------------------" << std::endl;
		std::cout << std::endl;
		*/
		//std::cin.ignore();
	}
	//puffer->print_all();
	puffer->print();
	system("PAUSE");
	return 0;
}

