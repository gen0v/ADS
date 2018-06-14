#pragma once
#include<iostream>
#include <vector>
#include "GraphNode.h"
#include<list>
class Graph
{
public:
	Graph();
	~Graph();
	struct sedge {

		GraphNode *start;
		GraphNode *end; //Destination node
		double value; //Edge Weight
		bool used = false;
		sedge() {
			start = nullptr;
			end = nullptr;
			value = 0;
		}
		sedge(GraphNode * s, double val, GraphNode * n)
		{
			start = s;
			end = n;
			value = val;

		}

		bool operator ==(Graph::sedge e) {
			if (start == e.start && end == e.end && value == e.value) {
				return true;
			}
			else return false;
		}
		void print() {
			std::cout << "Start :" << start->key;
			std::cout << " |Value :" << value;
			std::cout << " |End :" << end->key << std::endl;
		}

	};
	std::list<sedge> sedges;
	std::list<sedge> visitededges;

	int numNodes = 0;
	bool weighted = false;
	bool directed = false;
	std::vector<GraphNode*> nodes;

	bool depthSearch(int number);
	bool breadthSearch();
	double prim(int number);
	double kruskal();
	double kruskalver2();
	double kruskalver3();
	double kruskalver4();


	bool testCirclestd(std::vector<sedge> sedges);

	//bool init(std::string path);
	bool init2(std::string path);
	GraphNode* getNode(int key);

	void depthSearchRec(GraphNode* point);

	void print();

	bool allNodesVisited();

private:

};

