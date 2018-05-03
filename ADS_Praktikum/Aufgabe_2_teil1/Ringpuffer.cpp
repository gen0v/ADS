#include "Ringpuffer.h"
#include <iostream>

Ringpuffer::Ringpuffer()
{
	anker = new Ringnode();
}

/*
	Contructor for first Node
*/
Ringpuffer::Ringpuffer(std::string desc, std::string data) {
	Ringnode* newNode = new Ringnode(nullptr, desc, data, 0);
	anker->next = newNode;
}
/*
	Destructor 
*/
Ringpuffer::~Ringpuffer() {
}

/*
	New Node as First in with age=0,
	if the ring is full delete last and push
*/
void Ringpuffer::addNode(std::string desc, std::string data) {

	increaseAge();

	Ringnode* newNode = new Ringnode(nullptr, desc, data, 0);
	//if Ring is empty newNode is first element
	if (anker->next == nullptr) anker->next = newNode;
	//if Ring is not empty but only one element
	else if (anker->next->next == nullptr) {
		newNode->next = anker->next;
		anker->next->next = newNode;
		anker->next = newNode;
	}
	//Ring full then delete last element and push newNode
	else if (anker->next->next->getAge() == 6) {
		newNode->next = anker->next->next->next;
		delete anker->next->next;
		anker->next->next = newNode;
		anker->next = newNode;
	}
	//Ring not full
	else {
		newNode->next = anker->next->next;
		anker->next->next = newNode;
		anker->next = newNode;
	}

}

bool Ringpuffer::search(std::string data) {
	
	Ringnode* index;
	index = anker->next;

	do {
		if (index->data == data) {
			std::cout << "++ Backup found ++ || ";
			std::cout << "OldAge: " << index->oldAge << " | Description: " << index->desc << " | Data: " << index->data << std::endl;
			return true;
		}
		index = index->next;
	} while (index != nullptr && index != anker->next);
	std::cout << "-- Backup not found --" << std::endl;
	return false;
}
/*
	printing the whole ring to console
*/
void Ringpuffer::print_all() {

	Ringnode* index;
	index = anker->next;

	do{
		std::cout << " || ";
		std::cout << index->desc << " | ";
		std::cout << index->data << " | ";
		std::cout << index->oldAge << " || ";
		std::cout << std::endl;

		index = index->next;
	} while (index != nullptr && index != anker->next);
	//std::cout << index->data << std::endl;
}

void Ringpuffer::print_rec(Ringnode* n) {
	//if (n->next != anker->next && n->next != nullptr) {
	if (n->next->oldAge != 0 && n->next != nullptr) {
		//print_rec(n->next);
		n = n->next;
		print_rec(n);
		std::cout << "OldAge: " << n->oldAge << " | Description: " << n->desc << " | Data: " << n->data << std::endl;
	}
	else {
		std::cout << "OldAge: " << n->next->oldAge << " | Description: " << n->next->desc << " | Data: " << n->next->data << std::endl;
	}
}

void Ringpuffer::print()
{
	//Rekursive
	if (!(is_ring_empty())) {
		//std::cout << "OldAge: " << anker->next->oldAge << " | Description: " << anker->next->desc << " | Data: " << anker->next->data << std::endl;
		print_rec(anker->next);
	}
}

void Ringpuffer::increaseAge()
{
	Ringnode* index;
	if (anker->next == nullptr) return;
	index = anker->next;
	do {
		index->oldAge++;
		index = index->next;
	} while (index != nullptr && index != anker->next);
}

bool Ringpuffer::is_ring_empty()
{
	if (anker->next == nullptr) return true;
	else return false;
}
