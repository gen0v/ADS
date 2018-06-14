#include "Graph.h"
#include<fstream>
#include<iostream>
#include<string>
#include<sstream>
#include<list>
#include<queue>

Graph::Graph()
{
}

Graph::~Graph()
{
}

void Graph::depthSearchRec(GraphNode* point) {
	point->visited = true;
	for (int i = 0; i < point->edges.size(); i++)
	{
		if (point->edges[i].getNode()->visited == false) {
			depthSearchRec(point->edges[i].getNode());
		}
	}

}

bool Graph::depthSearch(int number)
{
	//number is key to start
	//this must be recursive
	GraphNode* start = getNode(number);
	depthSearchRec(start);

	for (GraphNode* node : nodes) {
		if (node->visited == false) {
			std::cout << "Not all nodes were visited - depthSearch()\n";
			return false;
		}
	}
	std::cout << "All nodes were visited - depthSearch().\n";
	return true;
	//all nodes return to not visited?
}

bool Graph::breadthSearch()
{
	//function to see if every node can be reached
	//through iterative breadthsearch
	//pop first element
	if (nodes.empty() == true)return false;
	GraphNode* startNode = nodes[0];
	std::list<GraphNode*> myList;
	//start with startNode
	int count = 0;
	while (count < nodes.size()) {
		for (int i = 0; i < startNode->edges.size(); i++)
		{
			if (startNode->edges[i].getNode()->visited == false && startNode->edges[i].getNode()->marked == false) {
				myList.push_back(startNode->edges[i].getNode());
				startNode->edges[i].getNode()->marked = true;
			}
		}
		startNode->visited = true;
		if (myList.empty())break;
		startNode = myList.front();
		myList.pop_front();
		count++;
	}
	for (GraphNode* node : nodes) {
		if (node->visited == false) {
			std::cout << "Not all nodes were visited - breadthSearch()\n";
			return false;
		}
	}
	std::cout << "All nodes were visited - breadthSearch().\n";
	return true;
	//all nodes return to not visited?
}

double Graph::prim(int number)
{
	double weight = 0;
	//best neighbor
	std::list<GraphNode*> myList;
	std::list<GraphNode::edge> edgeList;
	
	std::list<GraphNode::edge>::iterator position;
	std::list<GraphNode::edge>::iterator it;
	std::list<GraphNode::edge>::reverse_iterator rit;

	GraphNode* start = getNode(number);
	GraphNode* node = start;

	//node is visited now
	node->visited = true;
	while (!allNodesVisited()) {
		for (int i = 0; i < node->edges.size(); i++)
		{
			//push them in order
			if (edgeList.size() > 0) {
				position = edgeList.begin();
				for (rit = edgeList.rbegin(); rit != edgeList.rend(); rit++)
				{

					//std::cout << "Adding Edges ...\n";
					if (node->edges[i].getNode()->visited == false) {
						if (node->edges[i].value < (*rit).value) {
							for (it = edgeList.begin(); it != edgeList.end(); it++) {
								if (node->edges[i].value < (*it).value) {
									//test from beginning
									//std::cout << node->edges[i].value << "<" << (*it).value << std::endl;
									edgeList.insert(it, node->edges[i]);
									break;
								}
							}
							//it++;
							/*
							it = rit.base();
							it--;
							std::cout << "It value " << (*it).value<<std::endl;
							std::cout << node->edges[i].value <<"<"<< (*it).value<<std::endl;
							edgeList.insert(it, node->edges[i]);
							*/
							break;

						}
						else if (node->edges[i].value > (*rit).value) {
							//std::cout << node->edges[i].value << ">" << (*rit).value << std::endl;
							edgeList.insert(rit.base(), node->edges[i]);
							break;
						}
					}
				}
			}
			else edgeList.push_back(node->edges[i]);
			//list of all edges
		}
		//edgelist with all edges is sorted
		//take lightest edge


		int size = edgeList.size();
		for (int j = 0; j < size; j++)
		{
			if (edgeList.front().getNode()->visited == false) {
				std::cout << "TAKING EDGE " << edgeList.front().value << "\n";
				weight = weight + edgeList.front().value;
				node = edgeList.front().getNode();
				edgeList.front().getNode()->setVisited(true);
				edgeList.pop_front();
				break;
			}
			else edgeList.pop_front();
			//std::cout << "WEIGHT "<<edgeList.front().value<<"\n";
			//edgeList.pop_front();
		}

	//already circle
		if (edgeList.size() == 0)break;
	}

	return weight;
}

