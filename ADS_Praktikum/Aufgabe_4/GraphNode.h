#pragma once
#include<vector>

class GraphNode
{
public:
	GraphNode();
	GraphNode(int key);
	~GraphNode();


	struct edge {

		GraphNode *node; //Destination node
		GraphNode *prev; //start node
		double value; //Edge Weight
		bool used = false;
		edge() {
			node = nullptr;
			value = 0;


		}
		edge(GraphNode * s,GraphNode * n, double val)
		{
			prev = s;
			node = n;
			value = val;

		}

		GraphNode* getNode() {
			return node;
		}

		void setUsed(bool a) {
			used = a;
		}
		bool operator ==(GraphNode::edge e) {
			if (node == e.node && value == e.value) {
				return true;
			}
			else return false;
		}

		bool operator<(const edge& comp) const
		{
			return value > comp.value;
		}

	};
	std::vector<edge> edges;

	int key = 0;
	bool visited = false;
	bool marked = false;
	double distance = 0;

	int getKey();
	void setKey(int tkey);

	bool getVisited();
	void setVisited(bool visited);

private:

};
