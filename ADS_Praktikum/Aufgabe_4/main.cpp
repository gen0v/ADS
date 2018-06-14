#include <iostream>
#include "Graph.h"

int main() {

	int input = 9;
	int number = 0;
	Graph* graph = new Graph();
	double result = 0;

	//while (input < 0 || input > 6) {
	while (true) {
		std::cout << "--Menu--\n";
		std::cout << "0:Graph einlesen\n";
		std::cout << "1:Tiefensuche\n";
		std::cout << "2:Breitensuche\n";
		std::cout << "3:Prim\n";
		std::cout << "4:Kruskal\n";
		std::cout << "5:Graph ausgeben\n";
		std::cout << "6:Programm beenden\n\n";
		std::cin >> input;
		if (input < 0 || input > 6) {
			std::cout << "WRONG INPUT !\n";
		}
		else {
		}
		switch (input)
		{
		case 0:
			graph = new Graph();
			std::cout << "Welcher Graph soll eingelesen werden.\n Graph 1,2 oder 3.\n";
			std::cin >> input;
			if (input < 1 || input > 3) {
				std::cout << "WRONG INPUT -> INPUT WILL BE 1!\n";
				input = 1;
			}
			if (input == 1) graph->init2("graph1.txt");
			else if (input == 2)graph->init2("graph2.txt");
			else graph->init2("graph3.txt");
			break;
		case 1:
			std::cout << "Bitte Startknoten eingeben..\n";
			std::cin >> number;
			std::cout << "Tiefensuche wird ausgefuehrt...\n";
			graph->depthSearch(number);
			break;
		case 2:
			std::cout << "Breitensuche wird ausgefuehrt...\n";
			graph->breadthSearch();
			break;
		case 3:
			std::cout << "Bitte Startknoten eingeben..\n";
			std::cin >> number;
			std::cout << "Prim wird ausgefuehrt...\n";
			result = graph->prim(number);
			std::cout << "Das Gewicht ab Knoten " << number << " ist " << result << std::endl;
			break;
		case 4:
			std::cout << "Kruskal wird ausgefuehrt...\n";
			result = graph->kruskal();
			std::cout << "Das Gewicht ist " << result << std::endl;
			break;
		case 5:
			graph->print();
			break;
		case 6:
			std::cout << "Programm wird beendet...\n";
			system("PAUSE");
			exit(0);
			break;
		default:
			break;
		}
	}


	system("PAUSE");
	return 0;
}