double Graph::kruskal()
{
	std::vector<int> marked(this->nodes.size());
	std::priority_queue<GraphNode::edge> pq;
	std::vector<GraphNode::edge> e;
	for (int i = 0; i < nodes.size(); i++)
	{
		for (int j = 0; j < nodes[i]->edges.size(); j++)
		{
			e.push_back(nodes[i]->edges[j]);
		}
	}

	for (int i = 0; i < e.size(); i++) pq.push(e[i]);
	for (int i = 0; i < nodes.size(); i++) marked[i] = i;
	double sum = 0;
	while (!pq.empty()) {
		GraphNode::edge e = pq.top();

		pq.pop();
		int key = e.node->key;
		int w = e.prev->key;

		if (marked[key] != marked[w]) {
			sum += e.value;
			int from = marked[e.prev->key];

			for (int i = 0; i < marked.size(); i++) {
				if (marked[i] == from)
					marked[i] = marked[key];
			}
			std::cout << e.prev->key << "->" << e.node->key << ": " << e.value << std::endl;
		}
	}
	return sum;
}

double Graph::kruskalver2()
{

	//all edge into vector
	double weight = 0;
	double tempweight = 0;
	bool found = false;
	//best option

	std::list<GraphNode::edge> edgeList;
	std::list<GraphNode*> nodeList;

	GraphNode* reverse;

	std::list<GraphNode::edge>::iterator position;
	std::list<GraphNode::edge>::iterator it;
	std::list<GraphNode::edge>::reverse_iterator rit;

	std::list<GraphNode*>::iterator git;
	std::list<GraphNode*>::reverse_iterator grit;

	//node is visited now
	for (GraphNode* node : nodes) {
		//node->visited = true;

		for (int i = 0; i < node->edges.size(); i++)
		{
			//push them in order
			if (edgeList.size() > 0) {
				//position = edgeList.begin();
				for (rit = edgeList.rbegin(), grit = nodeList.rbegin(); rit != edgeList.rend(); rit++, grit++)
				{

					//std::cout << "Adding Edges ...\n";
					if (node->edges[i].getNode()->visited == false) {
						if (node->edges[i].value < (*rit).value) {
							for (it = edgeList.begin(), git = nodeList.begin(); it != edgeList.end(); it++, git++) {
								if (node->edges[i].value < (*it).value) {
									//test from beginning
									edgeList.insert(it, node->edges[i]);
									nodeList.insert(git, node);
									node->edges[i].getNode()->marked = true;
									break;
								}
							}

							break;

						}
						else if (node->edges[i].value > (*rit).value) {
							//std::cout << node->edges[i].value << ">" << (*rit).value << std::endl;
							edgeList.insert(rit.base(), node->edges[i]);
							nodeList.insert(grit.base(), node);
							node->edges[i].getNode()->marked = true;
							break;
						}
					}
				}
			}
			else {
				edgeList.push_back(node->edges[i]);
				nodeList.push_back(node);
			}
			//list of all edges
		}
	}
	while (true) {
		//test if one of the edges of front edges is already used
		for (int x = 0; x < edgeList.front().getNode()->edges.size(); x++)
		{
			if (edgeList.front().getNode()->edges[x].getNode()->visited == true) {
				nodeList.pop_front();
				edgeList.pop_front();
			}
		}
		//take lightest edge and add weight and mark edge as used two ways
		if (edgeList.front().used == true){// || edgeList.front().getNode()->visited == true) {
			nodeList.pop_front();
			edgeList.pop_front();
		}
		else {
			std::cout << "Adding weight " << edgeList.front().value << "\n";
			weight = weight + edgeList.front().value;
			tempweight = edgeList.front().value;
			
			edgeList.front().setUsed(true);
			//edgeList.front().setUsed(true);
			//weight added

			//backway needs to be marked as well
			//edgeList.front().getNode() ~ endnode
			//search for startnode
			for (int h = 0; h < edgeList.front().getNode()->edges.size(); h++)
			{
				found = false;
				if (edgeList.front().used == true) {
					nodeList.pop_front();
					edgeList.pop_front();
				}
				if (edgeList.front().getNode()->edges[h].value == tempweight
					&& edgeList.front().getNode()->edges[h].used == false
					&& edgeList.front().getNode()->edges[h].getNode() == nodeList.front())
				{//
					//edgeList.front().getNode()->edges[h].setUsed(true);
					//this edge in edgelist
					for (it = edgeList.begin(); it != edgeList.end(); it++) {
						{
							if ((*it) == edgeList.front().getNode()->edges[h] && (*it).used == false)
							{
								std::cout << "set used node " << (*it).getNode()->key << " with weight " << (*it).value << std::endl;
								(*it).setUsed(true);
								(*it).getNode()->setVisited(true);
								//startnode found
								found = true;
								break;
							}
						}
					}

				}

				if (found)break;
			}
			//edgeList.front().used = true;
			edgeList.pop_front();
			nodeList.pop_front();
			if (edgeList.size() == 0)break;

			//and delete edge from edgelist


		}

	}
	return weight;
}

