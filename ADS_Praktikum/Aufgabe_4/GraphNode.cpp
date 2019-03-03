#include "GraphNode.h"

GraphNode::GraphNode()
{
}
GraphNode::GraphNode(int key)
{
	this->key = key;
}

GraphNode::~GraphNode()
{
}

int GraphNode::getKey()
{
	return key;
}

void GraphNode::setKey(int tkey)
{
	this->key = tkey;
}

bool GraphNode::getVisited()
{
	return visited;
}

void GraphNode::setVisited(bool visited)
{
	this->visited = visited;
}
