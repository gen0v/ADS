#pragma once
#include "Ringnode.h"
#include <string>

class Ringpuffer
{
	
private:
	Ringnode * anker;



public:
	Ringpuffer();
	Ringpuffer(std::string desc, std::string data);
	~Ringpuffer();

	void addNode(std::string desc, std::string data);
	bool search(std::string data);
	void print_all();
	void print_rec(Ringnode * n);
	void print();
	void increaseAge();
	bool is_ring_empty();

private:

};