double Graph::kruskalver3() {
	std::list<sedge> visitededges;
	std::list<sedge> sedges;
	double weight = 0;
	double tempweight = 0;
	bool found = false;
	int counter = 0;
	//best option
	std::list<GraphNode::edge> edgeList;
	std::list<GraphNode::edge>::iterator it;
	std::list<GraphNode::edge>::reverse_iterator rit;

	std::list<sedge>::iterator git;
	std::list<sedge>::reverse_iterator grit;
	for (GraphNode* node : nodes) {
		//node->visited = true;
		for (int i = 0; i < node->edges.size(); i++)
		{
			//push them in order
			if (edgeList.size() > 0) {
				//position = edgeList.begin();
				for (rit = edgeList.rbegin(), grit = sedges.rbegin(); rit != edgeList.rend(); rit++, grit++)
				{

					//std::cout << "Adding Edges ...\n";
					if (node->edges[i].getNode()->visited == false) {
						if (node->edges[i].value < (*rit).value) {
							for (it = edgeList.begin(), git = sedges.begin(); it != edgeList.end(); it++, git++) {
								if (node->edges[i].value < (*it).value) {
									//test from beginning
									edgeList.insert(it, node->edges[i]);
									sedges.insert(git, sedge(node, node->edges[i].value, node->edges[i].getNode()));
									break;
								}
							}

							break;

						}
						else if (node->edges[i].value > (*rit).value) {
							//std::cout << node->edges[i].value << ">" << (*rit).value << std::endl;
							edgeList.insert(rit.base(), node->edges[i]);
							sedges.insert(grit.base(), sedge(node, node->edges[i].value, node->edges[i].getNode()));
							node->edges[i].getNode()->marked = true;
							break;
						}
					}
				}
			}
			else {
				edgeList.push_back(node->edges[i]);

				sedges.push_back(sedge(node, node->edges[i].value, node->edges[i].getNode()));
			}
			//list of all edges
		}
	}
	//saved into vector
	while (!allNodesVisited()) {
		for (int v = 0; v < sedges.size(); v++)
		{
			while (counter < visitededges.size()) {
				/*for (Graph::sedge now : visitededges) {
					if (sedges.front().start == now.start) {
						visitededges.push_back(sedges.front());
						sedges.front().start->setVisited(true);
						sedges.front().end->setVisited(true);
						sedges.pop_front();
						counter = 0;
					}*/
				if (sedges.front().start->visited == true && sedges.front().end->visited == true) {
					visitededges.push_back(sedges.front());
					sedges.front().start->setVisited(true);
					sedges.front().end->setVisited(true);
					sedges.pop_front();
				}
					else counter++;
				}
			

			


			std::cout << "Adding weight " << sedges.front().value << "\n";
			sedge t = sedges.front();
			weight = weight + sedges.front().value;
			
			//delete this and the reverse
			git = sedges.begin();
			git++;
			for (; git != sedges.end(); git++) {
				{
					//find reverse
					sedge temp(sedges.front().end, sedges.front().value, sedges.front().start);
					if ((*git) == temp) {
						std::cout << "Temp .. \n";
						temp.print();
						std::cout << "Erasing .. \n";
						(*git).print();
						visitededges.push_back((*git));
						(*git).start->setVisited(true);
						(*git).end->setVisited(true);
						sedges.erase(git);
						break;
					}
				}
			}
			visitededges.push_back(sedges.front());
			sedges.front().start->setVisited(true);
			sedges.front().end->setVisited(true);
			sedges.pop_front();
			//deleted
		}
	}
	return weight;
}

double Graph::kruskalver4()
{
	std::list<sedge> visitededges;
	std::list<sedge> sedges;
	double weight = 0;
	double tempweight = 0;
	bool found = false;
	int counter = 0;
	//best option
	int test[20] = { 0 };

	std::list<GraphNode::edge> edgeList;
	std::list<GraphNode::edge>::iterator it;
	std::list<GraphNode::edge>::reverse_iterator rit;

	std::list<sedge>::iterator git;
	std::list<sedge>::reverse_iterator grit;
	for (GraphNode* node : nodes) {
		//node->visited = true;
		for (int i = 0; i < node->edges.size(); i++)
		{
			//push them in order
			if (edgeList.size() > 0) {
				//position = edgeList.begin();
				for (rit = edgeList.rbegin(), grit = sedges.rbegin(); rit != edgeList.rend(); rit++, grit++)
				{

					//std::cout << "Adding Edges ...\n";
					if (node->edges[i].getNode()->visited == false) {
						if (node->edges[i].value < (*rit).value) {
							for (it = edgeList.begin(), git = sedges.begin(); it != edgeList.end(); it++, git++) {
								if (node->edges[i].value < (*it).value) {
									//test from beginning
									edgeList.insert(it, node->edges[i]);
									sedges.insert(git, sedge(node, node->edges[i].value, node->edges[i].getNode()));
									break;
								}
							}

							break;

						}
						else if (node->edges[i].value > (*rit).value) {
							//std::cout << node->edges[i].value << ">" << (*rit).value << std::endl;
							edgeList.insert(rit.base(), node->edges[i]);
							sedges.insert(grit.base(), sedge(node, node->edges[i].value, node->edges[i].getNode()));
							node->edges[i].getNode()->marked = true;
							break;
						}
					}
				}
			}
			else {
				edgeList.push_back(node->edges[i]);

				sedges.push_back(sedge(node, node->edges[i].value, node->edges[i].getNode()));
			}
			//list of all edges
		}
	}
	//saved into vector
	int sets[10][10];
	std::pair<int, int> eg;




	while (!allNodesVisited()) {


	}
	return weight;
}


bool Graph::testCirclestd(std::vector<sedge> sedges)
{
	
	return false;
}
/*
bool Graph::init(std::string path)
{
	std::ifstream file;
	file.open(path, std::ios_base::in);

	if (!file) {
		std::cout << "Cannot open file!\n";
		return false;
	}
	else
	{
		std::string line;
		std::getline(file, line);
		std::istringstream iss(line);
		//read first line
		iss >> numNodes;
		//set all nodes
		for (int i = 0; i < numNodes; i++)
		{
			GraphNode* newNode = new GraphNode(i);
			nodes.push_back(newNode);
		}
		//set all edges
		while (std::getline(file, line))
		{
			std::istringstream edges(line);
			int from, val, to;
			if (!(edges >> from >> to >> val)){
			break;//error with the format
			}
			GraphNode* currentNode = getNode(from);
			GraphNode* currentNextToNode = getNode(to);
			//One Way
			GraphNode::edge edge(currentNextToNode, val);
			currentNode->edges.push_back(edge);
			//Back Way
			GraphNode::edge backEdge(currentNode, val);
			currentNextToNode->edges.push_back(backEdge);
		}

		return true;
	}
	return false;
}
*/
bool Graph::init2(std::string path)
{
	{
		std::ifstream file;
		file.open(path, std::ios_base::in);

		if (!file)
		{
			std::cout << "Cannot open file." << std::endl;
			return false;
		}
		else
		{
			std::cout << "Start reading" << std::endl;

			std::string line;
			std::getline(file, line);
			std::istringstream iss(line);

			std::cout << "Insert number Nodes" << std::endl;
			iss >> numNodes;

			std::cout << "Create all Nodes" << std::endl;
			//Alle Knoten anlegen
			for (int i = 0; i < numNodes; i++)
			{
				GraphNode* currentNode = new GraphNode(i);
				nodes.push_back(currentNode);
			}

			std::cout << "Start creating edges" << std::endl;
			while (std::getline(file, line))
			{
				std::istringstream edges(line);
				int from, value, to;
				if (!(edges >> from >> to >> value)) { break; } // error

				std::cout << "From: " << from << " To: " << to << " Value: " << value << std::endl;
				GraphNode* currentNode = getNode(from);
				GraphNode* currentNeighbour = getNode(to);
				//ONE WAY
				GraphNode::edge edge(currentNode, currentNeighbour, value);
				currentNode->edges.push_back(edge);


				//BACKWAY
				GraphNode::edge backEdge(currentNeighbour, currentNode, value);
				currentNeighbour->edges.push_back(backEdge);
			}
			return true;
		}

		return false;
	}

}

GraphNode* Graph::getNode(int key)
{
	//GraphNode* current;
	for (int i = 0; i < numNodes; i++)
	{
		if (nodes[i]->getKey() == key) {
			return nodes[i];
		}
	}

	return nullptr;
}

void Graph::print()
{
	if (nodes.empty() == true) {
		std::cout << "ERROR PRINTING !!\n";
		return;
	}

	for (int i = 0; i < numNodes; i++)
	{
		GraphNode* curNode = nodes[i];
		std::cout << "Current Node: " << curNode->getKey() << " ";
		for (int j = 0; j < curNode->edges.size(); j++)
		{
			if (curNode->edges.empty() == false) {
				GraphNode::edge curEdge = curNode->edges[j];
				std::cout << " ===> " << curEdge.node->getKey() << "(" << curEdge.value << ")";
			}
		}
		std::cout << std::endl;
	}
}

bool Graph::allNodesVisited() {
	for (GraphNode* node : nodes) {
		if (node->visited == false) {
			//std::cout << "Not all nodes were visited - breadthSearch()\n";
			return false;
		}
	}
	//std::cout << "All nodes were visited - breadthSearch().\n";
	return true;
}